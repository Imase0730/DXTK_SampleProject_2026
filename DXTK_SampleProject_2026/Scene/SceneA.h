//--------------------------------------------------------------------------------------
// File: SceneA.h
//
// サンプルシーンクラス
//
// Date: 2026.2.24
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "ImaseLib/SceneManager.h"
#include "GameContext.h"
#include "SceneId.h"
#include "ImaseLib/TaskSystem.h"
#include "Task/PlayerTask.h"
#include "CollisionManager.h"

class SceneA : public Imase::SceneBase<SceneId, GameContext>
{
public:

	// 更新
	void Update(Imase::ISceneController<SceneId>& sceneController, GameContext& gameContext) override;

	// 描画
	void Render(GameContext& gameContext) override;

	// シーン切り替え時に呼び出される関数
	void OnEnter(GameContext& gameContext) override;

private:

	// タスクシステム
	Imase::TaskSystem m_taskSystem;

	// スプライトバッチ
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// シェーダーリソースビュー
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// プレイヤータスクへのポインタ
	PlayerTask* m_playerTask = nullptr;

	// 当たり判定を行うマネージャー
	CollisionManager m_collisionManager;
};

