#include "D3DHelper.hpp"
#include <random>

#include "DxUtils/WicTextureLoader/WICTextureLoader.h"

namespace D3DHelper {
    DirectX::XMMATRIX   CalcWorldMatrix(
        const DirectX::XMFLOAT3& v3Translation,
        const  DirectX::XMFLOAT3& v3Rotation,
        const  DirectX::XMFLOAT3& v3Scale,
        const std::array<RotationOrderAxis, 3>& arrRotationOrder) {
        DirectX::XMMATRIX mtWorld = DirectX::XMMatrixIdentity();

        const auto mtTranslation = DirectX::XMMatrixTranslation(v3Translation.x, v3Translation.y, v3Translation.z);

        std::array<DirectX::XMMATRIX, 3> arrRotation;
        arrRotation[static_cast<size_t>(arrRotationOrder[0])] = DirectX::XMMatrixRotationX(v3Rotation.x);
        arrRotation[static_cast<size_t>(arrRotationOrder[1])] = DirectX::XMMatrixRotationY(v3Rotation.y);
        arrRotation[static_cast<size_t>(arrRotationOrder[2])] = DirectX::XMMatrixRotationZ(v3Rotation.z);
        const auto mtScale = DirectX::XMMatrixScaling(v3Scale.x, v3Scale.y, v3Scale.z);

        mtWorld = mtScale * arrRotation[0] * arrRotation[1] *  arrRotation[2] * mtTranslation;

        return mtWorld;
    }

    std::wstring StringToWString(const std::string& str) {
        std::wstring result;  
        auto len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), NULL, 0);  
        auto buffer = new WCHAR[len + 1];  
        MultiByteToWideChar(CP_ACP, 0, str.c_str(), static_cast<int>(str.size()), buffer, len);  
        buffer[len] = '\0';
        result.append(buffer);  
        delete[] buffer;  
        return result;  
    }

    std::string WStringToString(const std::wstring &wstr) {
        std::string result;  
        auto len = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), static_cast<int>(wstr.size()), NULL, 0, NULL, NULL);  
        auto buffer = new char[len + 1];  
        WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), static_cast<int>(wstr.size()), buffer, len, NULL, NULL);  
        buffer[len] = '\0';  
        result.append(buffer);  
        delete[] buffer;  
        return result; 
    }

    bool RandomBool(float fRate) {
        static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    static std::uniform_real_distribution<> distr(0, 1); // define the range

		return distr(eng) > fRate ? true : false;
    }

    float RandomFloatInRange(float fFrom, float fTo) {
        static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    std::uniform_real_distribution<> distr(fFrom, fTo); // define the range

        return static_cast<float>(distr(eng));
    }

    int RandomIntegerInRange(int nFrom, int nTo) {
        static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    std::uniform_int_distribution<> distr(nFrom, nTo); // define the range

        return distr(eng);
    }

    // reference from https://github.com/MKXJun/DirectX11-With-Windows-SDK/blob/master/22%20Static%20Cube%20Mapping/d3dUtil.cpp
    HRESULT CreateWICTexture2DCubeFromFile(ID3D11Device* d3dDevice,
        ID3D11DeviceContext* d3dDeviceContext,
        std::wstring_view cubeMapFileName,
        ID3D11Texture2D** textureArray,
        ID3D11ShaderResourceView** textureCubeView,
        bool generateMips) {

        if (!d3dDevice || !d3dDeviceContext || !(textureArray || textureCubeView)) {
            return E_INVALIDARG;
        }

        ID3D11Texture2D* srcTex = nullptr;
        ID3D11ShaderResourceView* srcTexSRV = nullptr;

        HRESULT hResult = DirectX::CreateWICTextureFromFile(d3dDevice,
            (generateMips ? d3dDeviceContext : nullptr),
            cubeMapFileName.data(),
            (ID3D11Resource**)&srcTex,
            (generateMips ? &srcTexSRV : nullptr));

        if (FAILED(hResult)) {
            return hResult;
        }

        D3D11_TEXTURE2D_DESC texDesc, texArrayDesc;
        srcTex->GetDesc(&texDesc);

        if (texDesc.Width * 3 != texDesc.Height * 4) {
            SafeRelease(srcTex);
            SafeRelease(srcTexSRV);
            return E_FAIL;
        }

        UINT squareLength = texDesc.Width / 4;
        texArrayDesc.Width = squareLength;
        texArrayDesc.Height = squareLength;
        texArrayDesc.MipLevels = (generateMips ? texDesc.MipLevels - 2 : 1);
        texArrayDesc.ArraySize = 6;
        texArrayDesc.Format = texDesc.Format;
        texArrayDesc.SampleDesc.Count = 1;
        texArrayDesc.SampleDesc.Quality = 0;
        texArrayDesc.Usage = D3D11_USAGE_DEFAULT;
        texArrayDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        texArrayDesc.CPUAccessFlags = 0;
        texArrayDesc.MiscFlags = D3D11_RESOURCE_MISC_TEXTURECUBE;

        ID3D11Texture2D* texArray = nullptr;
        hResult = d3dDevice->CreateTexture2D(&texArrayDesc, nullptr, &texArray);
        if (FAILED(hResult))
        {
            SafeRelease(srcTex);
            SafeRelease(srcTexSRV);
            return hResult;
        }

        D3D11_BOX box;
        box.front = 0;
        box.back = 1;

        for (UINT i = 0; i < texArrayDesc.MipLevels; ++i)
        {
            // +X
            box.left = squareLength * 2;
            box.top = squareLength;
            box.right = squareLength * 3;
            box.bottom = squareLength * 2;
            d3dDeviceContext->CopySubresourceRegion(
                texArray,
                D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_X, texArrayDesc.MipLevels),
                0, 0, 0,
                srcTex,
                i,
                &box);

            // -X
            box.left = 0;
            box.top = squareLength;
            box.right = squareLength;
            box.bottom = squareLength * 2;
            d3dDeviceContext->CopySubresourceRegion(
                texArray,
                D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_X, texArrayDesc.MipLevels),
                0, 0, 0,
                srcTex,
                i,
                &box);

            // +Y
            box.left = squareLength;
            box.top = 0;
            box.right = squareLength * 2;
            box.bottom = squareLength;
            d3dDeviceContext->CopySubresourceRegion(
                texArray,
                D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_Y, texArrayDesc.MipLevels),
                0, 0, 0,
                srcTex,
                i,
                &box);


            // -Y
            box.left = squareLength;
            box.top = squareLength * 2;
            box.right = squareLength * 2;
            box.bottom = squareLength * 3;
            d3dDeviceContext->CopySubresourceRegion(
                texArray,
                D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_Y, texArrayDesc.MipLevels),
                0, 0, 0,
                srcTex,
                i,
                &box);

            // +Z
            box.left = squareLength;
            box.top = squareLength;
            box.right = squareLength * 2;
            box.bottom = squareLength * 2;
            d3dDeviceContext->CopySubresourceRegion(
                texArray,
                D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_POSITIVE_Z, texArrayDesc.MipLevels),
                0, 0, 0,
                srcTex,
                i,
                &box);

            // -Z
            box.left = squareLength * 3;
            box.top = squareLength;
            box.right = squareLength * 4;
            box.bottom = squareLength * 2;
            d3dDeviceContext->CopySubresourceRegion(
                texArray,
                D3D11CalcSubresource(i, D3D11_TEXTURECUBE_FACE_NEGATIVE_Z, texArrayDesc.MipLevels),
                0, 0, 0,
                srcTex,
                i,
                &box);

            squareLength /= 2;
        }


        if (textureCubeView) {
            D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
            viewDesc.Format = texArrayDesc.Format;
            viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
            viewDesc.TextureCube.MostDetailedMip = 0;
            viewDesc.TextureCube.MipLevels = texArrayDesc.MipLevels;

            hResult = d3dDevice->CreateShaderResourceView(texArray, &viewDesc, textureCubeView);
        }

        if (textureArray)
        {
            *textureArray = texArray;
        }
        else
        {
            SafeRelease(texArray);
        }

        SafeRelease(srcTex);
        SafeRelease(srcTexSRV);

        return hResult;
    }
}
