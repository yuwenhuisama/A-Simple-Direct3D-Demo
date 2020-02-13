Texture2D colorMap : register(t0);
Texture2D shadowMap : register(t1);
SamplerState colorSampler : register(s0);

cbuffer cbPerObject: register(b0) {
	float4 gLightPos;
    float4 gViewPos; 
};

struct PixelInput {
	float4 PosH  : SV_POSITION;
	float3 PosL : POSITION0;
	float3 Normal : NORMAL;
    float2 Tex : TEXCOORD0;
    float4 PosLightSpaceL : POSITION1;
};

float CalculateShadow(PixelInput pin) {
    float2 projCoords;
    projCoords.x = (pin.PosLightSpaceL.x / pin.PosLightSpaceL.w) * 0.5 + 0.5;
    projCoords.y = (pin.PosLightSpaceL.y / pin.PosLightSpaceL.w) * (-0.5) + 0.5;

    float closestDepth = shadowMap.Sample(colorSampler, projCoords).r;
    float currentDepth = pin.PosLightSpaceL.z / pin.PosLightSpaceL.w;

    // float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;
    // float3 normal = normalize(pin.Normal);
    // float3 lightDir = normalize(gLightPos.xyz - pin.PosLightSpaceL.xyz);

    // float bias = max(0.01 * (1.0 - dot(normal, lightDir)), 0.001);
    float bias = -0.001;
    float shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;

    if (currentDepth > 1.0) {
        shadow = 0.0;
    }

    return shadow;
}

float4 PSMain(PixelInput pin) : SV_Target {
    float3 color = colorMap.Sample(colorSampler, pin.Tex).xyz;
    float3 lightColor = float3(1.0, 1.0, 1.0);

    // ambient
    float3 ambient = 0.1 * color;

    // diffuse
    float3 lightDir = normalize(gLightPos.xyz - pin.PosL.xyz);
    float3 normal = normalize(pin.Normal.xyz);
    float diff = max(dot(lightDir, normal), 0.0);
    float3 diffuse = diff * lightColor;

    // specular
    float3 viewDir = normalize(gViewPos.xyz - pin.PosL.xyz);
    float3 reflectDir = reflect(-lightDir, normal);
    float3 halfwayDir = normalize(lightDir + viewDir);

    float spec = pow(max(dot(normal, halfwayDir), 0.0), 16.0);

    float3 specular = spec * lightColor;

    float shadow = CalculateShadow(pin);
    // float shadow = 0.0;
    float3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    return float4(lighting, 1.0);
    // float depth = shadowMap.Sample(colorSampler, pin.Tex).x;
    // return float4(depth, depth, depth, 1.0);
}
