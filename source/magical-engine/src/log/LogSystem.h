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
#ifndef __LOG_SYSTEM_H__
#define __LOG_SYSTEM_H__

#include "magical-macros.h"
#include "Common.h"

#ifndef MAGICAL_DEBUG
#define magicalLog( txt )
#else
#define magicalLog( txt ) ::magical::Log::writeLine( ::magical::Log::Debug, txt )
#endif

#define DEBUG_LOG_FILE "magical-Log-debug.log"
#define WARNING_LOG_FILE "magical-Log-warning.log"
#define ERROR_LOG_FILE "magical-Log-error.log"

NS_MAGICAL_BEGIN

class Log
{
public:
	enum : int 
	{
		Debug = 0,
		Warning = 1,
		Error = 2,
	};

public:
	static void init( void );
	static void delc( void );

public:
	static void write( int level, const char* txt );
	static void writeLine( int level, const char* txt );
};

NS_MAGICAL_END

#endif //__LOG_SYSTEM_H__