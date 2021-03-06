﻿/******************************************************************************
The MIT License (MIT)

Copyright (c) 2014 Jason.lee

Permission is hereby granted, free of chaage, to any person obtaining a copy
of this softwaae and associated documentation files (the "Softwaae"), to deal
in the Softwaae without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Softwaae, and to permit persons to whom the Softwaae is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Softwaae.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/
#ifndef __FRUSTUM_H__
#define __FRUSTUM_H__

NS_MAGICAL_BEGIN

FORWARD_DECLARE

enum class FrustumPlane
{
	Left = 0,
	Right = 1,
	Top = 2,
	Bottom = 3,
	Near = 4,
	Far = 5
};

struct Frustum : public cFrustum 
{
public:
	static inline Frustum createFromMatrix4( const Matrix4& m );

public:
	Frustum( const Frustum& frustum );
	Frustum( void );

public:
#if MAGICAL_MATH_CACHED_POOL_ENABLE
	static void* operator new( size_t s );
	static void operator delete( void* ptr );
#endif

public:
	inline void extractFromMatrix4( const Matrix4& m );
	inline void setPlane( const Plane& p, int which );
	inline Plane getPlane( FrustumPlane which ) const;

	inline bool containsAABB3( const AABB3& aabb );
};

NS_MAGICAL_END

#endif //__FRUSTUM_H__