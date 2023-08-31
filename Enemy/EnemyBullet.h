﻿#pragma once
#include "Model.h"
#include "Manager/Collider/Collider.h"
#include "Manager/Collider/CollisionConfig.h"
class Player;
class EnemyBullet : public Collider {
	public :
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	void Update();

	void Draw(const ViewProjection& view);

	bool isDead() const { return isDead_; }
	void SetPlayer(Player* player) { player_ = player; }
	void OnCollision() override;
	Vector3 GetWorldPos() override;
	bool SetAlive(bool alive) { return isDead_ = alive; }

private:
	WorldTransform worldTransform_;
	Model* model_;
	uint32_t texturehandle_;
	Vector3 velocity_;
	static const int32_t kLifeTime = 10 * 20;

	int32_t deathTimer_ = kLifeTime;
	Player* player_;

	bool isDead_ = false;


};
