#pragma once

#include <vector>
#include "Vec2.h"
#include <cassert>


class LineSegment {
public:
	LineSegment( const Vec2& pt1, const Vec2& pt2  )
		:
		pt1( pt1 ),
		pt2( pt2 )
	{
	}
	float CalculateGradient() const
	{
		assert( !IsVertical() );
		return (pt2.y - pt1.y) / (pt2.x - pt1.x);
	}
	float CalculateYIntercept() const
	{
		assert( !IsVertical() );
		return pt1.y - CalculateGradient() * pt1.x;
	}
	bool IsVertical() const
	{
		return pt1.y == pt2.y;
	}

	bool Intersects(const LineSegment& other) const
	{
		if (IsVertical())
		{
			if (other.IsVertical())
			{
				// not handling this case for now
				return pt1.x == other.pt1.x;
			}
			
			float intersectionY = other.CalculateGradient() * pt1.x + other.CalculateYIntercept();
			if (intersectionY >= std::min(pt1.y, pt2.y) && intersectionY <= std::max(pt1.y, pt2.y) &&
				intersectionY >= std::min(other.pt1.y, other.pt2.y) && intersectionY <= std::max(other.pt1.y, other.pt2.y))
			{
				return true;
			}
			return false;
		}
		else
		{
			if (other.IsVertical())
			{
				float intersectionY = CalculateGradient() * other.pt1.x + CalculateYIntercept();
				return intersectionY >= std::min(pt1.y, pt2.y) &&
					intersectionY <= std::max(pt1.y, pt2.y) &&
					intersectionY >= std::min(other.pt1.y, other.pt2.y) &&
					intersectionY <= std::max(other.pt1.y, other.pt2.y);
			}
			else
			{
				const float m0 = CalculateGradient();
				const float m1 = other.CalculateGradient();
				const float c0 = CalculateYIntercept();
				const float c1 = other.CalculateYIntercept();
				if (m0 == m1)
				{
					return c0 == c1;
				}
				else
				{
					const float intersectionX = (c1 - c0) / (m0 - m1);
					return intersectionX >= std::min(pt1.x, pt2.x) &&
						intersectionX <= std::max(pt1.x, pt2.x) &&
						intersectionX >= std::min(other.pt1.x, other.pt2.x) &&
						intersectionX <= std::max(other.pt1.x, other.pt2.x);
				}
			}
		}
	}

private:
	Vec2 pt1;
	Vec2 pt2;
};

bool PolyLinesIntersect(const std::vector<Vec2>& poly1, const std::vector<Vec2>& poly2);