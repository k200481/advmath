#include "World.h"

World::World(float width, float height, int nEntities, std::mt19937& rng)
	:
	width( width ),
	height( height )
{
	for ( int i = 0; i < nEntities; i++ ) {

		const float innerRadius = 10 + rng() % 89;
		const float outerRadius = 20 + rng() % 80;
		const int nFlares = 2 + rng() % 8;
		
		std::uniform_real_distribution<float> xDist( -width / 2 + outerRadius, +width / 2 - outerRadius );
		std::uniform_real_distribution<float> yDist( -height / 2 + outerRadius, +height / 2 - outerRadius );

		Vec2 pos;
		pos.x = xDist( rng );
		pos.y = yDist( rng );

		entities.emplace_back( Star::Make( outerRadius, innerRadius, nFlares ), pos );
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
