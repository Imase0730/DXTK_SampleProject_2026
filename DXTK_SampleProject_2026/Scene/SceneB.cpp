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

// 更新
void SceneB::Update(Imase::ISceneController<SceneId>& sceneController, GameContext& gameContext)
{
	float elapsedTime = float(gameContext.timer.GetElapsedSeconds());

	elapsedTime;

	Keyboard::KeyboardStateTracker& tracker = gameContext.keyboardTracker;

	// スペースキーが押された
	if (tracker.pressed.Space)
	{
		// 次のシーンへ
		sceneController.RequestSwitch(SceneId::SceneA);
	}

	auto& debugFont = gameContext.debugFont;

	debugFont.AddString(L"SceneB", SimpleMath::Vector2(0.0f, 0.0f));

	// デバッグカメラの更新
	m_debugCamera->Update();
}

// 描画
void SceneB::Render(GameContext& gameContext) const
{
	auto context = gameContext.deviceResources.GetD3DDeviceContext();
	auto& states = gameContext.commonStates;

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

// シーン切り替え時に呼び出される関数
void SceneB::OnEnter(GameContext& gameContext)
{
	m_debugCamera = std::make_unique<Imase::DebugCamera>(1280, 720);

	auto device = gameContext.deviceResources.GetD3DDevice();
	auto context = gameContext.deviceResources.GetD3DDeviceContext();

	//	モデルのロード
	EffectFactory fx(device);
	fx.SetDirectory(L"Resources/Models");
	m_model = Model::CreateFromCMO(device, L"Resources/Models/Monkey.cmo", fx);

	// グリッドフロアの作成
	m_gridFloor = std::make_unique<Imase::GridFloor>(device, context, &gameContext.commonStates);
}
