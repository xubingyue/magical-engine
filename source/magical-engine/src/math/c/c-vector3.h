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
#ifndef __C_VECTOR3_H__
#define __C_VECTOR3_H__

#include "c-utility.h"

#pragma pack( push )
#pragma pack( 4 )
typedef struct cVector3 {
	float x;
	float y;
	float z;
} cVector3;
#pragma pack( pop )

#include "c-vector2.h"
#include "c-vector4.h"

#ifdef __cplusplus
extern "C" {
#endif

MAGICALAPI_MATH cBool magicalVector3Equals( const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH cBool magicalVector3IsZero( const cVector3* v );
MAGICALAPI_MATH cBool magicalVector3IsOne( const cVector3* v );
MAGICALAPI_MATH cBool magicalVector3IsNormalized( const cVector3* v );

MAGICALAPI_MATH void magicalVector3Fill( cVector3* out, float x, float y, float z );
MAGICALAPI_MATH void magicalVector3Copy( cVector3* out, const cVector3* v );
MAGICALAPI_MATH void magicalVector3SetZero( cVector3* out );
MAGICALAPI_MATH void magicalVector3SetOne( cVector3* out );
MAGICALAPI_MATH void magicalVector3FromVector2( cVector3* out, const cVector2* v );
MAGICALAPI_MATH void magicalVector3FromVector4( cVector3* out, const cVector4* v );

MAGICALAPI_MATH void magicalVector3AddScalar( cVector3* out, const cVector3* v, float a );
MAGICALAPI_MATH void magicalVector3Add( cVector3* out, const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH void magicalVector3SubScalar( cVector3* out, const cVector3* v, float a );
MAGICALAPI_MATH void magicalVector3Sub( cVector3* out, const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH void magicalVector3MulScalar( cVector3* out, const cVector3* v, float a );
MAGICALAPI_MATH void magicalVector3Mul( cVector3* out, const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH void magicalVector3DivScalar( cVector3* out, const cVector3* v, float a );
MAGICALAPI_MATH void magicalVector3Div( cVector3* out, const cVector3* v1, const cVector3* v2 );

MAGICALAPI_MATH float magicalVector3Dot( const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH float magicalVector3DistanceBetween( const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH float magicalVector3DistanceBetweenSq( const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH float magicalVector3Length( const cVector3* v );
MAGICALAPI_MATH float magicalVector3LengthSq( const cVector3* v );
MAGICALAPI_MATH float magicalVector3AngleBetween( const cVector3* v1, const cVector3* v2 );

MAGICALAPI_MATH void magicalVector3Cross( cVector3* out, const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH void magicalVector3Clamp( cVector3* out, const cVector3* v, const cVector3* min, const cVector3* max );
MAGICALAPI_MATH void magicalVector3Negate( cVector3* out, const cVector3* v );
MAGICALAPI_MATH void magicalVector3Normalize( cVector3* out, const cVector3* v );
MAGICALAPI_MATH void magicalVector3Scale( cVector3* out, const cVector3* v, float s );
MAGICALAPI_MATH void magicalVector3MidPointBetween( cVector3* out, const cVector3* v1, const cVector3* v2 );
MAGICALAPI_MATH void magicalVector3Project( cVector3* out, const cVector3* p, const cVector3* n );

#ifdef __cplusplus
}
#endif

#endif //__C_VECTOR3_H__