Texture2D colorMap : register(t0);
SamplerState colorSampler : register(s0);

cbuffer cbPerObject: register(b0) {
	float4 gLightPose;
    float4 gViewPos; 
};

struct PixelInput {
	float4 PosH  : SV_POSITION;
    float4 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
};

float4 PSMain(PixelInput pin) : SV_Target {
    float3 color = colorMap.Sample(colorSampler, pin.Tex).xyz;

    // ambient
    float3 ambient = 0.05 * color;

    // diffuse
    float3 lightDir = normalize(gLightPose - pin.PosH);
    float3 normal = normalize(pin.Normal.xyz);
    float diff = max(dot(lightDir, normal), 0.0);
    float3 diffuse = diff * color;

    // specular
    float3 viewDir = normalize(gViewPos - pin.PosH);
    float spec = 0.0;
    float3 reflectDir = reflect(-lightDir, normal);

    vec3 halfwayDir = normalize(lightDir + viewDir);

    specular = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

    vec3 specular = color * spec;

    return float4(ambient + diffuse + specular, 1.0);
}
