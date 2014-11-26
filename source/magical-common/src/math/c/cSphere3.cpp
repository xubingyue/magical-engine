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
#include "cSphere3.h"

void magicalSphere3FillScalars( cSphere3 out, const float x, const float y, const float z, const float r )
{
	out _x = x;
	out _y = y;
	out _z = z;
	out _r = r;
}

void magicalSphere3FillCenterAndRadius( cSphere3 out, const cVec3 center, const float r )
{
	out _x = center _x;
	out _y = center _y;
	out _z = center _z;
	out _r = r;
}

void magicalSphere3Fill( cSphere3 out, const cSphere3 sp )
{
	out _x = sp _x;
	out _y = sp _y;
	out _z = sp _z;
	out _r = sp _r;
}

cBool magicalSphere3Intersects( const cSphere3 sp1, const cSphere3 sp2 )
{
	return magicalVec3DistanceBetweenSq( sp1, sp2 ) <= ( sp1 _r + sp2 _r ) * ( sp1 _r + sp2 _r );
}

cBool magicalSphere3IntersectsAABB3( const cSphere3 sp, const cAABB3 aabb )
{
	return magicalAABB3IntersectsSphere3( aabb, sp );
}

cBool magicalSphere3IntersectsPlane3( const cSphere3 sp, const cPlane3 p )
{
	return magicalPlane3IntersectsSphere3( p, sp );
}