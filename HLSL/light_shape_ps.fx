Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer cbPerObject: register(b0) {
	float4 gLightPos;
    float4 gViewPos; 
};

struct PixelInput {
	float4 PosH  : SV_POSITION;
	float3 PosL : POSITION;
	float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
};

float4 PSMain(PixelInput pin) : SV_Target {
    float3 color = colorMap.Sample(colorSampler, pin.Tex).xyz;

    // ambient
    float3 ambient = 0.05 * color;

    // diffuse
    float3 lightDir = normalize(gLightPos.xyz - pin.PosL.xyz);
    float3 normal = normalize(pin.Normal.xyz);
    float diff = max(dot(lightDir, normal), 0.0);
    float3 diffuse = diff * color;

    // specular
    float3 viewDir = normalize(gViewPos.xyz - pin.PosL.xyz);
    float3 reflectDir = reflect(-lightDir, normal);
    float3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

    float3 specular = color * spec;

    return float4(ambient + diffuse + specular, 1.0f);
}
