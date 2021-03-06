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
#include "Camera.h"
#include "Scene.h"

NS_MAGICAL_BEGIN

Camera::Camera( void )
: m_view_channel_index( ViewChannel::Default )
, m_camera_dirty_info( kCameraClean )
{
	m_element_enum = Element::Camera;
}

Camera::~Camera( void )
{
	
}

Ptr<Camera> Camera::create( void )
{
	Camera* ret = new Camera();
	magicalAssert( ret, "new Camera() failed" );
	return Ptr<Camera>( PtrCtor<Camera>( ret ) );
}

Ptr<Camera> Camera::create( const char* name )
{
	Camera* ret = new Camera();
	magicalAssert( ret, "new Camera() failed" );
	ret->setName( name );
	return Ptr<Camera>( PtrCtor<Camera>( ret ) );
}

void Camera::setVisible( bool visible )
{
	if( visible != m_visible )
	{
		if( visible == false ) 
			setActive( false );

		Entity::setVisible( visible );
	}
}

void Camera::setActive( bool active ) 
{
	if( m_visible == false )
		return;
	if( active == m_active )
		return;

	m_active = active;
	if( m_running && m_root_scene )
	{
		if( active )
		{
			m_root_scene->bindCameraToViewChannel( this );
		}
		else
		{
			m_root_scene->unbindCameraFromViewChannel( this );
		}
	}
}

void Camera::bindViewChannel( ViewChannel::Index index )
{
	magicalAssert( 0 <= index && index <= ViewChannel::Count, "Invalid Index!" );
	if( index == m_view_channel_index  )
		return;

	m_view_channel_index = index;
	if( m_active && m_running && m_root_scene )
	{
		m_root_scene->bindCameraToViewChannel( this );
	}
}

void Camera::setOrthWindow( float width, float height )
{

}

void Camera::setOrth( float left, float right, float bottom, float top, float znear, float zfar )
{
	m_left = left;
	m_right = right;
	m_bottom = bottom;
	m_top = top;
	m_znear = znear;
	m_zfar = zfar;

	m_projection = Projection::Orth;
	m_camera_dirty_info |= ( kCameraProjectionDirty | kCameraViewProjectionDirty );
}

void Camera::setFieldOfView( float fov )
{
	m_fov = fov;
	m_camera_dirty_info |= ( kCameraProjectionDirty | kCameraViewProjectionDirty );
}

void Camera::setAutoAspectRatio( bool auto_aspect_ratio )
{
	m_auto_aspect_ratio = auto_aspect_ratio;
}

void Camera::setAspectRatio( float aspect )
{
	m_aspect = aspect;
	m_camera_dirty_info |= ( kCameraProjectionDirty | kCameraViewProjectionDirty );
}

void Camera::setNearClipDistance( float znear )
{
	m_znear = znear;
	m_camera_dirty_info |= ( kCameraProjectionDirty | kCameraViewProjectionDirty );
}

void Camera::setFarClipDistance( float zfar )
{
	m_zfar = zfar;
	m_camera_dirty_info |= ( kCameraProjectionDirty | kCameraViewProjectionDirty);
}

void Camera::setPerspective( float fov, float aspect, float znear, float zfar )
{
	m_fov = fov;
	m_aspect = aspect;
	m_znear = znear;
	m_zfar = zfar;

	m_projection = Projection::Perspective;
	m_camera_dirty_info |= ( kCameraProjectionDirty | kCameraViewProjectionDirty );
}

const Matrix4& Camera::getViewMatrix( void ) const
{
	if( m_camera_dirty_info & kCameraViewDirty )
	{
		m_view_matrix = getLocalToWorldMatrix().getInversed();
		m_camera_dirty_info &= ~kCameraViewDirty;
	}

	return m_view_matrix;
}

const Matrix4& Camera::getProjectionMatrix( void ) const
{
	if( m_camera_dirty_info & kCameraProjectionDirty )
	{
		switch( m_projection )
		{
		case Projection::Orth:
			m_projection_matrix.setOrth( m_left, m_right, m_bottom, m_top, m_znear, m_zfar );
			break;
		case Projection::Perspective:
			m_projection_matrix.setPerspective( m_fov, m_aspect, m_znear, m_zfar );
			break;
		default:
			magicalAssert( false, "Invalid!" );
			break;
		}
		m_camera_dirty_info &= ~kCameraProjectionDirty;
	}

	return m_projection_matrix;
}

const Matrix4& Camera::getViewProjectionMatrix( void ) const
{
	if( m_camera_dirty_info & kCameraViewProjectionDirty )
	{
		m_view_projection_matrix = getViewMatrix() * getProjectionMatrix();
		m_camera_dirty_info &= ~kCameraViewProjectionDirty;
	}

	return m_view_projection_matrix;
}

void Camera::transform( void )
{
	Entity::transform();
}

void Camera::transformDirty( int info )
{
	SceneObject::transformDirty( info );

	m_camera_dirty_info |= kCameraViewDirty;
	m_camera_dirty_info |= kCameraViewProjectionDirty;
}

NS_MAGICAL_END