#version 400

out vec3 FragColor;

in vec2 UV;

in vec3 Normals;


uniform sampler2D TextureData;

uniform bool TextureMapping;

uniform bool NormalRendering;


uniform vec3 AmbientLight;

uniform vec3 DiffuseLight;

uniform vec3 SpecularLight;

uniform vec3 LightPosition;

uniform vec3 LightView;

in vec3 FragPos;

uniform vec3 AmbientMaterial;

uniform vec3 DiffuseMaterial;

uniform vec3 SpecularMaterial;

uniform float Shininess;

uniform bool PointLight;

uniform bool SpotLight;

uniform bool DirectionalLight;

uniform float AttenuationC1;

uniform float AttenuationC2;

uniform float AttenuationC3;

uniform float InnerAngle;

uniform float OuterAngle;

uniform float FallOff;

vec3 Specular;

vec3 ComputePointLight()
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

	//Attenuation
	float distance = length(LightPosition - FragPos);
	float attenuation = min(1.0 / (AttenuationC1 + AttenuationC2 * distance + AttenuationC3 * (distance * distance)), 1.0);

	Ambient *= attenuation;
	Diffuse *= attenuation;
	Specular *= attenuation;

	return Ambient + Diffuse;
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

	return Ambient + Diffuse;
}

vec3 ComputeDirectionalLight()
{
	//Ambient
	vec3 Ambient = AmbientLight * AmbientMaterial;

	//Diffuse
	vec3 norm = normalize(Normals);
	vec3 LightDirection = normalize(LightPosition);
	float diff = max(dot(norm, LightDirection), 0.0);
	vec3 Diffuse = DiffuseLight * (diff * DiffuseMaterial);
	
	//Specular
	vec3 ViewDirection = normalize(-FragPos);
	vec3 ReflectDirection = reflect(-LightDirection, norm);
	float spec = pow(max(dot(ViewDirection, ReflectDirection), 0.0), Shininess);
	Specular = SpecularLight * (spec * SpecularMaterial);

	return Ambient + Diffuse;
}

void main()
{	
	vec3 result;

	if(PointLight)
		result = ComputePointLight();
		
	else if(SpotLight)
		result = ComputeSpotLight();

	else if(DirectionalLight)
		result = ComputeDirectionalLight();

	if(NormalRendering)
		FragColor = vec3(1.0f, 1.0f, 1.0f);

	else if(TextureMapping)
		FragColor = result * vec3(UV.x, UV.y, 0.0f) + Specular;

	else
		FragColor = result * texture(TextureData, UV).rgb + Specular; 
}