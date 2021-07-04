#pragma once

#include "Colors.h"
#include "ChiliMath.h"
#include <algorithm>

namespace StarAnimations
{
	class Scale 
	{
	public:
		Scale( float period )
			:
			period( period )
		{
		}
		void operator()( Color& c, float& scale, float dt )
		{
			seconds += dt;

			const float meanScale = ( minScale + maxScale ) / 2;
			const float amplitude = meanScale - minScale;

			scale = amplitude * sin( seconds * 2 * PI / period ) + meanScale;
		}

	private:
		float seconds = 0.0f;
		const float period = 1.0f;

		const float minScale = 0.5f;
		const float maxScale = 1.5f;
	};

	class ColorEffect
	{
	public:
		ColorEffect( Color baseColor, Color destinationColor = Colors::White, float period = 1.0f )
			:
			baseColor( baseColor ),
			destinationColor( destinationColor ),
			period( period )
		{
		}
		void operator()( Color& c, float& scale, float dt )
		{
			seconds += dt;

			const int alpha = 127 + int( 127.0f * sin( seconds * 2 * PI / period ) );
			int r = alpha + baseColor.GetR();
			int g = alpha + baseColor.GetG();
			int b = alpha + baseColor.GetB();
			r = std::clamp( r, 0, (int)destinationColor.GetR() );
			g = std::clamp( g, 0, (int)destinationColor.GetG() );
			b = std::clamp( b, 0, (int)destinationColor.GetB() );
			c = { (unsigned char)r, (unsigned char)g, (unsigned char)b };
		}
	private:
		float seconds = 0.0f;
		const float period;
		
		const Color baseColor;
		const Color destinationColor;
	};

	class ScaleAndColor : public Scale, public ColorEffect
	{
	public:
		ScaleAndColor(Color baseColor, Color destinationColor, float period)
			:
			Scale( period ),
			ColorEffect( baseColor, destinationColor, period )
		{
		}
		void operator()(Color& c, float& scale, float dt)
		{
			Scale::operator()( c, scale, dt );
			ColorEffect::operator()( c, scale, dt );
		}
	};
};