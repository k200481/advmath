#pragma once
#include <cmath>
#include "Vec2.h"

#define PI 3.1418

template<typename T>
auto sq( T x )
{
	return x * x;
}

template<typename T>
T DistancePointLine( const _Vec2<T>& p0,const _Vec2<T>& p1,const _Vec2<T>& q )
{
	const T a = p0.y - p1.y;
	const T b = p1.x - p0.x;
	const T c = p0.x * p1.y - p1.x * p0.y;

	return std::abs( a * q.x + b * q.y + c ) / std::sqrt( sq( a ) + sq( b ) );
}

template<typename T>
_Vec2<T> PointOnPerpendicularBisector( const _Vec2<T>& p0, const _Vec2<T>& p1, const _Vec2<T>& pt )
{
	T m = ( p0.y - p1.y ) / ( p0.x - p1.x );
	T w = -1 / m;

	T c = p0.y - m * p0.x;
	T b = pt.y - w * pt.x;

	T x = ( b - c ) / ( m - w );
	T y = m * x + c;
	return { x, y };
}