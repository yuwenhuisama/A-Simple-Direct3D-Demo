#ifndef _H_COLORS_
#define _H_COLORS_

#include <DirectXMath.h>
#include <random>

// reference from https://github.com/Ray1024/D3D11Tutorial/blob/946fa79dd7054b3183668f52618cd93ae88c6963/Common/D3D11Util.h
namespace Colors
{
	XMGLOBALCONST DirectX::XMFLOAT4 White     = {1.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Black     = {0.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Red       = {1.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Green     = {0.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Blue      = {0.0f, 0.0f, 1.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Yellow    = {1.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Cyan      = {0.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 Magenta   = {1.0f, 0.0f, 1.0f, 1.0f};

	XMGLOBALCONST DirectX::XMFLOAT4 Silver    = {0.75f, 0.75f, 0.75f, 1.0f};
	XMGLOBALCONST DirectX::XMFLOAT4 LightSteelBlue = {0.69f, 0.77f, 0.87f, 1.0f};

	DirectX::XMFLOAT4 RandomColor();
};

#endif // !_H_COLORS_
