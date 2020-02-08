Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

struct PixelInput
{
	float4 PosH  : SV_POSITION;
    float2 Tex : TEXCOORD0;
};

float4 PSMain(PixelInput pin) : SV_Target
{
    return colorMap.Sample(colorSampler, pin.Tex);
}
