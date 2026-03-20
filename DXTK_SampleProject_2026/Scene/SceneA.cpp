//--------------------------------------------------------------------------------------
// File: SceneA.cpp
//
// サンプルシーンクラス
//
// Date: 2026.2.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SceneA.h"
#include "SceneB.h"

using namespace DirectX;

// 更新
void SceneA::Update(Imase::ISceneController<SceneId>& sceneController, GameContext& gameContext)
{
	float elapsedTime = float(gameContext.timer.GetElapsedSeconds());

	elapsedTime;

	Keyboard::KeyboardStateTracker& tracker = gameContext.keyboardTracker;

	// スペースキーが押された
	if (tracker.pressed.Space)
	{
		// 次のシーンへ
		sceneController.RequestSwitch(SceneId::SceneB);
	}

	auto& debugFont = gameContext.debugFont;

	debugFont.AddString(L"SceneA", SimpleMath::Vector2(0.0f, 0.0f));
}

// 描画
void SceneA::Render(GameContext& gameContext) const
{
	auto& states = gameContext.commonStates;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	// スプライトの描画
	m_spriteBatch->Draw(m_texture.Get(), SimpleMath::Vector2(100.0f, 100.0f));

	m_spriteBatch->End();
}

// シーン切り替え時に呼び出される関数
void SceneA::OnEnter(GameContext& gameContext)
{
	auto device = gameContext.deviceResources.GetD3DDevice();
	auto context = gameContext.deviceResources.GetD3DDeviceContext();

	// スプライトバッチの作成
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	// テクスチャのロード
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Resources/Textures/ShootingGame.dds", nullptr, m_texture.ReleaseAndGetAddressOf())
	);
}
