#version 450 core

layout (location = 0) in vec4 position;
layout (location = 1) uniform mat4 projection;

void main()
{
	gl_Position = projection * position;
}