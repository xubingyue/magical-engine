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
#ifndef __ASSETS_SYSTEM_H__
#define __ASSETS_SYSTEM_H__

#include "platform-macros.h"
#include "common.h"
#include "Data.h"

NS_MAGICAL_BEGIN

class AssetsSystem
{
public:
	static void Init( void );
	static void Delc( void );

public:
	static void getFileData( void );
	static void SetDefaultAssetsPath( void );
	static void SetAssetsPath( const char* path );
	static std::string GetAssetsPath( void );
	static std::string GetAssetsAbsFilename( const char* file );
	static bool IsFileExist( const char* file );
	static Ptr<Data> GetFileData( const char* file );
};

NS_MAGICAL_END

#endif //__ASSETS_SYSTEM_H__