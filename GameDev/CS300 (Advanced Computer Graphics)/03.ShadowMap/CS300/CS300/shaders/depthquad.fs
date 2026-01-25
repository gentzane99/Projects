#version 400

out vec3 FragColor;

in vec2 UV;

uniform sampler2D DepthMap;
uniform float ShadowMapContrast;

void main()
{
	float DepthValue = texture(DepthMap, UV).r;

	FragColor = vec3(DepthValue);

	if(DepthValue!=1.0)
		FragColor *= ShadowMapContrast;

	
}