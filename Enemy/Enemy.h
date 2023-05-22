#pragma once
#include "Model.h"
#include "Vector3Calc.h"
#include <WorldTransform.h>
class Enemy {

public:
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& view);

private:
	enum class Phase {
		Approach, // 接近
		Leave,    // 離脱

	};

	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	Phase phase_ = Phase::Approach;

	void Approach();
	void Leave();
	static void (Enemy::*EfuncTable[])();
};
