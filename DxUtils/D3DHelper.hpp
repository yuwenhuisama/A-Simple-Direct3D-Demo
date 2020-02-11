#ifndef _H_D3DHELPER_
#define _H_D3DHELPER_

#include <d3d11.h>
#include <DirectXMath.h>
#include <functional>

#include <array>
#include <string>
#include <Windows.h>

#include "GameObjects/GameObject.h"

namespace D3DHelper {
    template<class T>
    void SafeRelease(T& p) {
        if (p) {
            p->Release();
            p = nullptr;
        }
    }

    DirectX::XMMATRIX CalcWorldMatrix(
        const DirectX::XMFLOAT3& v3Translation,
        const DirectX::XMFLOAT3& v3Rotation,
        const DirectX::XMFLOAT3& v3Scale,
        const std::array<RotationOrderAxis, 3>& arrRotationOrder);

    std::wstring StringToWString(const std::string& str);
    std::string WStringToString(const std::wstring &wstr);

    bool RandomBool(float fRate);
    float RandomFloatInRange(float fFrom, float fTo);
    int RandomIntegerInRange(int nFrom, int nTo);

    HRESULT CreateWICTexture2DCubeFromFile(
        ID3D11Device* d3dDevice,
        ID3D11DeviceContext* d3dDeviceContext,
        std::wstring_view cubeMapFileName,
        ID3D11Texture2D** textureArray,
        ID3D11ShaderResourceView** textureCubeView,
        bool generateMips);
};

struct InstancedInfo {
    DirectX::XMFLOAT3 m_v3Position = { 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 m_v3Rotation = { 0.0f, 0.0f, 0.0f };
    DirectX::XMFLOAT3 m_v3Scale = { 1.0f, 1.0f, 1.0f };
    std::array<RotationOrderAxis, 3> m_arrRotationOrder = { RotationOrderAxis::X, RotationOrderAxis::Y, RotationOrderAxis::Z };
    std::function<void(InstancedInfo&)> m_fUpdate = nullptr;
};

#endif // !_H_D3DHELPER_
