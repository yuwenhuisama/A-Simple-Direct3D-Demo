#include "D3DHelper.hpp"
#include <random>

namespace D3DHelper {
    DirectX::XMMATRIX CalcWorldMatrix(const DirectX::XMFLOAT3& v3Translation, const  DirectX::XMFLOAT3& v3Rotation, const  DirectX::XMFLOAT3& v3Scale) {
        DirectX::XMMATRIX mtWorld = DirectX::XMMatrixIdentity();

        const auto mtTranslation = DirectX::XMMatrixTranslation(v3Translation.x, v3Translation.y, v3Translation.z);
        const auto mtRotationX = DirectX::XMMatrixRotationX(v3Rotation.x);
        const auto mtRotationY = DirectX::XMMatrixRotationY(v3Rotation.y);
        const auto mtRotationZ = DirectX::XMMatrixRotationZ(v3Rotation.z);
        const auto mtScale = DirectX::XMMatrixScaling(v3Scale.x, v3Scale.y, v3Scale.z);

        mtWorld = mtScale * mtRotationX * mtRotationY * mtRotationZ * mtTranslation;

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

    bool RandomBool() {
        static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    static std::uniform_real_distribution<> distr(0, 1); // define the range

		return distr(eng) > 0.7f ? true : false;
    }

    float RandomFloatInRange(float fFrom, float fTo) {
        static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    std::uniform_real_distribution<> distr(fFrom, fTo); // define the range

        return distr(eng);
    }

    int RandomIntegerInRange(int nFrom, int nTo) {
        static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    std::uniform_int_distribution<> distr(nFrom, nTo); // define the range

        return distr(eng);
    }
}
