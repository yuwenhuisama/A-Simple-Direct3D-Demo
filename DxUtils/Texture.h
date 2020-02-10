#ifndef _H_TEXTURE_
#define _H_TEXTURE_

#include <string>
#include "DxUtils/WicTextureLoader/WICTextureLoader.h"

class Texture {
private:
    ID3D11ShaderResourceView* m_pResourceView = nullptr;
    ID3D11Texture2D* m_pTexture = nullptr;

public:
    Texture() = default;
    ~Texture();

    ID3D11ShaderResourceView* GetShaderResourceView() const { return m_pResourceView; }
    ID3D11Texture2D* GetTextureResource() const { return m_pTexture; }

    bool Load(std::wstring_view wstrFilePath);
    bool LoadCube(std::wstring_view wstrFilePath);
};

#endif // !_H_TEXTURE_
