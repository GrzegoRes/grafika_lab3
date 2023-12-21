/*
 * Copyright © 2014 .. Mariusz Szwoch v.2023
 *   based on 
 * Copyright © 2012-2013 Graham Sellers
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
//------------------------- Headers ------------------------
#include <stdio.h> // sprintf()
#include <sb6.h> // Library by Graham Sellers
#include <shader.h>
#pragma comment(lib, "legacy_stdio_definitions.lib") // For backward compatibility
extern "C" { FILE __iob_func[ 3 ] = { *stdin,*stdout,*stderr }; } // For backward compatibility

//------------------------- Const parameters ------------------------
// 36, 41. Set up the number of shader programs ...
#define SHADER_PROGRAM_NUM 1 // the number of shader programs
#define INNER_TESS_LEVEL_NUM 2
#define OUTER_TESS_LEVEL_NUM 4
#define MIN_TESS_LEVEL 1 // minimum tesselation level
#define MAX_TESS_LEVEL 60 // maximum tesselation level
//------------------------- The application class ------------------------
class TesselationModesApp : public sb6::application
{
private:
	// Fields
	int program_index; // index to switch current program (0..SHADER_PROGRAM_NUM-1)
	GLuint program[ SHADER_PROGRAM_NUM ]; // IDs for shader program objects
	GLuint vao; // IDs for vertex array object
	GLfloat TessLevelInner[ INNER_TESS_LEVEL_NUM ]; // inner tesselation levels
	GLfloat TessLevelOuter[ OUTER_TESS_LEVEL_NUM ]; // outer tesselation levels
	// Methods
	virtual void startup(); // Do the startup
	virtual void shutdown(); // Do the shutdown
	virtual void render( double currentTime ); // Render the scene
	void IncreaseTesselationLevel( GLfloat &level ); // Increase the tesselation level
	void DecreaseTesselationLevel( GLfloat &level ); // Decrease the tesselation level
	void init(); // Initialize the program
	void onKey( int key, int action ); // Key stroke handler
	void UpdateTitle( void ); // Update the title bar
public:
	TesselationModesApp() : program_index( 0 ) {}
};
//
//------------------------- Initialize the program ------------------------
void TesselationModesApp::init()
{
	sb6::application::init(); // initilize sb6 application base class
	UpdateTitle();

	// 46. Initialize tesselation inner & outer levels ...


}
//-------------------------Do the startup ------------------------
static const char *tess_shaders_names[] =
{ // TCS & TES shaders' names
	"Quads", "Triangles", "Isolines"
};
void TesselationModesApp::startup()
{
	GLuint vs, fs;
	// 4. Load vertex shader 
	// ...
	vs = sb6::shader::load("Shaders/TessDemoQuad.vs", GL_VERTEX_SHADER);

	// 5. Compile vertex shader 
	// ...
	glCompileShader(vs);

	// 6. Load fragment shader 
	// ...
	fs = sb6::shader::load("Shaders/TessDemoQuad.fs", GL_FRAGMENT_SHADER);


	// 7. Compile fragment shader 
	// ...
	glCompileShader(fs);


	for ( int i = 0; i < SHADER_PROGRAM_NUM; i++ )
	{
		GLuint tcs, tes; // tcs & tes shader objects
		char shaderName[ 200 ];

		// 21. Load tesselation control shader ...
		sprintf(shaderName, "Shaders/%s.tcs", tess_shaders_names[i]);
		tcs = sb6::shader::load(shaderName, GL_TESS_CONTROL_SHADER);


		// 22. Compile tesselation control shader ...
		glCompileShader(tcs);

		// 23. Load tesselation evaluation shader ...
		tes = sb6::shader::load(shaderName, GL_TESS_EVALUATION_SHADER);


		// 24. Compile tesselation evaluation shader ...
		glCompileShader(tes);

		// 8. Create the i-th program ...
		program[i] = glCreateProgram();

		// 9. Atach VS & FS shaders ...
		glAttachShader(program[i], vs);
		glAttachShader(program[i], fs);


		// 25. Atach TCS & TES shaders ...
		glAttachShader(program[i], tcs);
		glAttachShader(program[i], tes);


		// 10. Link the program ...
		glLinkProgram(program[i]);

		// 26. Delete TCS and TES shaders ...
		glDeleteShader(tcs);
		glDeleteShader(tes);

	}
	
	// 11. Delete VS and FS shaders
	glDeleteShader(vs);
	glDeleteShader(fs);

	// 12. Generate Vertex Array Object (vao)
	glGenVertexArrays(1, &vao);

	// 13. Bind actual vao
	glBindVertexArray(vao);

	// 14. Set patch elements' number
	glPatchParameteri(GL_PATCH_VERTICES, 4);

	// 15. Set line rendering mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}
//------------------------- Do the shutdown ------------------------
void TesselationModesApp::shutdown()
{
	// 16. Delete VAO object
	glDeleteVertexArrays(1, &vao);

	// 17. Delete SHADER_PROGRAM_NUM program objects
	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		glDeleteProgram(program[i]);
	}
}
//------------------------- Render the scene ------------------------
void TesselationModesApp::render( double currentTime )
{
	static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glClearBufferfv( GL_COLOR, 0, black );

	// 18. Use actual program ...
	glUseProgram(program[program_index]);

	GLint uniformLoc;

	// 47. Get location of a TessLevelInner ...


	// 48. Set the parameter's value ...



	// 49. Get location of a TessLevelInner & set the parameter's value...




	// 19. Draw an object ...
	glDrawArrays(GL_PATCHES, 0, 4);
}
//-------------------------Key stroke handler ------------------------
void TesselationModesApp::onKey( int key, int action )
{ // Key stroke handler
	if ( !action )
		return;
	switch ( key )
	{
		case ' ': 
			program_index = (program_index + 1) % SHADER_PROGRAM_NUM;
			break;
		// 52. Increase & decrease tesselation levels according to different keystrokes
		case 'Q': 

			break;
		case 'A': 

			break;
		case 'W': 

			break;
		case 'S': 

			break;
		case 'E': 

			break;
		case 'D': 

			break;
		case 'R': 

			break;
		case 'F': 

			break;
		case 'T': 

			break;
		case 'G': 

			break;
		case 'Y': 

			break;
		case 'H': 

			break;
	}
	UpdateTitle();
}
//-------------------------Increase the tesselation level ------------------------
void TesselationModesApp::IncreaseTesselationLevel( GLfloat &level ) 
{
	if ( level < MAX_TESS_LEVEL )
		level++;
}
//-------------------------Decrease the tesselation level ------------------------
void TesselationModesApp::DecreaseTesselationLevel( GLfloat &level )
{
	if ( level > MIN_TESS_LEVEL )
		level--;
}
//-------------------------Update the title bar ------------------------
void TesselationModesApp::UpdateTitle( void )
{
	char title[ 128 ]; // content of the application's title bar
	sprintf( title, "Tessellation Modes by Anonim [%s]", tess_shaders_names[ program_index ] );
	memcpy( info.title, title, sizeof( title ) );
	glfwSetWindowTitle(info.title);
}


DECLARE_MAIN(TesselationModesApp)
