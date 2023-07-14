#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	delete collisionManager_;
	delete skyDome_;
	delete skyDomeModel_;
	delete railCamera_;
	for (EnemyBullet* bullet : enemyBullets_) {

		delete bullet;
	}
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textyreHandle_ = TextureManager::Load("sample.png");
	model_ = Model::Create();
	skyDomeModel_ = Model::CreateFromOBJ("SkyDome", true);
	viewProjection_.Initialize();
	player_ = new Player();
	Vector3 playerPos(0, 0, 30);
	player_->Initialize(model_, textyreHandle_,  playerPos);
	debugCamera_ = new DebugCamera(1280, 720);
	// 軸方向の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	
	Enemy* enemy = new Enemy();
	enemy->SetPlayer(player_);
	enemy->SetGameScene(this);
	enemy->Initialize(model_, {14, 0, 40}, {0, 0, -0.5});
	
	enemys_.push_back(enemy);
	collisionManager_ = new CollisionManager();
	skyDome_ = new SkyDome();
	skyDome_->Initialize(skyDomeModel_);
	railCamera_ = new RailCamera();
	railCamera_->Initialize({0.0f, 0.0f, 0.0f}, {0.0f,0.0f,0.0f});
	player_->Setparent(&railCamera_->GetWorldTransform());
}

void GameScene::Update() {

	player_->Update();
	
	debugCamera_->Update();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_RETURN)) {
		isDebugcameraActive_ = true;
	}
#endif
	// カメラの処理
	if (isDebugcameraActive_ == true) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		/*viewProjection_.UpdateMatrix();*/
		
	}
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->isDead()) {
			delete enemy;
			return true;
		}
		return false;
	});
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->isDead()) {
			delete bullet;
			return true;
		}
		return false;
	});
	for (EnemyBullet* bullet : enemyBullets_) {

		bullet->Updarte();
	}
	

	collisionManager_->ClearColliders();
	collisionManager_->AddCollider(player_);
	for (Enemy* enemy : enemys_) {
		collisionManager_->AddCollider(enemy);
	}
	for (PlayerBullet* pBullet : player_->GetBullets()) {
		collisionManager_->AddCollider(pBullet);
	}
	for (EnemyBullet* eBullet : enemyBullets_) {
		collisionManager_->AddCollider(eBullet);
	}
	collisionManager_->CheckAllCollision();
	skyDome_->Update();

}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	for (EnemyBullet* bullet : enemyBullets_) {

		bullet->Draw(viewProjection_);
	}
	player_->Draw(viewProjection_);
	skyDome_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) { enemyBullets_.push_back(enemyBullet); }

