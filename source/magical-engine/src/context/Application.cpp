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
#include "Renderer.h"
//#include "AssetsSystem.h"
//#include "LuaSystem.h"
#include "LogSystem.h"
#include "InputSystem.h"

NS_MAGICAL_BEGIN

void Application::init( void )
{
	magicalStartObjectsListener( kEngineObjectsListener );

	Log::init();
	magicalShowLastError();
	magicalReturnIfError();

	/*Assets::Init();
	magicalShowLastError();
	magicalReturnIfError();*/

	Input::init();
	magicalShowLastError();
	magicalReturnIfError();

	/*Lua::init();
	magicalShowLastError();
	magicalReturnIfError();*/

	initWindow();
	magicalShowLastError();
	magicalReturnIfError();

	initRenderContext();
	magicalShowLastError();
	magicalReturnIfError();

	Engine::init();
	magicalShowLastError();
	magicalReturnIfError();

	Renderer::init();
	magicalShowLastError();
	magicalReturnIfError();

	std::string msg;
	msg += "<init>\n";

#ifdef MAGICAL_DEBUG
	msg += "  [debug model]: true\n";
#else
	msg += "  [debug model]: false\n";
#endif

	msg += "<init>\n";
	magicalLog( msg.c_str() );
}

void Application::delc( void )
{
	Renderer::delc();
	magicalShowLastError();
	magicalReturnIfError();

	Engine::delc();
	magicalShowLastError();
	magicalReturnIfError();

	delcRenderContext();
	magicalShowLastError();
	magicalReturnIfError();

	delcWindow();
	magicalShowLastError();
	magicalReturnIfError();

	/*Lua::delc();
	magicalShowLastError();
	magicalReturnIfError();*/

	Input::delc();
	magicalShowLastError();
	magicalReturnIfError();

	/*Assets::Delc();
	magicalShowLastError();
	magicalReturnIfError();*/

	std::stringstream ss;
	ss << "C: " << magicalGetObjectsConstructCount( kEngineObjectsListener ) << "  ";
	ss << "D: " << magicalGetObjectsDestructCount( kEngineObjectsListener ) << "\n";
	magicalLog( ss.str().c_str() );

	magicalEndObjectsListener( kEngineObjectsListener );

	Log::delc();
	magicalShowLastError();
	magicalReturnIfError();
}

NS_MAGICAL_END