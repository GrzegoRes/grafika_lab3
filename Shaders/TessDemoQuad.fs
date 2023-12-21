// simple.fs
// Just use white color for all pot-background primitives

#version 420 core // OpenGL 4.20+
out vec4 color;

void main( void )
{
	//3.  Set white output color ...
	color = vec4(1.0, 1.0, 1.0, 1.0);
}
