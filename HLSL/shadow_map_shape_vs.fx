cbuffer cbPerObject: register(b0) {
	float4x4 gWorldMatrix; 
	float4x4 gViewMatrix;
	float4x4 gProjMatrix;
};

struct VertexIn {
	float3 Pos    	: POSITION;
	float3 Normal 	: NORMAL;
	float3 Tangent  : TANGENT;
    float2 Tex    	: TEXCOORD0;
};

struct VertexOut {
	float4 PosH  : SV_POSITION;
};

VertexOut VSMain(VertexIn vin)
{
	VertexOut vout;
	
	float4x4 vp = mul(gWorldMatrix, gViewMatrix);
	float4x4 wvp = mul(vp, gProjMatrix);
	
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.Pos, 1.0f), wvp);
    
    return vout;
}
