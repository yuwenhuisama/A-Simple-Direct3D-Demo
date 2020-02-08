#ifndef _H_RENDERCOMMAND_
#define _H_RENDERCOMMAND_

#include <any>

enum class RenderCommandType {
    Render,
    BeginInstance,
    EndInstance,
    SetWorldMatrix,
    SetInstancedInfo,
    SetBaseModelRenderInfo,
    SetTexture,
};

struct RenderCommand {
    RenderCommandType m_eType;
    std::any m_objRenderInfo;
};

#endif // !_H_RENDERCOMMAND_
