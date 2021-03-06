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
#include "Utils.h"
#include <chrono>

NS_MAGICAL_BEGIN

int64_t TimeUtils::currentMicroseconds( void )
{
	using namespace ::std::chrono;
	system_clock::duration scd = system_clock::now().time_since_epoch();
	microseconds::rep now = duration_cast<microseconds>( scd ).count();
	return now;
}

int64_t TimeUtils::currentSeconds( void )
{
	using namespace ::std::chrono;
	system_clock::duration scd = system_clock::now().time_since_epoch();
	return scd.count();
}

bool FileUtils::isAbsPath( const char* path )
{
	magicalAssert( path, "should not be nullptr." );

#ifdef MAGICAL_WIN32
	if( strlen( path ) > 2
		&& ((path[0] >= 'a' && path[0] <= 'z') 
		|| ( path[0] >= 'A' && path[0] <= 'Z'))
		&& ( path[1] == ':') )
	{
		return true;
	}
	return false;
#endif
}

string FileUtils::toUnixPath( const char* path )
{
	magicalAssert( path, "should not be nullptr." );

	string ret = path;
	int len = ret.length();
    for( int i = 0; i < len; ++i )
    {
        if( ret[i] == '\\' )
        {
            ret[i] = '/';
        }
    }
    return ret;
}

NS_MAGICAL_END