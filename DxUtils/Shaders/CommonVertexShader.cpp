#include "CommonVertexShader.h"
#include "DxUtils/Direct3DManager.h"
#include "DxUtils/D3DHelper.hpp"
#include "GameObjects/Camera.h"
#include "GameObjects/GameObject.h"

CommonVertexShader::CommonVertexShader() : VertexShaderBase() {

}

CommonVertexShader::~CommonVertexShader() {
    D3DHelper::SafeRelease(m_pWVPBuffer);
}

std::wstring CommonVertexShader::GetShaderFile() {
    return L"HLSL/shape_vs.fx";
}

std::string CommonVertexShader::GetShaderEntryName() {
    return "VSMain";
}

std::string CommonVertexShader::GetShaderVersion() {
    return "vs_5_0";
}

bool CommonVertexShader::DefineShaderSubResource() {
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
    {"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

const D3D11_INPUT_ELEMENT_DESC* CommonVertexShader::GetInputLayoutDescArray() {
    return s_arrDesc;
}

UINT CommonVertexShader::GetInputLayoutDescArraySize() {
    return static_cast<UINT>(std::size(s_arrDesc));
}

void CommonVertexShader::UpdateWVPMatrix(const DirectX::XMMATRIX& mtMatrix) {
    const auto pDeviceContext = Direct3DManager::Instance().GetDeviceContext();
    pDeviceContext->UpdateSubresource(m_pWVPBuffer, 0, nullptr, &mtMatrix, 0, 0);
    pDeviceContext->VSSetConstantBuffers(0, 1, &m_pWVPBuffer);
}

void CommonVertexShader::Apply(const RenderCommand& rcCommand) {
    if (rcCommand.m_eType == RenderCommandType::SetWorldMatrix) {
        DirectX::XMMATRIX I = DirectX::XMMatrixIdentity();

        const auto& mtWorldMatrix = std::any_cast<std::function<DirectX::XMMATRIX(void)>>(rcCommand.m_objRenderInfo)();
        const auto& mtProjMatrix = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV4, Direct3DManager::Instance().GetWindowAspect(), 1.0f, 1000.0f);
        const auto& mtViewMatrix = Camera::Instance().GetViewMatrix();

        auto mtWorldViewProjMatrix = mtWorldMatrix * mtViewMatrix * mtProjMatrix;

        this->UpdateWVPMatrix(DirectX::XMMatrixTranspose(mtWorldViewProjMatrix));
    }
}
