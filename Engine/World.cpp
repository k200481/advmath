#include "World.h"

#include "LinearAlgebra.h"
#include "StarAnimations.h"

World::World(float width, float height, int nEntities, std::mt19937& rng)
	:
	width( width ),
	height( height )
{
	const std::uniform_int_distribution<int> nFlaresDist( 2, 10 );
	const std::uniform_real_distribution<float> innerRadDist( 50, 200 );
	const std::uniform_real_distribution<float> outerRadDist( 150, 300 );

	for ( int i = 0; i < nEntities; ) 
	{
		const float innerRadius = innerRadDist( rng );
		const float outerRadius = outerRadDist( rng );
		const int nFlares = nFlaresDist( rng );
		
		const std::uniform_real_distribution<float> xDist( (-width / 2) - 1 + outerRadius, (+width / 2) - 1 - outerRadius );
		const std::uniform_real_distribution<float> yDist( (-height / 2) - 1 + outerRadius, (+height / 2) - 1 - outerRadius );
		const std::uniform_real_distribution<float> periodDist( 0.1f, 5.0f );
		const std::uniform_int_distribution<int> colorDist( 0, 255 );

		std::vector<std::function<void(Color&, float&, float)>> effects =
		{
			StarAnimations::Scale( periodDist( rng ) ),
			StarAnimations::ColorEffect( 
				{(unsigned char)colorDist(rng), (unsigned char)colorDist(rng), (unsigned char)colorDist(rng)},
				{(unsigned char)colorDist(rng), (unsigned char)colorDist(rng), (unsigned char)colorDist(rng)},
				periodDist(rng)
			),
			StarAnimations::ScaleAndColor(
				{(unsigned char)colorDist(rng), (unsigned char)colorDist(rng), (unsigned char)colorDist(rng)},
				{(unsigned char)colorDist(rng), (unsigned char)colorDist(rng), (unsigned char)colorDist(rng)},
				periodDist(rng)
			)
		};

		const std::uniform_int_distribution<int> effectDist(0, effects.size() - 1);

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
			int effectIndex = effectDist( rng );
			entities[i].SetEffect( effects[effectIndex] );

			i++;
		}
	}
}

void World::Update(float dt)
{
	for ( auto& e : entities )
	{
		e.Update( dt );
	}
}

void World::Render(Camera& cam)
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
		if ( camRect.ContainsPoint(e.GetPos()) || PolyLinesIntersect(e.GetModel(), camBorders) )
		{
			Drawable d = e.GetDrawable();
			cam.Draw( d );
		}
	}
}
