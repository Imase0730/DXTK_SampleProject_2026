//--------------------------------------------------------------------------------------
// File: SceneB.h
//
// サンプルシーンクラス
//
// Date: 2026.3.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "ImaseLib/SceneManager.h"
#include "ImaseLib/DebugCamera.h"
#include "ImaseLib/GridFloor.h"
#include "GameContext.h"

class SceneB : public Imase::Scene<GameContext>
{
public:
	
	// コンストラクタ
	SceneB(Imase::SceneManager<GameContext>* sceneManager);

	// 更新処理
	void Update(float elapsedTime) override;

	// 描画処理
	void Render() override;

	// デバイスに依存するリソースを作成する関数
	void CreateDeviceDependentResources() override;

	// ウインドウサイズに依存するリソースを作成する関数
	void CreateWindowSizeDependentResources() override;

	// デバイスロストした時に呼び出される関数
	void OnDeviceLost() override;

private:

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	// デバッグカメラ
	std::unique_ptr<Imase::DebugCamera> m_debugCamera;

	// グリッドフロア
	std::unique_ptr<Imase::GridFloor> m_gridFloor;

};

