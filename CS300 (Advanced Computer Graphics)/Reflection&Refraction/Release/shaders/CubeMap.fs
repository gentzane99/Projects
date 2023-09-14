#version 400

out vec3 FragColor;

in vec3 UV;

uniform samplerCube Skybox;

void main()
{
	FragColor = texture(Skybox, UV).rgb;
}