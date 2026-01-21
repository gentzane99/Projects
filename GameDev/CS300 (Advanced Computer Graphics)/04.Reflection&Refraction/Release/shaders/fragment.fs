#version 400

out vec3 FragColor;

in vec2 UV;
in vec3 NormalsWorld;
in vec3 PositionWorld;

uniform sampler2D TextureData;
uniform samplerCube EnvironmentMap;

uniform float RefractionIndex;
uniform int RenderMode;

uniform vec3 CameraPositionWorld;

void main()
{	
	vec3 L = normalize(PositionWorld - CameraPositionWorld);
	vec3 N = normalize(NormalsWorld);

	vec3 Reflection = reflect(L, N);
	vec3 Refraction = refract(L, N, 1.0f / RefractionIndex);

	if(RenderMode == 0)
		FragColor = texture(TextureData, UV).rgb;

	else if(RenderMode == 1)
		FragColor = texture(EnvironmentMap, normalize(Reflection)).rgb;

	else if(RenderMode == 2)
		FragColor = texture(EnvironmentMap, normalize(Refraction)).rgb;
}