//--------------------------------------------------------------------------------------
// File: SceneB.cpp
//
// サンプルシーンクラス
//
// Date: 2026.3.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SceneB.h"
#include "SceneA.h"

using namespace DirectX;

// コンストラクタ
SceneB::SceneB(Imase::SceneManager<GameContext>* sceneManager)
	: Scene(sceneManager)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();

	// デバッグ用カメラの作成
	m_debugCamera = std::make_unique<Imase::DebugCamera>(1280, 720);
}

// 更新処理
void SceneB::Update(float elapsedTime)
{
	elapsedTime;

	Keyboard::KeyboardStateTracker& tracker = GetGameContexts()->keyboardTracker;

	// スペースキーが押された
	if (tracker.pressed.Space)
	{
		// 次のシーンへ
		ChangeScene<SceneA>();
	}

	auto& debugFont = GetGameContexts()->debugFont;

	debugFont.AddString(L"SceneB", SimpleMath::Vector2(0.0f, 0.0f));

	// デバッグカメラの更新
	m_debugCamera->Update();
}

// 描画処理
void SceneB::Render()
{
	auto context = GetGameContexts()->deviceResources.GetD3DDeviceContext();
	auto& states = GetGameContexts()->commonStates;

	// モデルの描画
	SimpleMath::Matrix world;
	SimpleMath::Matrix view = m_debugCamera->GetCameraMatrix();
	SimpleMath::Matrix projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		1280.0f / 720.0f,
		0.1f,
		100.0f
	);
	m_model->Draw(context, states, world, view, projection);

	// グリッドフロアの描画
	m_gridFloor->Render(context, view, projection);
}

// デバイスに依存するリソースを作成する関数
void SceneB::CreateDeviceDependentResources()
{
	auto device = GetGameContexts()->deviceResources.GetD3DDevice();
	auto context = GetGameContexts()->deviceResources.GetD3DDeviceContext();

	//	モデルのロード
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Models");
	m_model = Model::CreateFromCMO(device, L"Resources/Models/Monkey.cmo", fx);

	// グリッドフロアの作成
	m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, &GetGameContexts()->commonStates);
}

// ウインドウサイズに依存するリソースを作成する関数
void SceneB::CreateWindowSizeDependentResources()
{
}

// デバイスロストした時に呼び出される関数
void SceneB::OnDeviceLost()
{
}


