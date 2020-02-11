#include "Configure.h"
#include <fstream>
#include <string>

Configure::~Configure() {}

std::string Configure::GetString(rapidjson::Value::Object vObject,std::string_view strvFieldName) {
    assert(vObject.HasMember(strvFieldName.data()) == true);
    auto pMember = vObject.FindMember(strvFieldName.data());
    assert(pMember->value.IsString() == true);
    return pMember->value.GetString();
}

int Configure::Configure::GetInt(rapidjson::Value::Object vObject, std::string_view strvFieldName) {
    assert(vObject.HasMember(strvFieldName.data()) == true);
    auto pMember = vObject.FindMember(strvFieldName.data());
    assert(pMember->value.IsInt() == true);
    return pMember->value.GetInt();
}

float Configure::GetFloat(rapidjson::Value::Object vObject, std::string_view strvFieldName) {
    assert(vObject.HasMember(strvFieldName.data()) == true);
    auto pMember = vObject.FindMember(strvFieldName.data());
    assert(pMember->value.IsFloat() == true);
    return pMember->value.GetFloat();
}

std::vector<int> Configure::GetIntArray(rapidjson::Value::Object vObject, std::string_view strvFieldName) {
    assert(vObject.HasMember(strvFieldName.data()) == true);
    auto pMember = vObject.FindMember(strvFieldName.data());
    assert(pMember->value.IsArray() == true);

    auto garrArray = pMember->value.GetArray();
    auto uSize = garrArray.Size();

    std::vector<int> vcResult(uSize);
    for (auto i = 0u; i < uSize; ++i) {
        auto& vValue = garrArray[i];

        assert(vValue.IsInt() == true);
        vcResult[i] = vValue.GetInt();
    }

    return vcResult;
}

std::vector<float> Configure::GetFloatArray(rapidjson::Value::Object vObject, std::string_view strvFieldName) {
    assert(vObject.HasMember(strvFieldName.data()) == true);
    auto pMember = vObject.FindMember(strvFieldName.data());
    assert(pMember->value.IsArray() == true);

    auto garrArray = pMember->value.GetArray();
    auto uSize = garrArray.Size();

    std::vector<float> vcResult(uSize);
    for (auto i = 0u; i < uSize; ++i) {
        auto& vValue = garrArray[i];

        assert(vValue.IsFloat() == true);
        vcResult[i] = vValue.GetFloat();
    }

    return vcResult;
}

bool Configure::Initialize(std::string_view strvConfigureFileName) {
    std::ifstream ifsFile(strvConfigureFileName.data(), std::ifstream::binary);

    if (!ifsFile) {
        ifsFile.close();
        return false;
    }

    std::string strContent;
    std::string strLine;
    while (std::getline(ifsFile, strLine)) {
        strContent += strLine;
    }

    if (m_dcDocument.Parse(strContent.c_str()).HasParseError()) {
        return false;
    }

    return true;
}
