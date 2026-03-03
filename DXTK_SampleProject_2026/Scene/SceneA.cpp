//--------------------------------------------------------------------------------------
// File: SampleScene.cpp
//
// サンプルシーンクラス
//
// Date: 2026.2.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "SampleScene.h"

using namespace DirectX;

// コンストラクタ
SampleScene::SampleScene()
{
}

// 初期化
void SampleScene::Initialize()
{
	CreateDeviceDependentResources();
	CreateWindowSizeDependentResources();
}

// 更新処理
void SampleScene::Update(float elapsedTime)
{
	elapsedTime;

	auto debugFont = GetUserResources()->GetDebugFont();

	debugFont->AddString(L"SampleScene", SimpleMath::Vector2(0.0f, 0.0f));
}

// 描画処理
void SampleScene::Render()
{
	auto debugFont = GetUserResources()->GetDebugFont();
	auto states = GetUserResources()->GetCommonStates();

	// デバッグ用文字列の描画
	debugFont->Render(states);
}

// 終了処理
void SampleScene::Finalize()
{
}

// デバイスに依存するリソースを作成する関数
void SampleScene::CreateDeviceDependentResources()
{
}

// ウインドウサイズに依存するリソースを作成する関数
void SampleScene::CreateWindowSizeDependentResources()
{
}

// デバイスロストした時に呼び出される関数
void SampleScene::OnDeviceLost()
{
	Finalize();
}


