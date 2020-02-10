#ifndef _H_GROUND_
#define _H_GROUND_

#include "JsonModel.h"
#include <vector>

struct RegionRect {
    float left, top, right, bottom;
};

class Texture;
class Ground : public JsonModel{
private:
    std::vector<RegionRect> m_stRegionSet;

private:
    std::shared_ptr<Texture> _RandomTexture();

    void _GenerateSphare(size_t uFrom, size_t uTo);
    void _GenerateCylinder(size_t uFrom, size_t uTo);
    void _GenerateCuboid(size_t uFrom, size_t uTo);
    void _GenerateShape(size_t uFrom, size_t uTo);

    void _RandomGenerateModels();
    void _DecideGeneratingRegion(const RegionRect& v4Region, size_t uLevel);

protected:
    virtual std::string GetJsonFilePath() override;
    virtual void Update() override;

public:
    Ground();
    virtual ~Ground() = default;

    virtual bool Initialize() override;

};

#endif // !_H_GROUND_
