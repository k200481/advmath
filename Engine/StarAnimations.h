#pragma once

#include "Colors.h"
#include "ChiliMath.h"

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
			const float alpha = abs(sin(seconds * 2 * PI / period));

			scale = interpolate( 0.5f, 1.0f, alpha );
		}

	private:
		float seconds = 0.0f;
		const float period = 1.0f;
	};

	class ColorEffect
	{
	public:
		ColorEffect( Color baseColor, Color destinationColor, float period )
			:
			baseColor( baseColor ),
			destinationColor( destinationColor )
		{
		}
		void operator()( Color& c, float& scale, float dt )
		{
			seconds += dt;
			const float alpha = abs( sin( seconds * 2 * PI / period ) );

			c = interpolate( baseColor.dword, destinationColor.dword, alpha );
		}
	private:
		float seconds = 0.0f;
		const float period = 1.0f;
		
		const Color baseColor;
		const Color destinationColor;
	};

	class ScaleAndColor 
	{
	public:
		ScaleAndColor(Color baseColor, Color destinationColor, float period)
			:
			baseColor(baseColor),
			destinationColor(destinationColor)
		{
		}
		void operator()(Color& c, float& scale, float dt)
		{
			seconds += dt;
			const float alpha = abs( sin(seconds * 2 * PI / period) );

			c = interpolate(baseColor.dword, destinationColor.dword, alpha);
			scale = interpolate(0.5f, 1.0f, alpha);
		}
	private:
		float seconds = 0.0f;
		const float period = 1.0f;

		const Color baseColor;
		const Color destinationColor;
	};
};