cbuffer cbPerObject: register(b0) {
	float4x4 gWorldViewProj; 
};

struct VertexIn {
	float3 Pos    	: POSITION;
	float3 Normal 	: NORMAL;
	float3 Tangent  : TANGENT;
    float2 Tex    	: TEXCOORD0;
};

struct VertexOut {
	float4 PosH  : SV_POSITION;
	float4 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
};

VertexOut VSMain(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.Pos, 1.0f), gWorldViewProj);
	vout.Normal = mul(float4(vin.Normal, 1.0f), gWorldViewProj);

	// Just pass vertex color into the pixel shader.
    vout.Tex = vin.Tex;
    
    return vout;
}
