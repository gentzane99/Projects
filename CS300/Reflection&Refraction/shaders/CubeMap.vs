#version 400

layout(location = 0) in vec4 vPosition;

out vec3 UV;

uniform mat4 projection;
uniform mat4 view;

void main()
{  
	UV = vec3(vPosition);
	gl_Position = (projection * view * vPosition).xyww;   
}