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

inline Quaternion Quaternion::fromMatrix4( const Matrix4& m )
{
	Quaternion ret;
	magicalQuaternionFromMatrix4( tofpointer( &ret ), tofpointer( &m ) );
	return ret;
}

inline Quaternion Quaternion::fromAxisAngle( const AxisAngle& aa )
{
	Quaternion ret;
	magicalQuaternionFromAxisAngle( tofpointer( &ret ), tofpointer( &aa ) );
	return ret;
}

inline Quaternion Quaternion::fromAxisAngle( const Vector3& axis, const float angle )
{
	Quaternion ret;
	magicalQuaternionFromAxisAngleScalars( tofpointer( &ret ), tofpointer( &axis ), angle );
	return ret;
}

inline Quaternion Quaternion::fromEuler( const EulerAngles& ea )
{
	Quaternion ret;
	magicalQuaternionFromEulerAngles( tofpointer( &ret ), tofpointer( &ea ) );
	return ret;
}

inline Quaternion Quaternion::fromEuler( const float yaw, const float pitch, const float roll )
{
	Quaternion ret;
	magicalQuaternionFromEulerYawPitchRoll( tofpointer( &ret ), yaw, pitch, roll );
	return ret;
}

inline Quaternion Quaternion::fromRotationX( const float angle )
{
	Quaternion ret;
	magicalQuaternionFillRotationX( tofpointer( &ret ), angle );
	return ret;
}

inline Quaternion Quaternion::fromRotationY( const float angle )
{
	Quaternion ret;
	magicalQuaternionFillRotationY( tofpointer( &ret ), angle );
	return ret;
}

inline Quaternion Quaternion::fromRotationZ( const float angle )
{
	Quaternion ret;
	magicalQuaternionFillRotationZ( tofpointer( &ret ), angle );
	return ret;
}

inline bool Quaternion::equals( const Quaternion& q ) const
{
	return magicalQuaternionEquals( tofpointer( this ), tofpointer( &q ) );
}

inline bool Quaternion::isZero( void ) const
{
	return magicalQuaternionIsZero( tofpointer( this ) );
}

inline bool Quaternion::isIdentity( void ) const
{
	return magicalQuaternionIsIdentity( tofpointer( this ) );
}

inline bool Quaternion::isNormalized( void ) const
{
	return magicalQuaternionIsNormalized( tofpointer( this ) );
}

inline void Quaternion::fill( const Quaternion& r )
{
	x = r.x; y = r.y; z = r.z; w = r.w;
}

inline void Quaternion::fill( float x, float y, float z, float w )
{
	this->x = x; this->y = y; this->z = z; this->w = w;
}

inline void Quaternion::fillIdentity( void )
{
	x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
}

inline void Quaternion::fillMatrix4( const Matrix4& m )
{
	magicalQuaternionFromMatrix4( tofpointer( this ), tofpointer( &m ) );
}

inline void Quaternion::fillAxisAngle( const AxisAngle& aa )
{
	magicalQuaternionFromAxisAngle( tofpointer( this ), tofpointer( &aa ) );
}

inline void Quaternion::fillAxisAngle( const Vector3& axis, const float angle )
{
	magicalQuaternionFromAxisAngleScalars( tofpointer( this ), tofpointer( &axis ), angle );
}

inline void Quaternion::fillEuler( const EulerAngles& ea )
{
	magicalQuaternionFromEulerAngles( tofpointer( this ), tofpointer( &ea ) );
}

inline void Quaternion::fillEuler( const float yaw, const float pitch, const float roll )
{
	magicalQuaternionFromEulerYawPitchRoll( tofpointer( this ), yaw, pitch, roll );
}

inline void Quaternion::fillRotationX( const float angle )
{
	magicalQuaternionFillRotationX( tofpointer( this ), angle );
}

inline void Quaternion::fillRotationY( const float angle )
{
	magicalQuaternionFillRotationY( tofpointer( this ), angle );
}

inline void Quaternion::fillRotationZ( const float angle )
{
	magicalQuaternionFillRotationZ( tofpointer( this ), angle );
}

inline void Quaternion::add( Quaternion& out, const Quaternion& q1, const Quaternion& q2 )
{
	magicalQuaternionAdd( tofpointer( &out ), tofpointer( &q1 ), tofpointer( &q2 ) );
}

inline void Quaternion::sub( Quaternion& out, const Quaternion& q1, const Quaternion& q2 )
{
	magicalQuaternionSub( tofpointer( &out ), tofpointer( &q1 ), tofpointer( &q2 ) );
}

inline void Quaternion::mulScalar( Quaternion& out, const Quaternion& q, const float a )
{
	magicalQuaternionMulScalar( tofpointer( &out ), tofpointer( &q ), a );
}

inline void Quaternion::mul( Quaternion& out, const Quaternion& q1, const Quaternion& q2 )
{
	magicalQuaternionMul( tofpointer( &out ), tofpointer( &q1 ), tofpointer( &q2 ) );
}

inline bool Quaternion::operator==( const Quaternion& q ) const
{
	return magicalQuaternionEquals( tofpointer( this ), tofpointer( &q ) );
}

inline bool Quaternion::operator!=( const Quaternion& q ) const
{
	return !magicalQuaternionEquals( tofpointer( this ), tofpointer( &q ) );
}

inline Quaternion Quaternion::operator+( const Quaternion& q ) const
{
	return Quaternion( x + q.x, y + q.y, z + q.z, w + q.w );
}

inline Quaternion Quaternion::operator-( const Quaternion& q ) const
{
	return Quaternion( x - q.x, y - q.y, z - q.z, w - q.w );
}

inline Quaternion Quaternion::operator*( const float a ) const
{
	return Quaternion( x * a, y * a, z * a, w * a );
}

inline Quaternion Quaternion::operator*( const Quaternion& q ) const
{
	Quaternion ret;
	magicalQuaternionMul( tofpointer( &ret ), tofpointer( this ), tofpointer( &q ) );
	return ret;
}

inline Quaternion& Quaternion::operator+=( const Quaternion& q )
{
	w += q.w; x += q.x; y += q.y; z += q.z;
	return *this;
}

inline Quaternion& Quaternion::operator-=( const Quaternion& q )
{
	w -= q.w; x -= q.x; y -= q.y; z -= q.z;
	return *this;
}

inline Quaternion& Quaternion::operator*=( const float a )
{
	x *= a; y *= a; z *= a; w *= a;
	return *this;
}

inline Quaternion& Quaternion::operator*=( const Quaternion& q )
{
	magicalQuaternionMul( tofpointer( this ), tofpointer( this ), tofpointer( &q ) );
	return *this;
}

inline Quaternion& Quaternion::operator=( const Quaternion& q )
{
	x = q.x; y = q.y; z = q.z; w = q.w;
	return *this;
}

inline void Quaternion::rotateX( Quaternion& out, const Quaternion& q, const float angle )
{
	magicalQuaternionRotateX( tofpointer( &out ), tofpointer( &q ), angle );
}

inline void Quaternion::rotateY( Quaternion& out, const Quaternion& q, const float angle )
{
	magicalQuaternionRotateY( tofpointer( &out ), tofpointer( &q ), angle );
}

inline void Quaternion::rotateZ( Quaternion& out, const Quaternion& q, const float angle )
{
	magicalQuaternionRotateZ( tofpointer( &out ), tofpointer( &q ), angle );
}

inline void Quaternion::rotateAxisAngle( Quaternion& out, const Quaternion& q, const AxisAngle& aa )
{
	magicalQuaternionRotateAxisAngle( tofpointer( &out ), tofpointer( &q ), tofpointer( &aa ) );
}

inline void Quaternion::rotateAxisAngle( Quaternion& out, const Quaternion& q, const Vector3& axis, const float angle )
{
	magicalQuaternionRotateAxisAngleScalars( tofpointer( &out ), tofpointer( &q ), tofpointer( &axis ), angle );
}

inline void Quaternion::rotateEuler( Quaternion& out, const Quaternion& q, const EulerAngles& ea )
{
	magicalQuaternionRotateEulerAngles( tofpointer( &out ), tofpointer( &q ), tofpointer( &ea ) );
}

inline void Quaternion::rotateEuler( Quaternion& out, const Quaternion& q, const float yaw, const float pitch, const float roll )
{
	magicalQuaternionRotateEulerYawPitchRoll( tofpointer( &out ), tofpointer( &q ), yaw, pitch, roll );
}

inline void Quaternion::normalize( Quaternion& out, const Quaternion& q )
{
	magicalQuaternionNormalize( tofpointer( &out ), tofpointer( &q ) );
}

inline void Quaternion::conjugate( Quaternion& out, const Quaternion& q )
{
	magicalQuaternionConjugate( tofpointer( &out ), tofpointer( &q ) );
}

inline void Quaternion::negate( Quaternion& out, const Quaternion& q )
{
	magicalQuaternionNegate( tofpointer( &out ), tofpointer( &q ) );
}

inline void Quaternion::inverse( Quaternion& out, const Quaternion& q )
{
	magicalQuaternionInverse( tofpointer( &out ), tofpointer( &q ) );
}

inline void Quaternion::rotateX( const float angle )
{
	magicalQuaternionRotateX( tofpointer( this ), tofpointer( this ), angle );
}

inline void Quaternion::rotateY( const float angle )
{
	magicalQuaternionRotateY( tofpointer( this ), tofpointer( this ), angle );
}

inline void Quaternion::rotateZ( const float angle )
{
	magicalQuaternionRotateZ( tofpointer( this ), tofpointer( this ), angle );
}

inline void Quaternion::rotateAxisAngle( const AxisAngle& aa )
{
	magicalQuaternionRotateAxisAngle( tofpointer( this ), tofpointer( this ), tofpointer( &aa ) );
}

inline void Quaternion::rotateAxisAngle( const Vector3& axis, const float angle )
{
	magicalQuaternionRotateAxisAngleScalars( tofpointer( this ), tofpointer( this ), tofpointer( &axis ), angle );
}

inline void Quaternion::rotateEuler( const EulerAngles& ea )
{
	magicalQuaternionRotateEulerAngles( tofpointer( this ), tofpointer( this ), tofpointer( &ea ) );
}

inline void Quaternion::rotateEuler( const float yaw, const float pitch, const float roll )
{
	magicalQuaternionRotateEulerYawPitchRoll( tofpointer( this ), tofpointer( this ), yaw, pitch, roll );
}

inline void Quaternion::normalize( void )
{
	magicalQuaternionNormalize( tofpointer( this ), tofpointer( this ) );
}

inline void Quaternion::conjugate( void )
{
	magicalQuaternionConjugate( tofpointer( this ), tofpointer( this ) );
}

inline void Quaternion::negate( void )
{
	magicalQuaternionNegate( tofpointer( this ), tofpointer( this ) );
}

inline void Quaternion::inverse( void )
{
	magicalQuaternionInverse( tofpointer( this ), tofpointer( this ) );
}

inline Quaternion Quaternion::getNormalized( void ) const
{
	Quaternion ret;
	magicalQuaternionNormalize( tofpointer( &ret ), tofpointer( this ) );
	return ret;
}

inline Quaternion Quaternion::getConjugated( void ) const
{
	Quaternion ret;
	magicalQuaternionConjugate( tofpointer( &ret ), tofpointer( this ) );
	return ret;
}

inline Quaternion Quaternion::getNegated( void ) const
{
	Quaternion ret;
	magicalQuaternionNegate( tofpointer( &ret ), tofpointer( this ) );
	return ret;
}

inline Quaternion Quaternion::getInversed( void ) const
{
	Quaternion ret;
	magicalQuaternionInverse( tofpointer( &ret ), tofpointer( this ) );
	return ret;
}

inline float Quaternion::dot( const Quaternion& q ) const
{
	return magicalQuaternionDot( tofpointer( this ), tofpointer( &q ) );
}

inline float Quaternion::length( void ) const
{
	return magicalQuaternionLength( tofpointer( this ) );
}

inline float Quaternion::lengthSq( void ) const
{
	return magicalQuaternionLengthSq( tofpointer( this ) );
}

//inline float Quaternion::toAxisAngle( Vector3& out ) const
//{
//	return magicalQuaternionToAxisAngle( tofpointer( &out ), tofpointer( this ) );
//}