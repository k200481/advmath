#include "World.h"

#include "LinearAlgebra.h"

World::World(float width, float height, int nEntities, std::mt19937& rng)
	:
	width( width ),
	height( height )
{
	const std::uniform_int_distribution<int> nFlaresDist( 2, 10 );
	const std::uniform_real_distribution<float> innerRadDist( 50, 100 );
	const std::uniform_real_distribution<float> outerRadDist( 100, 150 );
	for ( int i = 0; i < nEntities; ) {

		const float innerRadius = innerRadDist( rng );
		const float outerRadius = outerRadDist( rng );
		const int nFlares = nFlaresDist( rng );
		
		const std::uniform_real_distribution<float> xDist( (-width / 2) - 1 + outerRadius, (+width / 2) - 1 - outerRadius );
		const std::uniform_real_distribution<float> yDist( (-height / 2) - 1 + outerRadius, (+height / 2) - 1 - outerRadius );

		Vec2 pos;
		pos.x = xDist( rng );
		pos.y = yDist( rng );

		Entity newEntity( Star::Make(outerRadius, innerRadius, nFlares), pos );

		bool isOverlapping = false;
		for ( auto& e : entities )
		{
			if ( PolyLinesIntersect(e.GetModel(), newEntity.GetModel()) )
			{
				isOverlapping = true;
			}
		}
		
		if ( !isOverlapping )
		{
			entities.push_back( std::move(newEntity) );
			i++;
		}
	}
}

void World::Update(float dt)
{
}

void World::Render(Camera& cam)
{
	for ( auto& e : entities ) {
		Drawable d = e.GetDrawable();
		cam.Draw( d );
	}
}
