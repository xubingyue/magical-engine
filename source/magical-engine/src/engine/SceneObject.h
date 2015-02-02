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
#ifndef __SCENE_OBJECT_H__
#define __SCENE_OBJECT_H__

#include "PlatformMacros.h"
#include "Common.h"
#include "SceneNode.h"
#include "Behaviour.h"

#include <unordered_map>

NS_MAGICAL_BEGIN

using ::std::unordered_map;

class SceneObject : public SceneNode
{
public:
	friend class Engine;
	friend class Scene;
	declare_class_hash_code;

public:
	SceneObject( void );
	virtual ~SceneObject( void );
	static Ptr<SceneObject> create( void );
	static Ptr<SceneObject> create( const char* name );

public:
	template< class TBehaviour >
	void addComponent( void );
	template< class TBehaviour >
	void removeComponent( void );

protected:
	void update( void );

protected:
	unordered_map<size_t, BehaviourBase*> m_behaviours;
};

template< class TBehaviour >
void SceneObject::addComponent( void )
{
	size_t key = typeid( TBehaviour ).hash_code();
	magicalAssert( m_behaviours.find( key ) == m_behaviours.end(), "Invaild, can't add the same one." );

	TBehaviour* behaviour = new TBehaviour();
	m_behaviours.insert( std::make_pair( key, behaviour ) );

	behaviour->that = dynamic_cast< decltype( behaviour->that ) >( this );
	magicalAssert( behaviour->that, "Invaild, dose not match target type!" );
	behaviour->onCreate();
}

template< class TBehaviour >
void SceneObject::removeComponent( void )
{
	size_t key = typeid( TBehaviour ).hash_code();

	auto itr = m_behaviours.find( key );
	if( itr != m_behaviours.end() )
	{
		m_behaviours.erase( itr );
		itr->second->onDestroy();
		itr->second->release();
	}
}

NS_MAGICAL_END

#endif //__SCENE_OBJECT_H__