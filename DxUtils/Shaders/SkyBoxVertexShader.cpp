#include "SkyBoxVertexShader.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/D3DHelper.hpp"
#include "GameObjects/Camera.h"

SkyBoxVertexShader::SkyBoxVertexShader() : VertexShaderBase() {}

SkyBoxVertexShader::~SkyBoxVertexShader() {
    D3DHelper::SafeRelease(m_pWVPBuffer);
}

std::wstring SkyBoxVertexShader::GetShaderFile() {
    return L"HLSL/skybox_vs.fx";
}

std::string SkyBoxVertexShader::GetShaderEntryName() {
    return "VSMain";
}

std::string SkyBoxVertexShader::GetShaderVersion() {
    return "vs_5_0";
}

bool SkyBoxVertexShader::DefineShaderSubResource() {
    D3D11_BUFFER_DESC dbdMatrix;
    memset(&dbdMatrix, 0, sizeof(D3D11_BUFFER_DESC));
    dbdMatrix.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    dbdMatrix.ByteWidth = sizeof(DirectX::XMMATRIX);
    dbdMatrix.Usage = D3D11_USAGE_DEFAULT;

    const auto result = Direct3DManager::Instance().CreateBuffer(dbdMatrix, m_pWVPBuffer);

    if (FAILED(result)) {
        return false;
    }

    return true;
}

constexpr D3D11_INPUT_ELEMENT_DESC s_arrDesc[] = {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

const D3D11_INPUT_ELEMENT_DESC* SkyBoxVertexShader::GetInputLayoutDescArray() {
    return s_arrDesc;
}

UINT SkyBoxVertexShader::GetInputLayoutDescArraySize() {
    return static_cast<UINT>(std::size(s_arrDesc));
}

void SkyBoxVertexShader::UpdateWVPMatrix(const DirectX::XMMATRIX& mtMatrix) {
    const auto pDeviceContext = Direct3DManager::Instance().GetDeviceContext();
    pDeviceContext->UpdateSubresource(m_pWVPBuffer, 0, nullptr, &mtMatrix, 0, 0);
    pDeviceContext->VSSetConstantBuffers(0, 1, &m_pWVPBuffer);
}


void SkyBoxVertexShader::Apply(const RenderCommand& rcCommand) {
    if (rcCommand.m_eType == RenderCommandType::SetWorldMatrix) {
        DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();

        const auto& mtWorldMatrix = std::any_cast<std::function<DirectX::XMMATRIX(void)>>(rcCommand.m_objRenderInfo)();
        const auto& mtProjMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, Direct3DManager::Instance().GetWindowAspect(), 1.0f, 1000.0f);
        const auto& mtViewMatrix = Camera::Instance().GetViewMatrix();

        auto mtWorldViewProjMatrix = mtWorldMatrix * mtViewMatrix * mtProjMatrix;

        this->UpdateWVPMatrix(DirectX::XMMatrixTranspose(mtWorldViewProjMatrix));
    }
}
