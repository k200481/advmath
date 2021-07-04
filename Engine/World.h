#pragma once

#include <vector>
#include <random>

#include "_Rect.h"

#include "StarEntity.h"
#include "Star.h"

#include "Camera.h"
#include "MouseCameraController.h"

#include "LinearAlgebra.h"

class World
{
public:
	World( int nEntities, std::mt19937& rng );
	void Update( float dt );
	void Render( Camera& cam );

private:
	static constexpr float width = 10000.0f;
	static constexpr float height = 6000.0f;

	static constexpr float maxStarOuterRadius = 300.0f;
	static constexpr float minStarOuterRadius = 150.0f;
	
	static constexpr float maxStarInnerRadius = 200.0f;
	static constexpr float minStarInnerRadius = 50.0f;

	static constexpr int nMaxFlares = 10;
	static constexpr int nMinFlares = 2;
private:
	std::vector<StarEntity> entities;
};

