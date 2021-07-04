#pragma once

#include "Entity.h"
#include "StarAnimations.h"
#include <random>

class StarEntity : public Entity
{
public:
	StarEntity( std::vector<Vec2> model, const Vec2& pos = { 0.0f, 0.0f }, Color c = Colors::Yellow )
		:
		Entity( model, pos, c )
	{
	}

	std::vector<Vec2> GetMaxModel() const
	{
		auto model = GetBaseModel();
		const auto pos = GetPos();

		for (auto& m : model)
		{
			m *= maxScale;
			m += pos;
		}
		return std::move(model);
	}

	void SetAnimationEffect(std::function<void(Color&, float&, float)> newEffect)
	{
		effect = newEffect;
	}
	void GiveRandomAnimationEffect( std::mt19937& rng )
	{
		const std::uniform_real_distribution<float> periodDist (0.5f, 1.5f );
		const std::uniform_int_distribution<int> colorDist( 0, 255 );

		const Color baseColor = { (unsigned char)colorDist(rng), (unsigned char)colorDist(rng), (unsigned char)colorDist(rng) };
		const Color targetColor = { (unsigned char)colorDist(rng), (unsigned char)colorDist(rng), (unsigned char)colorDist(rng) };
		//const Color targetColor = Colors::White;

		const std::vector<std::function<void( Color&, float&, float )>> effects =
		{
			StarAnimations::Scale( periodDist(rng) ),
			StarAnimations::ColorEffect( baseColor, targetColor, periodDist(rng) ),
			StarAnimations::ScaleAndColor( baseColor, targetColor, periodDist(rng) )
		};

		const std::uniform_int_distribution<int> effectDist( 0, (int) effects.size() - 1 );
		int effectIndex = effectDist( rng );

		effect = effects[ effectIndex ];
	}
	void Update(float dt)
	{
		Color c = GetColor();
		float scale = GetScale();

		effect(c, scale, dt);

		SetColor( c );
		SetScale( scale );
	}

private:
	static constexpr float maxScale = 1.5f;
	static constexpr float minScale = 0.5f;

private:
	std::function<void(Color&, float&, float)> effect;
};

