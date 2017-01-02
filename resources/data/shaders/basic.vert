#version 450 core

layout (location = 0) uniform mat4 position;
layout (location = 1) uniform mat4 scale;

void main() 
{
	const vec4 quad[6] = vec4[6](
		vec4(-1.0,  1.0, 0.0, 1.0),
		vec4( 1.0,  1.0, 0.0, 1.0),
		vec4( 1.0, -1.0, 0.0, 1.0),

		vec4( 1.0, -1.0, 0.0, 1.0),	
		vec4(-1.0, -1.0, 0.0, 1.0),
		vec4(-1.0,  1.0, 0.0, 1.0)
	);

	gl_Position = quad[gl_VertexID] * scale;
}