#ifndef _H_JSONMODEL_
#define _H_JSONMODEL_

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>

#include "GameObjects/GameObject.h"
#include "GameObjects/InstancedGameObject.h"
#include "DxUtils/D3DHelper.hpp"

class JsonModel : public GameObject {
private:
    std::list<std::shared_ptr<InstancedGameObject>> m_lsGameObjects;

    std::list<InstancedInfo> _GetInstancedInfo(rapidjson::Value::Object& dcDom);
    void _ProcessJsonValue(rapidjson::Value::Array& dcRoot);
    void _ProcessJsonValue(rapidjson::Value::Object& dcRoot);


protected:
    virtual std::string GetJsonFilePath() = 0;
    virtual void Render() override;

public:

    virtual std::shared_ptr<GameObject> FindGameObjectByTag(std::string_view strTag) override;

    virtual void AddChild(std::shared_ptr<InstancedGameObject> pObject);
    virtual void RemoveChild(std::shared_ptr<InstancedGameObject> pObject); 

    JsonModel();
    virtual ~JsonModel();

    virtual bool Initialize();
};

#endif // !_H_JSONMODEL_
