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
#include "Application.h"
#include "Engine.h"
#include "InputSystem.h"

#include <windows.h>
#include "win32/gl/glew/glew.h"
#include "win32/gl/glfw3/glfw3.h"

NS_MAGICAL_BEGIN

static void win32ErrorCallBack( int err_id, const char* error_desc );
static void win32MouseButtonCallBack( GLFWwindow* window, int button, int action, int modify );
static void win32MouseMoveCallBack( GLFWwindow* window, double x, double y );
static void win32MouseScrollCallBack( GLFWwindow* window, double x, double y );
static void win32CharCallBack( GLFWwindow* window, unsigned int character );
static void win32KeyCallBack( GLFWwindow* window, int key, int scancode, int action, int mods );
static void win32WindowPosCallBack( GLFWwindow* windows, int x, int y );
static void win32FrameBufferSizeCallBack( GLFWwindow* window, int w, int h );
static void win32WindowSizeCallBack( GLFWwindow* window, int width, int height );

static GLFWwindow* s_window = nullptr;
static LARGE_INTEGER s_interval_win32;
static double s_interval;
static bool s_window_resizable = true;
static Size s_window_size = Size::Zero;
static std::string s_window_title = "magical-engine";

void Application::run( MainDelegate mainDelegate )
{
	mainDelegate();
	magicalShowLastError();
	magicalReturnIfError();

	LARGE_INTEGER freq;
    LARGE_INTEGER last;
    LARGE_INTEGER now;

	QueryPerformanceFrequency( &freq );
	QueryPerformanceCounter( &last );

	while( !glfwWindowShouldClose( s_window ) )
	{
		QueryPerformanceCounter( &now );
		if( now.QuadPart - last.QuadPart > s_interval_win32.QuadPart )
		{
			last.QuadPart = now.QuadPart;

			Engine::mainLoop();
			glfwSwapBuffers( s_window );

#ifdef MAGICAL_DEBUG
			magicalShowLastError();
			magicalReturnIfError();
#endif
			glfwPollEvents();
		}
		else
		{
			Sleep( 0 );
		}
	}
}

void Application::setInterval( double interval )
{
	LARGE_INTEGER freq;
	QueryPerformanceFrequency( &freq );
	s_interval_win32.QuadPart = (LONGLONG) ( interval * freq.QuadPart );

	s_interval = interval;
}

double Application::getInterval( void )
{
	return s_interval;
}

void Application::setResizable( bool resizable )
{
	s_window_resizable = resizable;
	glfwWindowHint( GLFW_RESIZABLE, resizable );
}

bool Application::isResizable( void )
{
	return s_window_resizable;
}

void Application::setWindowSize( int width, int height )
{
	s_window_size.w = width;
	s_window_size.h = height;
	glfwSetWindowSize( s_window, s_window_size.w, s_window_size.h );
}

void Application::setWindowSize( const Size& size )
{
	s_window_size = size;
	glfwSetWindowSize( s_window, s_window_size.w, s_window_size.h );
}

const Size& Application::getWindowSize( void )
{
	return s_window_size;
}

void Application::setWindowTitle( const char* title )
{
	s_window_title = title;
	glfwSetWindowTitle( s_window, title );
}

void Application::swapBuffers( void )
{
	glfwSwapBuffers( s_window );
}

void Application::exit( void )
{
	glfwSetWindowShouldClose( s_window, 1 );
}

void Application::initWindow( void )
{
	glfwSetErrorCallback( win32ErrorCallBack );
	glfwInit();
	magicalReturnIfError();

	setInterval( 1.0 / 60 );
	setResizable( true );
	glfwDefaultWindowHints();

	s_window_size.w = 960;
	s_window_size.h = 640;

	s_window = glfwCreateWindow( s_window_size.w, s_window_size.h, s_window_title.c_str(), nullptr, nullptr );
	magicalReturnIfError();

	glfwMakeContextCurrent( s_window );
	magicalReturnIfError();

	glfwSetMouseButtonCallback( s_window, win32MouseButtonCallBack );
	glfwSetCursorPosCallback( s_window, win32MouseMoveCallBack );
	glfwSetScrollCallback( s_window, win32MouseScrollCallBack );
	glfwSetCharCallback( s_window, win32CharCallBack );
	glfwSetKeyCallback( s_window, win32KeyCallBack );
	glfwSetWindowPosCallback( s_window, win32WindowPosCallBack );
	glfwSetFramebufferSizeCallback( s_window, win32FrameBufferSizeCallBack );
	glfwSetWindowSizeCallback( s_window, win32WindowSizeCallBack );

	Engine::resize( s_window_size.w, s_window_size.h );
}

void Application::delcWindow( void )
{
	glfwTerminate();
}

void Application::initRenderContext( void )
{
	const GLubyte* gl_version = glGetString( GL_VERSION );
	if( atof( (const char*) gl_version ) < 1.5 )
	{
		magicalFormat( "OpenGL 1.5 or higher is required (your version is %s). Please upgrade the driver of your video card.", gl_version );
		magicalSetLastErrorA( magicalGetBuffer() );
		magicalLogLastError();
		return;
	}

	GLenum result = glewInit();
	if( result != GLEW_OK )
	{
		magicalFormat( "%s %s", "Init glew failed.", (char*)glewGetErrorString( result ) );
		magicalSetLastErrorA( magicalGetBuffer() );
		magicalLogLastError();
		return;
	}

	if( GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader )
	{
		//log( "Ready for GLSL" );
	}
	else
	{
		//log( "Not totally ready :(" );
	}

	if( glewIsSupported( "GL_VERSION_2_0" ) )
	{
		//log("Ready for OpenGL 2.0");
	}
	else
	{
		//log("OpenGL 2.0 not supported");
	}
}

void Application::delcRenderContext( void )
{

}

static void win32ErrorCallBack( int err_id, const char* error_desc )
{
	magicalSetLastErrorA( error_desc );
	magicalLogLastError();

	magicalLog( "win32ErrorCallBack" );
}

static void win32MouseButtonCallBack( GLFWwindow* window, int button, int action, int modify )
{
	Input::onMouseButtonEvent( button, action );

	stringstream ss;
	ss << "Button:" << button << "  Action:" << action << "  Modify:" << modify; 

	magicalLog( ss.str().c_str() );
	magicalLog( "win32MouseButtonCallBack" );
}

static void win32MouseMoveCallBack( GLFWwindow* window, double x, double y )
{
	Input::onMouseEvent( x, y );
	//magicalLog( "win32MouseMoveCallBack" );
}

static void win32MouseScrollCallBack( GLFWwindow* window, double x, double y )
{
	stringstream ss;
	ss << "Scroll: x=" << x << "  y=" << y;

	magicalLog( ss.str().c_str() );
	//magicalLog( "win32MouseScrollCallBack" );
}

static void win32CharCallBack( GLFWwindow* window, unsigned int character )
{
	//magicalLog( "win32CharCallBack" );
}

static void win32KeyCallBack( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	Input::onKeyEvent( (KeyCode) key, (KeyAction) action );
	magicalLog( "win32KeyCallBack" );
}

static void win32WindowPosCallBack( GLFWwindow* windows, int x, int y )
{
	//magicalLog( "win32WindowPosCallBack" );
}

static void win32FrameBufferSizeCallBack( GLFWwindow* window, int w, int h )
{
	//magicalLog( "win32FrameBufferSizeCallBack" );
}

static void win32WindowSizeCallBack( GLFWwindow* window, int width, int height )
{
	s_window_size.w = width;
	s_window_size.h = height;

	Engine::resize( width, height );
	magicalLog( "win32WindowSizeCallBack" );
}

NS_MAGICAL_END