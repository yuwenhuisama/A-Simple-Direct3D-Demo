#include "ShadowMapVertexShader.h"
#include "DxUtils/D3DHelper.hpp"
#include "DxUtils/Direct3DManager.h"
#include "GameUtils/GameConfigure.h"

ShadowMapVertexShader::ShadowMapVertexShader() : VertexShaderBase() {}

ShadowMapVertexShader::~ShadowMapVertexShader() {
    D3DHelper::SafeRelease(m_pWVPBuffer);
}

std::wstring ShadowMapVertexShader::GetShaderFile() {
    return L"HLSL/shadow_map_shape_vs.fx";
}

std::string ShadowMapVertexShader::GetShaderEntryName() {
    return "VSMain";
}

std::string ShadowMapVertexShader::GetShaderVersion() {
    return "vs_5_0";
}

bool ShadowMapVertexShader::DefineShaderSubResource() {
    D3D11_BUFFER_DESC dbdMatrix;
    memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
    dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    dbdMatrix.ByteWidth = sizeof(ShadowMapVertexShaderBuffer);
    dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

    const auto result = Direct3DManager::Instance().CreateBuffer(dbdMatrix, m_pWVPBuffer);

    if (FAILED(result)) {
        return false;
    }

    return true;
}

constexpr D3D11_INPUT_ELEMENT_DESC s_arrDesc[] = {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0},
};
const D3D11_INPUT_ELEMENT_DESC* ShadowMapVertexShader::GetInputLayoutDescArray() {
    return s_arrDesc;
}

UINT ShadowMapVertexShader::GetInputLayoutDescArraySize() {
    return static_cast<UINT>(std::size(s_arrDesc));
}

void ShadowMapVertexShader::UpdateWVPMatrix(const ShadowMapVertexShaderBuffer& mtBuffer) {
    const auto pDeviceContext = Direct3DManager::Instance().GetDeviceContext();
    pDeviceContext->UpdateSubresource(m_pWVPBuffer, 0, nullptr, &mtBuffer, 0, 0);
    pDeviceContext->VSSetConstantBuffers(0, 1, &m_pWVPBuffer);
}

void ShadowMapVertexShader::Apply(const RenderCommand& rcCommand) {
    if (rcCommand.m_eType == RenderCommandType::SetWorldMatrix) {
        DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();

        const auto& mtWorldMatrix = std::any_cast<std::function<DirectX::XMMATRIX(void)>>(rcCommand.m_objRenderInfo)();

        const auto& f4Region = GameConfigure::Instance().GetRandomGroundConfigure();
        const auto& mtProjMatrix = DirectX::XMMatrixOrthographicOffCenterLH(
            f4Region.m_f4Region.x,
            f4Region.m_f4Region.z,
            f4Region.m_f4Region.w,
            f4Region.m_f4Region.y,
            -10.0f,
            100.0f
        );

        const auto& mtViewMatrix = DirectX::XMMatrixLookAtLH(
            { m_f3LightPos.x, m_f3LightPos.y, m_f3LightPos.z },
            { 0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f });

        ShadowMapVertexShaderBuffer bfBuffer;
        bfBuffer.m_mtWorld = DirectX::XMMatrixTranspose(mtWorldMatrix);
        bfBuffer.m_mtView = DirectX::XMMatrixTranspose(mtViewMatrix);
        bfBuffer.m_mtProj = DirectX::XMMatrixTranspose(mtProjMatrix);

        this->UpdateWVPMatrix(bfBuffer);
    } else if (rcCommand.m_eType == RenderCommandType::SetLightInfo) {
        auto fCallback = std::any_cast<std::function<LightCommonPixelShaderBuffer(void)>>(rcCommand.m_objRenderInfo);
        auto bfLightInfo = fCallback();

        m_f3LightPos = bfLightInfo.m_f3LightPos;
    }
}
