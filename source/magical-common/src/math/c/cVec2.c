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
#include "cVec2.h"

cBool magicalVec2Equals( const cVec2 v1, const cVec2 v2 ) 
{
	return magicalAlmostEqual( v1 _x, v2 _x ) && magicalAlmostEqual( v1 _y, v2 _y );
}

cBool magicalVec2IsZero( const cVec2 v )
{
	return magicalAlmostZero( v _x ) && magicalAlmostZero( v _y );
}

cBool magicalVec2IsOne( const cVec2 v )
{
	return magicalAlmostEqual( v _x, 1.0f ) && magicalAlmostEqual( v _y, 1.0f );
}

cBool magicalVec2IsNormalize( const cVec2 v )
{
	return magicalAlmostEqual( v _x * v _x + v _y * v _y, 1.0f );
}

void magicalVec2FillScalars( cVec2 out, const float x, const float y )
{
	out _x = x;
	out _y = y;
}

void magicalVec2FillZero( cVec2 out )
{
	out _x = 0.0f;
	out _y = 0.0f;
}

void magicalVec2FillOne( cVec2 out )
{
	out _x = 1.0f;
	out _y = 1.0f;
}

void magicalVec2Fill( cVec2 out, const cVec2 v )
{
	out _x = v _x;
	out _y = v _y;
}

void magicalVec2FromVec3( cVec2 out, const cVec3 v )
{
	out _x = v _x;
	out _y = v _y;
}

void magicalVec2FromVec4( cVec2 out, const cVec4 v )
{
	out _x = v _x;
	out _y = v _y;
}

void magicalVec2AddScalar( cVec2 out, const cVec2 v, const float a )
{
	out _x = v _x + a;
	out _y = v _y + a;
}

void magicalVec2Add( cVec2 out, const cVec2 v1, const cVec2 v2 )
{
	out _x = v1 _x + v2 _x;
	out _y = v1 _y + v2 _y;
}

void magicalVec2SubScalar( cVec2 out, const cVec2 v, const float a )
{
	out _x = v _x - a;
	out _y = v _y - a;
}

void magicalVec2Sub( cVec2 out, const cVec2 v1, const cVec2 v2 )
{
	out _x = v1 _x - v2 _x;
	out _y = v1 _y - v2 _y;
}

void magicalVec2MulScalar( cVec2 out, const cVec2 v, const float a )
{
	out _x = v _x * a;
	out _y = v _y * a;
}

void magicalVec2Mul( cVec2 out, const cVec2 v1, const cVec2 v2 )
{
	out _x = v1 _x * v2 _x;
	out _y = v1 _y * v2 _y;
}

void magicalVec2DivScalar( cVec2 out, const cVec2 v, const float a )
{
	debugassert( !magicalAlmostZero( a ), "division by 0.f" );

	out _x = v _x / a;
	out _y = v _y / a;
}

void magicalVec2Div( cVec2 out, const cVec2 v1, const cVec2 v2 )
{
	debugassert( !magicalAlmostZero( v2 _x ) && !magicalAlmostZero( v2 _y ), "division by 0.f" );

	out _x = v1 _x / v2 _x;
	out _y = v1 _y / v2 _y;
}

/*-----------------------------------------------------------------------------*\
 * 返回两个向量的点乘运算 done
 * 
 * 点乘公式：dot(a,b) = a.x*b.x + a.y*b.y
 *
 * 点乘结果等于向量长度与向量夹角的cos值的积
 * 点乘夹角公式：dot(a,b) = length(a) * length(b) * cos(theta)
 *
 * 在3D中两向量的夹角是在包含两向量的平面中定义的
 *
 * v1 向量1
 * v2 向量2
 * return 点乘结果
 *        > 0 两向量接近同一方向
 *        = 0 两向量垂直
 *        < 0 两向量接近相反方向
 *-----------------------------------------------------------------------------*/
float magicalVec2Dot( const cVec2 v1, const cVec2 v2 )
{
	return v1 _x * v2 _x + v1 _y * v2 _y;
}

/*-----------------------------------------------------------------------------*\
 * 返回两个点之间的距离(a向量到b向量的距离) done
 * 
 * 距离公式：distance(a,b) = length(d);
 * 其中向量d = b-a
 *
 * v1 向量1
 * v2 向量2
 * return 距离>= 0 当距离=0时 两点在同一位置，或者说两向量大小相同
 *-----------------------------------------------------------------------------*/
float magicalVec2DistanceBetween( const cVec2 v1, const cVec2 v2 )
{
	float dx = v2 _x - v1 _x;
	float dy = v2 _y - v1 _y;

	return sqrtf( dx * dx + dy * dy );
}

/*-----------------------------------------------------------------------------*\
 * 返回两个点之间距离的平方 done
 *
 * v1 向量1
 * v2 向量2
 * return v1到v2的距离 >= 0 
 *        = 0时 两点在同一位置，或者说两向量大小相同
 *-----------------------------------------------------------------------------*/
float magicalVec2DistanceBetweenSq( const cVec2 v1, const cVec2 v2 )
{
	float dx = v2 _x - v1 _x;
	float dy = v2 _y - v1 _y;

	return dx * dx + dy * dy;
}

/*-----------------------------------------------------------------------------*\
 * 返回这个向量的长度(大小、模) done
 *
 * 求模公式 length = sqrt(a^2 + b^2 + ... n^2)
 *
 * v 求模向量
 * return v的模 >= 0
 *        = 0 零向量
 *        = 1 标准化(单位)向量
 *-----------------------------------------------------------------------------*/
float magicalVec2Length( const cVec2 v )
{
	return sqrtf( v _x * v _x + v _y * v _y );
}

/*-----------------------------------------------------------------------------*\
 * 返回这个向量长度(大小、模)的平方 done
 *
 * v 求模平方向量
 * return v模平方 >= 0
 *         = 0 零向量
 *         = 1 标准化(单位)向量
 *-----------------------------------------------------------------------------*/
float magicalVec2LengthSq( const cVec2 v )
{
	return v _x * v _x + v _y * v _y;
}

/*-----------------------------------------------------------------------------*\
 * 返回两个向量之间的夹角(弧度单位) done
 * 
 * 参考点乘夹角公式
 * 转换：theta = acos( dot(a,b) / length(a) * length(b) )
 *
 * 两个参与运算的向量都不能为零向量
 *
 * v1 向量1
 * v2 向量2
 * return 夹角弧度 >=0 and <= PI
 *        = 0 两向量方向一致
 *-----------------------------------------------------------------------------*/
float magicalVec2AngleBetween( const cVec2 v1, const cVec2 v2 )
{
	debugassert( !magicalVec2IsZero( v1 ) && !magicalVec2IsZero( v2 ), "invaild operate!" );

	return magicalSafeAcos( magicalVec2Dot( v1, v2 ) / ( magicalVec2Length( v1 ) * magicalVec2Length( v2 ) ) );
}

/*-----------------------------------------------------------------------------*\
 * 使点参照min与max的位置进行收缩 done
 *
 * out 结果 min <= out <= max
 * v 源向量
 * min 小值
 * max 大值
 *-----------------------------------------------------------------------------*/
void magicalVec2Clamp( cVec2 out, const cVec2 v, const cVec2 min, const cVec2 max )
{
	debugassert( min _x <= max _x && min _y <= max _y, "invaild operate!" );

	out _x = v _x;
	out _y = v _y;

	if( out _x < min _x ) out _x = min _x;
	if( out _x > max _x ) out _x = max _x;
	if( out _y < min _y ) out _y = min _y;
	if( out _y > max _y ) out _y = max _y;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的倒数形式 done
 *
 * out 结果 v = -v
 * v 源向量
 *-----------------------------------------------------------------------------*/
void magicalVec2Negate( cVec2 out, const cVec2 v )
{
	out _x = -v _x;
	out _y = -v _y;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的标准化 done
 * 
 * 向量标准化公式：normalize(a) = a / length(a)
 *
 * 当向量已经标准化或模接近0，则标准化失败
 *
 * out 结果 out = normalize(v)
 * v 源向量
 *-----------------------------------------------------------------------------*/
void magicalVec2Normalize( cVec2 out, const cVec2 v )
{
	out _x = v _x;
	out _y = v _y;

	float n = v _x * v _x + v _y * v _y;
	if( magicalAlmostEqual( n, 1.0f ) )
		return;

	n = sqrtf( n );
	if( magicalAlmostZero( n ) )
		return;

	n = 1.0f / n;
	out _x *= n;
	out _y *= n;
}

/*-----------------------------------------------------------------------------*\
 * 使2D向量绕原点旋转 done
 * 
 * 2D向量绕原点旋转公式：
 * v`.x = v.x*cos(theta) - v.y*sin(theta)
 * v`.y = v.x*sin(theta) + v.y*cos(theta) 
 *
 * out 旋转后的向量
 * v 源向量
 * angle 旋转的弧度
 *-----------------------------------------------------------------------------*/
void magicalVec2Rotate( cVec2 out, const cVec2 v, const float angle )
{
	float rx, ry, s, c;

	s = sinf( angle );
	c = cosf( angle );

	rx = v _x * c - v _y * s;
	ry = v _x * s + v _y * c;

	out _x = rx;
	out _y = ry;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量的缩放 done
 *
 * out 缩放后的向量
 * v 源向量
 * s 缩放系数
 *-----------------------------------------------------------------------------*/
void magicalVec2Scale( cVec2 out, const cVec2 v, const float s )
{
	out _x = v _x * s;
	out _y = v _y * s;
}

/*-----------------------------------------------------------------------------*\
 * 返回由两个点组成的线段的中点 done
 *
 * out 返回中点 当两点相等时中点也等于原点
 * v1 向量1
 * v2 向量2
 *-----------------------------------------------------------------------------*/
void magicalVec2MidPointBetween( cVec2 out, const cVec2 v1, const cVec2 v2 )
{
	out _x = ( v1 _x + v2 _x ) * 0.5f;
	out _y = ( v1 _y + v2 _y ) * 0.5f;
}

/*-----------------------------------------------------------------------------*\
 * 计算向量p到向量n的投影，结果由向量h(平行于n)和向量v(垂直于n)返回 done
 * 
 * 投影结果满足 p = h + v
 *
 * 平行投影向量公式：h = n * ( dot(p,n) / lengthSq(n) )
 * 如果n为单位向量 ：h = n * ( dot(p,n) )
 * 垂直投影向量公式：v = p - h;
 *
 * 向量p或向量n为零向量时投影无意义
 *
 * 如果向量p与向量n方向一致，则 h = p, v = 0
 * 
 * out_h 平行与n的投影分量
 * out_v 垂直于n的投影分量
 * p 源向量
 * n 投影目标向量
 *-----------------------------------------------------------------------------*/
void magicalVec2Project( cVec2 out_h, cVec2 out_v, const cVec2 p, const cVec2 n )
{
	float d;
	cVec2 normalize;

	debugassert( !magicalVec2IsZero( n ), "invaild operate!" );
	
	magicalVec2Normalize( normalize, n );
	d = magicalVec2Dot( p, normalize );

	out_h _x = normalize _x * d;
	out_h _y = normalize _y * d;

	if( magicalVec2Equals( out_h, p ) )
	{
		out_v _x = 0.0f;
		out_v _y = 0.0f;
	}
	else
	{
		out_v _x = p _x - out_h _x;
		out_v _y = p _y - out_h _y;
	}
}