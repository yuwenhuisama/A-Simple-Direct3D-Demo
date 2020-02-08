#ifndef _H_COMMONEFFECT_
#define _H_COMMONEFFECT_

#include "Effect.h"

class CommonEffect : public Effect {
private:
    ID3DX11EffectMatrixVariable* m_pMatrix = nullptr;

public:
    virtual std::wstring GetEffectFilePath() override;
    virtual void PostInitialize() override;

    virtual std::vector<EffectPassInfo> GetPassInfo() override;

    CommonEffect() = default;
    virtual ~CommonEffect();
};

#endif // !_H_COMMONEFFECT_
