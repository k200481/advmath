#include "LinearAlgebra.h"

bool PolyLinesIntersect(const std::vector<Vec2>& poly1, const std::vector<Vec2>& poly2)
{
	const int size1 = poly1.size();
	const int size2 = poly2.size();

	for (int i = 0; i < size1; i += 1)
	{
		const LineSegment ls1 = { poly1[i], poly1[(i + 1) % size1] };
		for (int j = 0; j < size2; j += 1)
		{
			const LineSegment ls2 = { poly2[j], poly2[(j + 1) % size2] };
			if (ls1.Intersects(ls2))
			{
				return true;
			}
		}
	}
	return false;
}