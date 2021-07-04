#include "World.h"

#include "LinearAlgebra.h"
#include "StarAnimations.h"

World::World( std::mt19937& rng )
{
	const std::uniform_int_distribution<int> nFlaresDist( nMinFlares, nMaxFlares );
	const std::uniform_real_distribution<float> innerRadDist( minStarInnerRadius, maxStarInnerRadius );
	const std::uniform_real_distribution<float> outerRadDist( minStarOuterRadius, maxStarOuterRadius );

	for ( int i = 0; i < nStars; ) 
	{
		const float innerRadius = innerRadDist( rng );
		const float outerRadius = outerRadDist( rng );
		const int nFlares = nFlaresDist( rng );
		
		const std::uniform_real_distribution<float> xDist( (-width / 2) - 1 + outerRadius, (+width / 2) - 1 - outerRadius );
		const std::uniform_real_distribution<float> yDist( (-height / 2) - 1 + outerRadius, (+height / 2) - 1 - outerRadius );

		Vec2 pos;
		pos.x = xDist( rng );
		pos.y = yDist( rng );

		StarEntity newEntity( outerRadius, innerRadius, nFlares, pos );
		newEntity.GiveRandomAnimationEffect( rng );

		if (std::any_of( entities.begin(), entities.end(),
				[&](const StarEntity& e) {
				bool isInside = ( e.GetPos() - newEntity.GetPos() ).Len() <= 
						( e.GetMaxInnerRadius() + newEntity.GetMaxInnerRadius() );
					return isInside || PolyLinesIntersect(e.GetMaxModel(), newEntity.GetMaxModel());
				}
			)
		)
		{
			continue;
		}
		
		entities.push_back( std::move(newEntity) );
		i++;
	}
}

void World::Update( float dt )
{
	for ( auto& e : entities )
	{
		e.Update( dt );
	}
}

void World::Render( Camera& cam )
{
	_Rect camRect = cam.GetRect();
	std::vector<Vec2> camBorders = {
		{ camRect.left, camRect.top },
		{ camRect.right, camRect.top },
		{ camRect.right, camRect.bottom },
		{ camRect.left, camRect.bottom }
	};

	for (auto& e : entities)
	{
		if ( camRect.ContainsPoint(e.GetPos()) || PolyLinesIntersect(e.GetCurrentModel(), camBorders) )
		{
			Drawable d = e.GetDrawable();
			cam.Draw( d );
		}
	}
}
