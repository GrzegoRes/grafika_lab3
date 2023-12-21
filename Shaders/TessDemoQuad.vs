// Tesselation.vs
// Supporting input patch for rendering pipeline

#version 420 core // OpenGL 4.20+

void main( void )
{
	const vec4 vertices[] = vec4[]
	(
		vec4(  0.4, -0.4, 0.5, 1.0 ), 
		vec4( -0.4, -0.4, 0.5, 1.0 ), 
		vec4(  0.4,  0.4, 0.5, 1.0 ), 
		vec4( -0.4,  0.4, 0.5, 1.0 ) 
	);
	// 2. Set vertex position using vertices[] indexed by gl_VertexID ...
	gl_Position = vertices[gl_VertexID];
}
