#ifndef _H_COMMANDQUEUE_
#define _H_COMMANDQUEUE_
#include <list>
#include "RenderCommand.h"
#include "DxUtils/D3DHelper.hpp"

enum class RenderCommandState {
    Normal = 0,
    Instanced,
};

class RenderCommandQueueManager {
private:
    RenderCommandQueueManager() = default;
    ~RenderCommandQueueManager() = default;

    std::list<RenderCommand> m_lsQueue;

    RenderCommandState m_eState = RenderCommandState::Normal;

    std::list<InstancedInfo>* m_pCurInfo = nullptr;

    DirectX::XMMATRIX m_mtBuffer;
    
private:
    void _RenderObject(RenderCommand& rcCommand);
    void _SetWorldMatrix(RenderCommand& rcCommand);
    void _BeginInstance(RenderCommand& rcCommand);
    void _EndInstance(RenderCommand& rcCommand);
    void _SetInstancedInfo(RenderCommand& rcCommand);
    void _SetBaseModelRenderInfo(RenderCommand& rcCommand);
    void _SetTexture(RenderCommand& rcCommand);
    void _RenderSkyBox(RenderCommand& rcCommand);
    void _SetLightInfo(RenderCommand& rcCommand);

public:
    void Initialize();

    static RenderCommandQueueManager& Instance();

    void Push(RenderCommand& rcCommand);
    void Render();
};

#endif // !_H_COMMANDQUEUE_
