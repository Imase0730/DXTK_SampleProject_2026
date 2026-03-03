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

using namespace DirectX;

// コンストラクタ
SceneB::SceneB()
{
}

// 初期化
void SceneB::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// 更新処理
void SceneB::Update(float elapsedTime)
{
	elapsedTime;

	auto debugFont = GetGameContexts()->GetDebugFont();

	debugFont->AddString(L"SceneB", SimpleMath::Vector2(0.0f, 0.0f));
}

// 描画処理
void SceneB::Render()
{
	auto debugFont = GetGameContexts()->GetDebugFont();
	auto states = GetGameContexts()->GetCommonStates();

	// デバッグ用文字列の描画
	debugFont->Render(states);
}

// 終了処理
void SceneB::Finalize()
{
}

// デバイスに依存するリソースを作成する関数
void SceneB::CreateDeviceDependentResources()
{
}

// ウインドウサイズに依存するリソースを作成する関数
void SceneB::CreateWindowSizeDependentResources()
{
}

// デバイスロストした時に呼び出される関数
void SceneB::OnDeviceLost()
{
	Finalize();
}


