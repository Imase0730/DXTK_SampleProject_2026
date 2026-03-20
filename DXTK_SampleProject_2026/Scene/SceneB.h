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
#include "SceneId.h"

class SceneB : public Imase::SceneBase<SceneId, GameContext>
{
public:

	// 更新
	void Update(Imase::ISceneController<SceneId>& sceneController, GameContext& gameContext) override;

	// 描画
	void Render(GameContext& gameContext) const override;

	// シーン切り替え時に呼び出される関数
	void OnEnter(GameContext& gameContext) override;

private:

	// モデル
	std::unique_ptr<DirectX::Model> m_model;

	// デバッグカメラ
	std::unique_ptr<Imase::DebugCamera> m_debugCamera;

	// グリッドフロア
	std::unique_ptr<Imase::GridFloor> m_gridFloor;

};

