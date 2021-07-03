#pragma once

#include "CoordinateTransformer.h"
#include "_Rect.h"

class Camera
{
public:
	Camera( CoordinateTransformer& ct, float width, float height )
		:
		ct( ct ),
		width( width ),
		height( height )
	{}
	Vec2 GetPos() const
	{
		return pos;
	}
	void MoveBy( const Vec2& offset )
	{
		pos += offset;
	}
	void MoveTo( const Vec2& pos_in )
	{
		pos = pos_in;
	}
	void Draw( Drawable& drawable ) const
	{
		drawable.Translate( -pos );
		drawable.Scale( scale );
		ct.Draw( drawable );
	}
	void SetScale( float s )
	{
		scale = s;
	}
	float GetScale() const
	{
		return scale;
	}
	_Rect GetRect() const
	{
		Vec2 topleft = Vec2( -1.0f, 1.0f ) / scale;
		Vec2 bottomright = Vec2( 1.0f, -1.0f ) / scale;

		topleft.x *= (width - 1) / 2;
		bottomright.x *= (width - 1) / 2;

		topleft.y *= (height - 1) / 2;
		bottomright.y *= (height - 1) / 2;

		topleft += pos;
		bottomright += pos;

		return _Rect( topleft, bottomright );
	}

private:
	Vec2 pos = {0.0f,0.0f};
	float scale = 1.0f;
	CoordinateTransformer& ct;

	const float width;
	const float height;
};