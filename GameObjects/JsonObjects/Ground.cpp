#include "Ground.h"
#include <array>
#include <algorithm>
#include <chrono>
#include <random>

#include "DxUtils/D3DHelper.hpp"

#include "DxUtils/Texture.h"

#include "GameObjects/BasicShapes/Cuboid.h"
#include "GameObjects/BasicShapes/Cylinder.h"
#include "GameObjects/BasicShapes/Sphare.h"

#include "GameObjects/InstancedGameObject.h"

Ground::Ground() : JsonModel() {}

std::string Ground::GetJsonFilePath() {
    return "SimpleModels/ground.json";
}

void Ground::Update() {

}

constexpr WCHAR* c_arrTextures[] = {
    L"Textures/chouyou.jpg",
    L"Textures/likailikai.jpg",
    L"Textures/shoushenguolai.jpg"
};

std::shared_ptr<Texture> Ground::_RandomTexture() {
    const auto wszTextureName = c_arrTextures[D3DHelper::RandomIntegerInRange(0, static_cast<int>(std::size(c_arrTextures)) - 1)];
    const auto pTexture = std::make_shared<Texture>();
    pTexture->Load(std::wstring(wszTextureName));

    return pTexture;
}

void Ground::_GenerateSphare(size_t uFrom, size_t uTo) {
    const auto uStackCount = D3DHelper::RandomIntegerInRange(10, 200);
    const auto uSliceCount = D3DHelper::RandomIntegerInRange(5, 200);

    const auto pInnerSphare = std::make_shared<Sphare>(1.0f, uStackCount, uSliceCount);
    pInnerSphare->Initialize();

    pInnerSphare->SetTexture(this->_RandomTexture());

    const auto pShpare = std::make_shared<InstancedGameObject>(
        pInnerSphare
    );

    for (auto i = uFrom; i < uTo; ++i){
        InstancedInfo iInfo;
        const auto& rtRegion = m_stRegionSet[i];

        DirectX::XMFLOAT2 v2Center {
            rtRegion.left + (rtRegion.right - rtRegion.left) / 2,
            rtRegion.top + (rtRegion.bottom - rtRegion.top) / 2,
        };

        DirectX::XMFLOAT3 v3Rotation {
            D3DHelper::RandomFloatInRange(0.0f, DirectX::XM_2PI),
            D3DHelper::RandomFloatInRange(0.0f, DirectX::XM_2PI),
            D3DHelper::RandomFloatInRange(0.0f, DirectX::XM_2PI),
        };

        const auto fMaxRadius = min(rtRegion.right - rtRegion.left, rtRegion.bottom - rtRegion.top);

        DirectX::XMFLOAT3 v3Scale {
            D3DHelper::RandomFloatInRange(0.1f, fMaxRadius),
            D3DHelper::RandomFloatInRange(0.1f, 5.0f),
            D3DHelper::RandomFloatInRange(0.1f, fMaxRadius),
        };

        // pos
        iInfo.m_v3Position.x = v2Center.x;
        iInfo.m_v3Position.z = v2Center.y;
        iInfo.m_v3Position.y = v3Scale.y;

        // rotation
        iInfo.m_v3Rotation = v3Rotation;

        // scale
        iInfo.m_v3Scale = v3Scale;

        iInfo.m_arrRotationOrder = { RotationOrderAxis::X, RotationOrderAxis::Y, RotationOrderAxis::Z };

        pShpare->AppendInstancedInfo(iInfo);
    }

    this->AddChild(pShpare);
}

void Ground::_GenerateCylinder(size_t uFrom, size_t uTo) {
    const auto uStackCount = D3DHelper::RandomIntegerInRange(10, 200);
    const auto uSliceCount = D3DHelper::RandomIntegerInRange(5, 200);

    const auto fTopRadius =  D3DHelper::RandomFloatInRange(0.0f, 1.0f);
    const auto fBottomRadius =  D3DHelper::RandomFloatInRange(0.0f, 1.0f);

    const auto pInnerCylinder = std::make_shared<Cylinder>(fTopRadius, fBottomRadius, 1.0f, uStackCount, uSliceCount);
    pInnerCylinder->Initialize();

    pInnerCylinder->SetTexture(this->_RandomTexture());

    const auto pCylinder = std::make_shared<InstancedGameObject>(
        pInnerCylinder
    );

    for (auto i = uFrom; i < uTo; ++i){
        InstancedInfo iInfo;
        const auto& rtRegion = m_stRegionSet[i];

        DirectX::XMFLOAT2 v2Center {
            rtRegion.left + (rtRegion.right - rtRegion.left) / 2,
            rtRegion.top + (rtRegion.bottom - rtRegion.top) / 2,
        };

        DirectX::XMFLOAT3 v3Rotation {
            0.0f,
            D3DHelper::RandomFloatInRange(0.0f, DirectX::XM_2PI),
            0.0f,
        };

        const auto fMaxRadius = min(rtRegion.right - rtRegion.left, rtRegion.bottom - rtRegion.top);

        DirectX::XMFLOAT3 v3Scale {
            D3DHelper::RandomFloatInRange(0.1f, fMaxRadius),
            D3DHelper::RandomFloatInRange(0.1f, 5.0f),
            D3DHelper::RandomFloatInRange(0.1f, fMaxRadius),
        };

        // pos
        iInfo.m_v3Position.x = v2Center.x;
        iInfo.m_v3Position.z = v2Center.y;
        iInfo.m_v3Position.y = v3Scale.y / 2;

        // rotation
        iInfo.m_v3Rotation = v3Rotation;

        // scale
        iInfo.m_v3Scale = v3Scale;

        iInfo.m_arrRotationOrder = { RotationOrderAxis::X, RotationOrderAxis::Y, RotationOrderAxis::Z };

        pCylinder->AppendInstancedInfo(iInfo);
    }

    this->AddChild(pCylinder);
}

void Ground::_GenerateCuboid(size_t uFrom, size_t uTo) {
    const auto pInnerCuboid = std::make_shared<Cuboid>(1.0f, 1.0f, 1.0f);
    pInnerCuboid->Initialize();

    pInnerCuboid->SetTexture(this->_RandomTexture());

    const auto pCuboid = std::make_shared<InstancedGameObject>(
        pInnerCuboid
    );

    for (auto i = uFrom; i < uTo; ++i){
        InstancedInfo iInfo;
        const auto& rtRegion = m_stRegionSet[i];

        DirectX::XMFLOAT2 v2Center {
            rtRegion.left + (rtRegion.right - rtRegion.left) / 2,
            rtRegion.top + (rtRegion.bottom - rtRegion.top) / 2,
        };

        DirectX::XMFLOAT3 v3Rotation {
            0.0f,
            D3DHelper::RandomFloatInRange(0.0f, DirectX::XM_2PI),
            0.0f,
        };

        const auto fMaxRadius = min(rtRegion.right - rtRegion.left, rtRegion.bottom - rtRegion.top);

        DirectX::XMFLOAT3 v3Scale {
            D3DHelper::RandomFloatInRange(0.1f, fMaxRadius),
            D3DHelper::RandomFloatInRange(0.1f, 5.0f),
            D3DHelper::RandomFloatInRange(0.1f, fMaxRadius),
        };

        // pos
        iInfo.m_v3Position.x = v2Center.x;
        iInfo.m_v3Position.z = v2Center.y;
        iInfo.m_v3Position.y = v3Scale.y / 2;

        // rotation
        iInfo.m_v3Rotation = v3Rotation;

        // scale
        iInfo.m_v3Scale = v3Scale;

        iInfo.m_arrRotationOrder = { RotationOrderAxis::X, RotationOrderAxis::Y, RotationOrderAxis::Z };

        pCuboid->AppendInstancedInfo(iInfo);
    }

    this->AddChild(pCuboid);
}

void Ground::_GenerateShape(size_t uFrom, size_t uTo) {
    auto nType = D3DHelper::RandomIntegerInRange(0, 2);
    switch (nType) {
        case 0:
            _GenerateSphare(uFrom, uTo);
            break;
        case 1:
            _GenerateCylinder(uFrom, uTo);
            break;
        case 2:
            _GenerateCuboid(uFrom, uTo);
            break;
        default:
            break;
    }
}

void Ground::_RandomGenerateModels() {
    auto uTotalModels = m_stRegionSet.size();
    const size_t uModelTypes = 12u;

    std::vector<UINT> vcIndex(uTotalModels);
    std::generate(vcIndex.begin(), vcIndex.end(), [n = 0]() mutable { return n++; });

    auto seed = static_cast<size_t>(std::chrono::system_clock::now ().time_since_epoch ().count ());
    std::shuffle(vcIndex.begin(), vcIndex.end(), std::default_random_engine(seed));

    auto nStep = uTotalModels / uModelTypes;
    auto nRemain = uTotalModels % uModelTypes;

    if (nRemain == 0) {
        for (auto i = 0u; i < uModelTypes; ++i) {
            _GenerateShape(i * nStep, (i+1) * nStep);
        }
    } else {
        for (auto i = 0u; i < uModelTypes - 1; ++i) {
            _GenerateShape(i * nStep, (i+1) * nStep);
        }
        _GenerateShape(uTotalModels - nRemain, uTotalModels);
    }
}

void Ground::_DecideGeneratingRegion(const RegionRect& v4Region, size_t uLevel) {  
    if (uLevel >= 6) {
        return;
    }

    if (v4Region.right - v4Region.left < 5.0f || v4Region.bottom - v4Region.top < 5.0f) {
        return;
    }

    const auto fRandomMiddleX = D3DHelper::RandomFloatInRange(v4Region.left, v4Region.right);
    const auto fRandomMiddleY = D3DHelper::RandomFloatInRange(v4Region.top, v4Region.bottom);

    const RegionRect rcLeftTop =  { v4Region.left, v4Region.top,  fRandomMiddleX, fRandomMiddleY };
    const RegionRect rcRightTop = { fRandomMiddleX, v4Region.top,  v4Region.right, fRandomMiddleY };
    const RegionRect rcLeftBottom = { v4Region.left, fRandomMiddleY,  fRandomMiddleX, v4Region.bottom };
    const RegionRect rcRightBottom = { fRandomMiddleX, fRandomMiddleY, v4Region.right, v4Region.bottom };

    const std::array<RegionRect, 4> arrRegions { rcLeftTop, rcRightTop, rcLeftBottom, rcRightBottom };

    if (uLevel >= 4) {
        for (const auto& region : arrRegions) {
            if (!(region.right - region.left < 5.0f || region.bottom - region.top < 5.0f)) {
                if (D3DHelper::RandomBool()) {
                    m_stRegionSet.push_back(region);
                } else {
                        this->_DecideGeneratingRegion(region, uLevel + 1);
                }
            }
        }
    } else {
        for (const auto& region : arrRegions) {
            this->_DecideGeneratingRegion(region, uLevel + 1);
        }
    }
}

bool Ground::Initialize() {
    JsonModel::Initialize();

    m_stRegionSet.clear();

    const RegionRect v4Region = { -150.0f, -150.0f, 150.0f, 150.0f };

    this->_DecideGeneratingRegion(v4Region, 0);
    this->_RandomGenerateModels();

    return true;
}
