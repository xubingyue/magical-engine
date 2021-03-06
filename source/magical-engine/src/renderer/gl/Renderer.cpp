﻿/******************************************************************************
The MIT License (MIT)

Copyright (c) 2014 Jason.lee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/
#include "Renderer.h"
#include "magical-math.h"
#include "Engine.h"
#include "Application.h"
#include "ShaderProgram.h"

#include <vector>

NS_MAGICAL_BEGIN

using std::vector;

//#define kAttrVertexIndex 1
//#define kAttrColorIndex 2

static const char* simple_vertex_shader = R"(
attribute vec4 attr_vertex;
void main( void )
{
	gl_Position = attr_vertex;
}
)";
						
static const char* simple_pixel_shader = R"(
uniform vec4 u_color;
void main( void )
{ 
	gl_FragColor = u_color;
}
)";

static const char* flat_vertex_shader = R"(
uniform mat4 u_mvp_matrix;
attribute vec4 attr_vertex;
attribute vec4 attr_color;
varying vec4 v_color;
void main( void )
{
	v_color = attr_color;
	gl_Position = u_mvp_matrix * attr_vertex;
}
)";
						
static const char* flat_pixel_shader = R"(
varying vec4 v_color;
void main( void )
{ 
	gl_FragColor = v_color;
}
)";

ShaderProgram* s_simple_program = nullptr;
ShaderProgram* s_flat_program = nullptr;

Vector3 rect[4];
Vector3 rect_triangle[4];
Vector3 cube[24];

//Matrix4 m_projection_matrix;
//Matrix4 m_model_matrix;

void Renderer::init( void )
{
	setDefault();
	magicalReturnIfError();

	s_simple_program = ShaderProgram::create( simple_vertex_shader, simple_pixel_shader ).take();
	s_simple_program->build();
	s_simple_program->bindAttribLocation( kAttrVertexIndex, "attr_vertex" );
	s_simple_program->link();

	s_flat_program = ShaderProgram::create( flat_vertex_shader, flat_pixel_shader ).take();
	s_flat_program->build();
	s_flat_program->bindAttribLocation( kAttrVertexIndex, "attr_vertex" );
	s_flat_program->bindAttribLocation( kAttrColorIndex, "attr_color" );
	s_flat_program->link();

	// 2D Rect Vertex
	rect[0].setScalars( -0.5f, -0.5f, 0 );
	rect[1].setScalars( 0.5f, -0.5f, 0 );
	rect[2].setScalars( 0.5f, 0.5f, 0 );
	rect[3].setScalars( -0.5f, 0.5f, 0 );

	// 2D Rect Vertex Triangle strip
	rect_triangle[0].setScalars( -0.5f, -0.5f, 2.0f );
	rect_triangle[1].setScalars( 0.5f, -0.5f, 2.0f );
	rect_triangle[2].setScalars( -0.5f, 0.5f, 2.0f );
	rect_triangle[3].setScalars( 0.5f, 0.5f, 2.0f );

	// font
	cube[0].setScalars( -0.5f, -0.5f, -0.5f );
	cube[1].setScalars( 0.5f, -0.5f, -0.5f );
	cube[2].setScalars( 0.5f, 0.5f, -0.5f );
	cube[3].setScalars( -0.5f, 0.5f, -0.5f );

	// top
	cube[4].setScalars( -0.5f, 0.5f, -0.5f );
	cube[5].setScalars( 0.5f, 0.5f, -0.5f );
	cube[6].setScalars( 0.5f, 0.5f, 0.5f );
	cube[7].setScalars( -0.5f, 0.5f, 0.5f );

	// back
	cube[8].setScalars( -0.5f, -0.5f, 0.5f );
	cube[9].setScalars( -0.5f, 0.5f, 0.5f );
	cube[10].setScalars( 0.5f, 0.5f, 0.5f );
	cube[11].setScalars( 0.5f, -0.5f, 0.5f );

	// bottom
	cube[12].setScalars( -0.5f, -0.5f, -0.5f );
	cube[13].setScalars( -0.5f, -0.5f, 0.5f );
	cube[14].setScalars( 0.5f, -0.5f, 0.5f );
	cube[15].setScalars( 0.5f, -0.5f, -0.5f );

	// left
	cube[16].setScalars( -0.5f, -0.5f, 0.5f );
	cube[17].setScalars( -0.5f, -0.5f, -0.5f );
	cube[18].setScalars( -0.5f, 0.5f, -0.5f );
	cube[19].setScalars( -0.5f, 0.5f, 0.5f );

	// right
	cube[20].setScalars( 0.5f, -0.5f, 0.5f );
	cube[21].setScalars( 0.5f, 0.5f, 0.5f );
	cube[22].setScalars( 0.5f, 0.5f, -0.5f );
	cube[23].setScalars( 0.5f, -0.5f, -0.5f );
}

void Renderer::delc( void )
{
	s_simple_program->release();
	s_flat_program->release();
}

void Renderer::render( void )
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// Simple Program Draw
	/*glUseProgram( s_simple_program->getId() );

	int32_t u_color = s_simple_program->getUniformLocation( "u_color" );
	glUniform4fv( u_color, 1, (GLfloat*)&Color4f::Pink );

	glEnableVertexAttribArray( kAttrVertexIndex );
	glVertexAttribPointer( kAttrVertexIndex, 3, GL_FLOAT, GL_FALSE, 0, &rect_triangle );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );*/


	// Flat Program Draw
	/*glUseProgram( s_flat_program->getId() );

	static float a = 0.0f;
	a += 30.0f * Engine::deltaTime();
	m_model_matrix.setRotationZ( magicalDegToRad( a ) );

	Matrix4 mvp_matrix = m_model_matrix * m_projection_matrix;

	GLint u_mvp_matrix = s_flat_program->getUniformLocation( "u_mvp_matrix" );
	glUniformMatrix4fv( u_mvp_matrix, 1, GL_FALSE, (GLfloat*)&mvp_matrix );

	Color4f colors[4] = {
		Color4f::Pink,
		Color4f::Yello,
		Color4f::Green,
		Color4f::Red };

	glEnableVertexAttribArray( kAttrVertexIndex );
	glEnableVertexAttribArray( kAttrColorIndex );
	glVertexAttribPointer( kAttrVertexIndex, 3, GL_FLOAT, GL_FALSE, 0, &rect_triangle );
	glVertexAttribPointer( kAttrColorIndex, 4, GL_FLOAT, GL_FALSE, 0, colors );
	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );*/



	magicalDebugCheckGLError();
}

void Renderer::resize( int width, int height )
{
	glViewport( 0, 0, width, height );

	//m_projection_matrix.setPerspective( 60.0f, (float)width / (float)height, 0.3f, 1000.0f );

	magicalCheckGLError();
}

void Renderer::setDefault( void )
{
	glClearColor( 0.3f, 0.3f, 0.3f, 1.0f );

	glEnable( GL_DEPTH_TEST );
	glEnable( GL_CULL_FACE );

	magicalCheckGLError();
}

void Renderer::pushRenderChannel( const ViewChannel* channel )
{
	//Application::getWindowSize()
}

NS_MAGICAL_END