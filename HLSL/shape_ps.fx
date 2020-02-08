struct PixelInput
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

float4 PSMain(PixelInput pin) : SV_Target
{
    return pin.Color;
    // return float4(0, 0, 0, 1.0f);
}
