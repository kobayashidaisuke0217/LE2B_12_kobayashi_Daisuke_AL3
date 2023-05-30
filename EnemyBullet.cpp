#include "EnemyBullet.h"
#include "Vector3Calc.h"
#include <assert.h>
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

assert(model);
	texturehandle_ = TextureManager::Load("enemyBullet.png");
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void EnemyBullet::Updarte() {
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& view) {
	model_->Draw(worldTransform_, view, texturehandle_);
}