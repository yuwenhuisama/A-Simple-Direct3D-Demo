#include "ShadowedLightCommonVertexShader.h"
#include "DxUtils/Direct3DManager.h"
#include "GameObjects/Camera.h"
#include "GameUtils/GameConfigure.h"
#include "DxUtils/D3DHelper.hpp"

ShadowedLightCommonVertexShader::ShadowedLightCommonVertexShader() : VertexShaderBase() {}

ShadowedLightCommonVertexShader::~ShadowedLightCommonVertexShader() {
    D3DHelper::SafeRelease(m_pWVPBuffer);
}


std::wstring ShadowedLightCommonVertexShader::GetShaderFile() {
    return L"HLSL/shadowed_light_shape_vs.fx";
}

std::string ShadowedLightCommonVertexShader::GetShaderEntryName() {
    return "VSMain";
}

std::string ShadowedLightCommonVertexShader::GetShaderVersion() {
    return "vs_5_0";
}

bool ShadowedLightCommonVertexShader::DefineShaderSubResource() {
    D3D11_BUFFER_DESC dbdMatrix;
    memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
    dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    dbdMatrix.ByteWidth = sizeof(ShadowedLightCommonVertexShaderBuffer);
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
const D3D11_INPUT_ELEMENT_DESC* ShadowedLightCommonVertexShader::GetInputLayoutDescArray() {
    return s_arrDesc;
}

UINT ShadowedLightCommonVertexShader::GetInputLayoutDescArraySize() {
    return static_cast<UINT>(std::size(s_arrDesc));
}

void ShadowedLightCommonVertexShader::Apply(const RenderCommand& rcCommand) {
    if (rcCommand.m_eType == RenderCommandType::SetWorldMatrix) {
        DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();

        const auto& mtWorldMatrix = std::any_cast<std::function<DirectX::XMMATRIX(void)>>(rcCommand.m_objRenderInfo)();
        const auto& mtProjMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, Direct3DManager::Instance().GetWindowAspect(), 1.0f, 1000.0f);

        const auto& mtViewMatrix = Camera::Instance().GetViewMatrix();

        ShadowedLightCommonVertexShaderBuffer bfBuffer;
        bfBuffer.m_mtWorld = DirectX::XMMatrixTranspose(mtWorldMatrix);
        bfBuffer.m_mtView = DirectX::XMMatrixTranspose(mtViewMatrix);
        bfBuffer.m_mtProj = DirectX::XMMatrixTranspose(mtProjMatrix);
        bfBuffer.m_mtWorldNormal = DirectX::XMMatrixInverse(nullptr, mtWorldMatrix); // transpose(transpose(inverse))

        const auto& f4Region = GameConfigure::Instance().GetLightConfigure().m_f4ProjectionRegion;
        const auto& mtLightProjMatrix = DirectX::XMMatrixOrthographicOffCenterLH(
            f4Region.x,
            f4Region.z,
            f4Region.w,
            f4Region.y,
            0.0f,
            100.0f
        );

        const auto& f3LightPos = GameConfigure::Instance().GetLightConfigure().m_f3LightEyePosition;
        const auto& mtLightViewMatrix = DirectX::XMMatrixLookAtLH(
            { f3LightPos.x, f3LightPos.y, f3LightPos.z },
            { 0.0f, 0.0f, 0.0f },
            { 1.0f, 0.0f, 0.0f });

        bfBuffer.m_mtLightView = DirectX::XMMatrixTranspose(mtLightViewMatrix);
        bfBuffer.m_mtLightProj = DirectX::XMMatrixTranspose(mtLightProjMatrix);

        this->UpdateWVPMatrix(bfBuffer);
    }
}

void ShadowedLightCommonVertexShader::UpdateWVPMatrix(const ShadowedLightCommonVertexShaderBuffer& mtBuffer) {
    const auto pDeviceContext = Direct3DManager::Instance().GetDeviceContext();
    pDeviceContext->UpdateSubresource(m_pWVPBuffer, 0, nullptr, &mtBuffer, 0, 0);
    pDeviceContext->VSSetConstantBuffers(0, 1, &m_pWVPBuffer);
}
