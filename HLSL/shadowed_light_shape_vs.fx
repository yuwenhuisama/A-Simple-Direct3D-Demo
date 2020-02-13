cbuffer cbPerObject: register(b0) {
	float4x4 gWorldMatrix; 
	float4x4 gWorldNormal;
	float4x4 gViewMatrix;
	float4x4 gProjMatrix;

	float4x4 gLightViewMatrix;
	float4x4 gLightProjMatrix;
};

struct VertexIn {
	float3 Pos    	: POSITION;
	float3 Normal 	: NORMAL;
	float3 Tangent  : TANGENT;
    float2 Tex    	: TEXCOORD0;
};

struct VertexOut {
	float4 PosH  : SV_POSITION;
	float3 PosL : POSITION0;
	float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
	float4 PosLightSpaceL : POSITION1;
};

VertexOut VSMain(VertexIn vin)
{
	VertexOut vout;
	
	float4x4 vp = mul(gWorldMatrix, gViewMatrix);
	float4x4 wvp = mul(vp, gProjMatrix);
	
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.Pos, 1.0f), wvp);
	vout.PosL = mul(float4(vin.Pos, 1.0f), gWorldMatrix).xyz;
	vout.Normal = mul(float4(vin.Normal, 1.0f), gWorldNormal).xyz;
	
	float4x4 lvp = mul(gWorldMatrix, gLightViewMatrix);
	float4x4 lwvp = mul(lvp, gLightProjMatrix);
	vout.PosLightSpaceL = mul(float4(vin.Pos, 1.0f), lwvp);

	// Just pass vertex color into the pixel shader.
    vout.Tex = vin.Tex;
    
    return vout;
}
