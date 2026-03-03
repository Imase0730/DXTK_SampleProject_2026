//--------------------------------------------------------------------------------------
// File: SampleScene.h
//
// サンプルシーンクラス
//
// Date: 2026.2.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "ImaseLib/SceneManager.h"
#include "UserResources.h"

class SampleScene : public Imase::Scene<UserResources>
{
public:
	
	// コンストラクタ
	SampleScene();

	// 初期化
	void Initialize() override;

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

	// 終了処理
	void Finalize() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	void OnDeviceLost() override;

};

