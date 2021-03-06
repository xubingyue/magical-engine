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
#ifndef __SPHERE_H__
#define __SPHERE_H__

NS_MAGICAL_BEGIN

FORWARD_DECLARE

struct Sphere : public cSphere
{
public:
	static const Sphere Zero;
	static const Sphere One;
	static Sphere var;

public:
	Sphere( float x, float y, float z, float r );
	Sphere( const Sphere& sp );
	Sphere( void );

public:
	static inline Sphere createZero( void );
	static inline Sphere createOne( void );
	static inline Sphere createFromCenterAndRadius( const Vector3& center, float r );

public:
#if MAGICAL_MATH_CACHED_POOL_ENABLE
	static void* operator new( size_t s );
	static void operator delete( void* ptr );
#endif
	inline bool equals( const Sphere& sp ) const;
	inline bool isZero( void ) const;
	inline bool isOne( void ) const;
	inline bool operator==( const Sphere& sp ) const;
	inline bool operator!=( const Sphere& sp ) const;
	inline Sphere& operator=( const Sphere& sp );

public:
	inline void set( const Sphere& sp );
	inline void setZero( void );
	inline void setOne( void );
	inline void setScalars( float x, float y, float z, float r );
	inline void setCenterAndRadius( const Vector3& center, float r );

	inline bool intersects( const Sphere& sp ) const;
	inline bool intersectsAABB3( const AABB3& aabb ) const;
	inline bool intersectsPlane( const Plane& p ) const;
	inline bool intersectsRay3( float& outt, const Ray3& r3, bool discard_inside = false ) const;
	inline bool containsPoint( const Vector3& point ) const;
};

NS_MAGICAL_END

#endif //__SPHERE_H__