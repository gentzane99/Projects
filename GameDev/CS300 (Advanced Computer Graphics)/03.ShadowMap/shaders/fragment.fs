#version 400

out vec3 FragColor;

in vec2 UV;
in vec3 Normals;
in vec3 FragPos;
in vec4 FragPosLightSpace;

uniform sampler2D TextureData;
uniform sampler2D ShadowMap;

uniform bool NormalRendering;

uniform vec3 AmbientLight;
uniform vec3 DiffuseLight;
uniform vec3 SpecularLight;

uniform vec3 LightPosition;
uniform vec3 LightView;

uniform vec3 AmbientMaterial;
uniform vec3 DiffuseMaterial;
uniform vec3 SpecularMaterial;


uniform float Shininess;

uniform float AttenuationC1;
uniform float AttenuationC2;
uniform float AttenuationC3;

uniform float InnerAngle;
uniform float OuterAngle;

uniform float FallOff;

vec3 Specular;

uniform float Bias;
uniform int PCFSamples;
uniform mat4 LightSpaceMatrix;
uniform mat4 W;

float ComputePCFShadow(vec3 ProjCoordinates, float PositionDepth)
{
	vec2 TexelOffset = 1.0 / textureSize(ShadowMap, 0);
	int Neighbor = PCFSamples;

	int SampleCount = 0;
	float Visibility = 0.0;

	for(int x = -Neighbor; x <= Neighbor; x++)
	{
		for(int y = -Neighbor; y <= Neighbor; y++)
		{
			float ShadowDepth = texture(ShadowMap, ProjCoordinates.xy + TexelOffset * vec2(x,y)).r;
			Visibility += ((ShadowDepth - PositionDepth) > 0.0) ? 1.0 : 0.0;
			SampleCount++;
		}
	}

	return Visibility / SampleCount;
}

float ComputeShadow()
{
	//Compute FragPosLightSpace
	vec4 FragPosLightSpace = LightSpaceMatrix * W * vec4(FragPos, 1.0);

	//Perspective division
	vec3 ProjCoordinates = FragPosLightSpace.xyz / FragPosLightSpace.w;

	//Transform to 1,0 range
	ProjCoordinates = ProjCoordinates * 0.5 + 0.5;

	//Compute the current depth
	float PositionDepth = (FragPosLightSpace.z + Bias) / FragPosLightSpace.w;
	
	//Compute the PCF
	return ComputePCFShadow(ProjCoordinates, PositionDepth);
}

vec3 ComputeSpotLight()
{
	//Ambient
	vec3 Ambient = AmbientLight * AmbientMaterial;

	//Diffuse
	vec3 norm = normalize(Normals);
	vec3 LightDirection = normalize(LightPosition - FragPos);
	float diff = max(dot(norm, LightDirection), 0.0);
	vec3 Diffuse = DiffuseLight * (diff * DiffuseMaterial);
	
	//Specular
	vec3 ViewDirection = normalize(-FragPos);
	vec3 ReflectDirection = 2 * dot(norm, LightDirection) * norm - LightDirection;
	float spec = max(pow(dot(ViewDirection, ReflectDirection), Shininess), 0.0);
	Specular = SpecularLight * (spec * SpecularMaterial);

	//SpotLight
	float Alpha = dot(normalize(LightView), -LightDirection);
	float SpotLightEffect = (Alpha - OuterAngle) /  (InnerAngle - OuterAngle);
	SpotLightEffect = pow(SpotLightEffect, FallOff);
	SpotLightEffect = clamp(SpotLightEffect, 0.0, 1.0);

	Ambient *= SpotLightEffect;
	Diffuse *= SpotLightEffect;
	Specular *= SpotLightEffect;

	//Attenuation
	float distance = length(LightPosition - FragPos);
	float attenuation = min(1.0 / (AttenuationC1 + AttenuationC2 * distance + AttenuationC3 * (distance * distance)), 1.0);

	Ambient *= attenuation;
	Diffuse *= attenuation;
	Specular *= attenuation;

	return (Ambient +  ComputeShadow() * (Diffuse + Specular)) * texture(TextureData, UV).rgb;
}

void main()
{	
	if(NormalRendering)
		FragColor = vec3(1.0f, 1.0f, 1.0f);
	else
		FragColor = ComputeSpotLight(); 
}