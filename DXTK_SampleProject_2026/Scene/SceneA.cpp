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

// コンストラクタ
SceneA::SceneA(Imase::SceneManager<GameContext>* sceneManager)
	: Scene(sceneManager)
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// 更新処理
void SceneA::Update(float elapsedTime)
{
	elapsedTime;

	Keyboard::KeyboardStateTracker& tracker = GetGameContexts()->keyboardTracker;

	// スペースキーが押された
	if (tracker.pressed.Space)
	{
		// 次のシーンへ
		ChangeScene<SceneB>();
	}

	auto& debugFont = GetGameContexts()->debugFont;

	debugFont.AddString(L"SceneA", SimpleMath::Vector2(0.0f, 0.0f));
}

// 描画処理
void SceneA::Render()
{
	auto& states = GetGameContexts()->commonStates;

	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	// スプライトの描画
	m_spriteBatch->Draw(m_texture.Get(), SimpleMath::Vector2(100.0f, 100.0f));

	m_spriteBatch->End();
}

// デバイスに依存するリソースを作成する関数
void SceneA::CreateDeviceDependentResources()
{
	auto device = GetGameContexts()->deviceResources.GetD3DDevice();
	auto context = GetGameContexts()->deviceResources.GetD3DDeviceContext();

	// スプライトバッチの作成
	m_spriteBatch = std::make_unique<SpriteBatch>(context);

	// テクスチャのロード
	DX::ThrowIfFailed(
		CreateDDSTextureFromFile(device, L"Resources/Textures/ShootingGame.dds", nullptr, m_texture.ReleaseAndGetAddressOf())
	);

}

// ウインドウサイズに依存するリソースを作成する関数
void SceneA::CreateWindowSizeDependentResources()
{
}

// デバイスロストした時に呼び出される関数
void SceneA::OnDeviceLost()
{
}


