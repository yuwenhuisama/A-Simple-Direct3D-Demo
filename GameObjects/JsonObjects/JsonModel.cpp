#include "JsonModel.h"
#include <fstream>

#include "GameObjects/BasicShapes/Cuboid.h"
#include "GameObjects/BasicShapes/Sphare.h"
#include "GameObjects/BasicShapes/Cylinder.h"

#include "DxUtils/RenderCommandQueue/RenderCommandQueueManager.h"
#include "DxUtils/D3DHelper.hpp"

JsonModel::JsonModel() : GameObject() {}

JsonModel::~JsonModel() {}

#undef GetObject
std::list<InstancedInfo> JsonModel::_GetInstancedInfo(rapidjson::Value::Object& dcDom) {
    std::list<InstancedInfo> iiList;

    InstancedInfo iiInfo;
    iiInfo.m_fUpdate = nullptr;
    auto vRenderInfo = dcDom.FindMember("render_info")->value.GetArray();

    auto uSize = vRenderInfo.Size();

    for (auto i = 0u; i < uSize; ++i) {
        auto vObj = vRenderInfo[i].GetObject();
        auto vArray = vObj.FindMember("position")->value.GetArray();
        iiInfo.m_v3Position = { vArray[0].GetFloat(), vArray[1].GetFloat(), vArray[2].GetFloat() };

        vArray = vObj.FindMember("rotation")->value.GetArray();
        iiInfo.m_v3Rotation = {
            DirectX::XM_PI * vArray[0].GetFloat(),
            DirectX::XM_PI * vArray[1].GetFloat(),
            DirectX::XM_PI * vArray[2].GetFloat()
        };

        vArray = vObj.FindMember("scale")->value.GetArray();
        iiInfo.m_v3Scale = { vArray[0].GetFloat(), vArray[1].GetFloat(), vArray[2].GetFloat() };

        iiList.push_back(iiInfo);
    }

    return iiList;
}

void JsonModel::_ProcessJsonValue(rapidjson::Value::Object& dcRoot) {
    if (dcRoot.HasMember("type")) {
        auto itType = dcRoot.FindMember("type");
        auto strType = std::string(itType->value.GetString());

        if (strType == "conbinant") {
            auto dcChildren = dcRoot.FindMember("children")->value.GetArray();
            this->_ProcessJsonValue(dcChildren);
        } else if (strType == "cylinder") {
            auto fTopRadius = dcRoot.FindMember("top_radius")->value.GetFloat();
            auto fBottomRadius = dcRoot.FindMember("bottom_radius")->value.GetFloat();
            auto fHeight = dcRoot.FindMember("height")->value.GetFloat();
            auto uStackCount = dcRoot.FindMember("stack_count")->value.GetUint();
            auto uSliceCount = dcRoot.FindMember("slice_count")->value.GetUint();

            auto strTexture = D3DHelper::StringToWString(dcRoot.FindMember("texture")->value.GetString());
            auto iiList = this->_GetInstancedInfo(dcRoot);

            auto pInnerCylindre = std::make_shared<Cylinder>(fTopRadius, fBottomRadius, fHeight, uSliceCount, uStackCount);
            pInnerCylindre->Initialize();

            auto pTexture = std::make_shared<Texture>();
            pTexture->Load(strTexture);
            pInnerCylindre->SetTexture(pTexture);

            auto pCylinder = std::make_shared<InstancedGameObject>(pInnerCylindre);
            pCylinder->GetAssignedInstancedInfo() = iiList;

            this->AddChild(pCylinder);
        } else if (strType == "sphare") {
            auto fRadius = dcRoot.FindMember("radius")->value.GetFloat();
            auto uStackCount = dcRoot.FindMember("stack_count")->value.GetUint();
            auto uSliceCount = dcRoot.FindMember("slice_count")->value.GetUint();

            auto strTexture = D3DHelper::StringToWString(dcRoot.FindMember("texture")->value.GetString());
            auto iiList = this->_GetInstancedInfo(dcRoot);

            auto pInnerSphare = std::make_shared<Sphare>(fRadius, uStackCount, uSliceCount);
            pInnerSphare->Initialize();

            auto pTexture = std::make_shared<Texture>();
            pTexture->Load(strTexture);
            pInnerSphare->SetTexture(pTexture);

            auto pShpare = std::make_shared<InstancedGameObject>(pInnerSphare);
            pShpare->GetAssignedInstancedInfo() = iiList;

            this->AddChild(pShpare);

        } else if (strType == "cuboid") {
            auto fWidth = dcRoot.FindMember("width")->value.GetFloat();
            auto fHeight = dcRoot.FindMember("height")->value.GetFloat();
            auto fDepth = dcRoot.FindMember("depth")->value.GetFloat();
            auto strTexture = D3DHelper::StringToWString(dcRoot.FindMember("texture")->value.GetString());
            auto iiList = this->_GetInstancedInfo(dcRoot);

            auto pInnerCuboid = std::make_shared<Cuboid>(fWidth, fHeight, fDepth);
            pInnerCuboid->Initialize();

            auto pTexture = std::make_shared<Texture>();
            pTexture->Load(strTexture);
            pInnerCuboid->SetTexture(pTexture);

            auto pCuboid = std::make_shared<InstancedGameObject>(pInnerCuboid);
            pCuboid->GetAssignedInstancedInfo() = iiList;

            this->AddChild(pCuboid);
        }
    }
}

void JsonModel::_ProcessJsonValue(rapidjson::Value::Array& dcRoot) {
    auto& vArray = dcRoot; 
    auto uSize = vArray.Size();

    for (auto i = 0u; i < uSize; ++i) {
        auto vObj = vArray[i].GetObject();
        this->_ProcessJsonValue(vObj);
    }
}

bool JsonModel::Initialize() {
    const auto& strFilePath = this->GetJsonFilePath();

    std::ifstream ifsFile(strFilePath, std::ifstream::binary);

    if (!ifsFile) {
        ifsFile.close();
        return false;
    }

    std::string strContent;
    std::string strLine;
    while (std::getline(ifsFile, strLine)) {
        strContent += strLine;
    }

    rapidjson::Document dDoc;
    if (dDoc.Parse(strContent.c_str()).HasParseError()) {
        return false;
    }

    if (dDoc.IsArray()) {
        this->_ProcessJsonValue(dDoc.GetArray());
    } else if (dDoc.IsObject()) {
        this->_ProcessJsonValue(dDoc.GetObject());
    }

    return true;
}

void JsonModel::AddChild(std::shared_ptr<InstancedGameObject> pObject) {
    m_lsGameObjects.push_back(pObject);
}

void JsonModel::RemoveChild(std::shared_ptr<InstancedGameObject> pObject) {
    m_lsGameObjects.remove(pObject);
}

std::shared_ptr<GameObject> JsonModel::FindGameObjectByTag(std::string_view strTag) {
    if (strTag == this->GetTag()) {
        return shared_from_this();
    } else {
        // return this->_FindGameObjectByTag(strTag, shared_from_this());
        for (auto pObject : m_lsGameObjects) {
            if (pObject->GetTag() == strTag) {
                return pObject;
            }
        }
    }
    return nullptr;
}

void JsonModel::Render() {
    std::function<DirectX::XMMATRIX(void)> fCallback = [this]() { return this->GetWorldMatrix(); };
    
    RenderCommandQueueManager::Instance().Push(
        RenderCommand { RenderCommandType::SetBaseModelRenderInfo,
            fCallback
        }
    );

    for (auto& pModel : m_lsGameObjects) {
        pModel->Render();
    }
}
