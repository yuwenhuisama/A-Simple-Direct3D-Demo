#include "Colors.h"
#include <Windows.h>

namespace Colors {
	DirectX::XMFLOAT4 RandomColor() {
		const DirectX::XMFLOAT4 arrColor[] = {
			White, Black, Red, Green, Blue, Yellow, Cyan, Magenta, Silver, LightSteelBlue,
		};
		static std::random_device rd; // obtain a random number from hardware
	    static std::mt19937 eng(rd()); // seed the generator
	    static std::uniform_int_distribution<> distr(0, std::size(arrColor) - 1); // define the range

		return arrColor[distr(eng)];
	}
}
