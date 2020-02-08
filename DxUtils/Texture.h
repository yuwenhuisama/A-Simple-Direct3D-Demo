#ifndef _H_TEXTURE_
#define _H_TEXTURE_

#include <string>
#include "DxUtils/WicTextureLoader/WICTextureLoader.h"

class Texture {
private:
    ID3D11ShaderResourceView* m_pResourceView = nullptr;
    ID3D11Resource* m_pTexture = nullptr;

public:
    Texture() = default;
    ~Texture();

    ID3D11ShaderResourceView* GetShaderResourceView() const { return m_pResourceView; }
    ID3D11Resource* GetTextureResource() const { return m_pTexture; }

    bool Load(std::wstring& strFilePath);
};

#endif // !_H_TEXTURE_
