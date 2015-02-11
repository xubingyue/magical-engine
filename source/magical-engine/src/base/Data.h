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
#ifndef __DATA_H__
#define __DATA_H__

#include "magical-macros.h"
#include "Common.h"
#include "Reference.h"

NS_MAGICAL_BEGIN
 
class Data : public Reference
{
public:
	declare_class_hash_code;

public:
	Data( void );
	virtual ~Data( void );
	static Ptr<Data> create( void );
	static Ptr<Data> create( size_t size );
	static Ptr<Data> create( char* data, size_t size );

public:
	void assign( char* data, size_t size );
	void malloc( size_t size );
	void realloc( size_t size );
	void free( void );
	bool empty( void ) const;
	size_t size( void ) const;
	char* cPtr( void );

private:
	char* m_data = nullptr;
	size_t m_size = 0;
};

NS_MAGICAL_END

#endif //__DATA_H__