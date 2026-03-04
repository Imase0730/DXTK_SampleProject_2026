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
}

// 描画処理
void SceneB::Render()
{
	auto context = GetGameContexts()->deviceResources.GetD3DDeviceContext();
	auto& debugFont = GetGameContexts()->debugFont;
	auto& states = GetGameContexts()->commonStates;

	// モデルの描画
	SimpleMath::Matrix world;
	SimpleMath::Matrix view = SimpleMath::Matrix::CreateLookAt(
		SimpleMath::Vector3(0.0f, 2.0f, 5.0f),
		SimpleMath::Vector3(0.0f, 0.0f, 0.0f),
		SimpleMath::Vector3::Up
	);
	SimpleMath::Matrix projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		1280.0f / 720.0f,
		0.1f,
		100.0f
	);
	m_model->Draw(context, states, world, view, projection);
}

// デバイスに依存するリソースを作成する関数
void SceneB::CreateDeviceDependentResources()
{
	auto device = GetGameContexts()->deviceResources.GetD3DDevice();

	//	モデルのロード
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Models");
	m_model = Model::CreateFromCMO(device, L"Resources/Models/Monkey.cmo", fx);
}

// ウインドウサイズに依存するリソースを作成する関数
void SceneB::CreateWindowSizeDependentResources()
{
}

// デバイスロストした時に呼び出される関数
void SceneB::OnDeviceLost()
{
}


