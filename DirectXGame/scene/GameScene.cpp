#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include"primitiveDrawer.h"
#include"ImGuiManager.h"
#include"AxisIndicator.h"

GameScene::GameScene() {}

GameScene::~GameScene() { delete debugCamera_; }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("sample.png");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});
	// 3dモデルの生成
	model_ = Model::Create();
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
	// サウンドデータの読み込み
	soundDataHandle_ = audio_->LoadWave("mokugyo.wav");
	// 音声再生
	audio_->PlayWave(soundDataHandle_);
	// 音声再生
	voiceHandle_ = audio_->PlayWave(soundDataHandle_, true);

	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewProjection_);

	debugCamera_ = new DebugCamera(1280, 720);

	//軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

}

void GameScene::Update() { 
	
		// スプライトの今の座標を取得
	Vector2 position = sprite_->GetPosition();
	// 座標を｛2，1｝移動
	position.x += 2.0f; // 毎回通るから継続移動
	position.y += 1.0f;
	// 移動した座標をスプライトに反映
	sprite_->SetPosition(position);
	// スペース押したとき
	if (input_->TriggerKey(DIK_SPACE)) {
		// 音声停止
		audio_->StopWave(voiceHandle_);
	}
	//デバッグカメラの更新
	debugCamera_->Update();

	
	#ifdef _DEBUG
	ImGui::Text("kamataTarou %d,%d,%d", 2050, 12, 31);

	ImGui::Begin("Debug1");
	ImGui::End();

	ImGui::InputFloat3("inputFloat3", inputFloat3);

	ImGui::SliderFloat3("SliderFloat3", inputFloat3, 0.0f, 1.0f);

	ImGui::ShowDemoWindow();
	#endif

}

void GameScene::Draw() {


	PrimitiveDrawer::GetInstance()->DrawLine3d({0, 0, 0}, {0, 10, 0}, {1.0f, 0.0f, 0.0f, 1.0f});
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
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	sprite_->Draw();



	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
