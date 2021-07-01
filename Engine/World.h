#pragma once

#include <vector>
#include <random>

#include "_Rect.h"

#include "Entity.h"
#include "Star.h"

#include "Camera.h"
#include "MouseCameraController.h"

class World
{
public:
	World( float width, float height, int nEntities, std::mt19937& rng );
	void Update( float dt );
	void Render( Camera& cam );

private:
	const float width;
	const float height;
	std::vector<Entity> entities;
};

