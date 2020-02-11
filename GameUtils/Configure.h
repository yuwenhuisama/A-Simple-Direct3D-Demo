#ifndef _H_CONFIGURE_
#define _H_CONFIGURE_

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

#include <vector>

class Configure {
protected:
    rapidjson::Document m_dcDocument;

public:
    Configure() = default;
    virtual ~Configure() = 0;

    virtual bool Initialize(std::string_view strvConfigureFileName);

    std::string GetString(rapidjson::Value::Object vObject, std::string_view strvFieldName);
    int GetInt(rapidjson::Value::Object vObject, std::string_view strvFieldName);
    float GetFloat(rapidjson::Value::Object vObject, std::string_view strvFieldName);

    std::vector<int> GetIntArray(rapidjson::Value::Object vObject, std::string_view strvFieldName);
    std::vector<float> GetFloatArray(rapidjson::Value::Object vObject, std::string_view strvFieldName);

};

#endif // !_H_CONFIGURE_
