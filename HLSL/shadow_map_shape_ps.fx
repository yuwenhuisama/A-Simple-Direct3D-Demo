struct PixelInput {
	float4 PosH  : SV_POSITION;
};

float4 PSMain(PixelInput pin) : SV_Target {
    return float4(0.0f, 0.0f, 0.0f, 1.0f);
}
