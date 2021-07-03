#pragma once

#include <vector>
#include "Vec2.h"
#include "Drawable.h"

class Entity
{
public:
	Entity( std::vector<Vec2> model,const Vec2& pos = { 0.0f,0.0f },Color c = Colors::Yellow )
		:
		c( c ),
		pos( pos ),
		model( std::move( model ) )
	{}
	const Vec2& GetPos() const
	{
		return pos;
	}
	void SetPos( const Vec2& newPos )
	{
		pos = newPos;
	}
	void TranslateBy( const Vec2& offset )
	{
		pos += offset;
	}
	void SetScale( float s )
	{
		scale = s;
	}
	float GetScale() const
	{
		return scale;
	}
	Drawable GetDrawable() const
	{
		Drawable d( model,c );
		d.Scale( scale );
		d.Translate( pos );
		return d;
	}
	std::vector<Vec2> GetModel() const
	{
		std::vector<Vec2> modelCpy = model;
		for (auto& m : modelCpy)
		{
			m *= scale;
			m += pos;
		}
		return std::move( modelCpy );
	}
private:
	Color c;
	float scale = 1.0f;
	Vec2 pos = {0.0f,0.0f};
	std::vector<Vec2> model;
};