#version 450 core

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

	gl_Position = quad[gl_VertexID];
}