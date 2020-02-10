TextureCube colorMap : register(t0);
SamplerState colorSampler : register(s0);

struct PixelInput {
	float4 PosH  : SV_POSITION;
    float3 PosL : POSITION;
};

float4 PSMain(PixelInput psIn) : SV_Target {
    return colorMap.Sample(colorSampler, psIn.PosL);
    // return float4(0.0f, 0.0f, 0.0f, 1.0f);
}
