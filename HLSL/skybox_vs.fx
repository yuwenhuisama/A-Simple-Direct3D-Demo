cbuffer cbPerObject: register(b0) {
	float4x4 gWorldViewProj; 
};

struct VertexIn {
	float3 Pos : POSITION;
};

struct VertexOut {
	float4 PosH  : SV_POSITION;
    float3 PosL : POSITION;
};

VertexOut VSMain(VertexIn vsIn) {
    VertexOut vsOut;
    vsOut.PosL = vsIn.Pos;
    // vsOut.PosH = mul(float4(vsIn.Pos, 1.0f), gWorldViewProj);
    vsOut.PosH = mul(float4(vsIn.Pos, 1.0f), gWorldViewProj).xyww;

    return vsOut;
}
