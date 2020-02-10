#ifndef _H_D3DHELPER_
#define _H_D3DHELPER_

#include <d3d11.h>
#include <DirectXMath.h>
#include <functional>

#include <string>

#include <Windows.h>

namespace D3DHelper {
    template<class T>
    void SafeRelease(T& p) {
        if (p) {
            p->Release();
            p = nullptr;
        }
    }

    DirectX::XMMATRIX CalcWorldMatrix(const DirectX::XMFLOAT3& v3Translation, const  DirectX::XMFLOAT3& v3Rotation, const  DirectX::XMFLOAT3& v3Scale);

    std::wstring StringToWString(const std::string& str);
    std::string WStringToString(const std::wstring &wstr);

    bool RandomBool();
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
    DirectX::XMFLOAT3 m_v3Position;
    DirectX::XMFLOAT3 m_v3Rotation;
    DirectX::XMFLOAT3 m_v3Scale;
    std::function<void(InstancedInfo&)> m_fUpdate;
};

#endif // !_H_D3DHELPER_
