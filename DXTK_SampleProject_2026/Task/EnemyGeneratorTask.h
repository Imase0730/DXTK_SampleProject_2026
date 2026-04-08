//--------------------------------------------------------------------------------------
// File: EnemyGeneratorTask.h
//
// 敵生成タスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../ImaseLib/Task.h"
#include "../Scene/GameContext.h"

class EnemyGeneratorTask : public Imase::Task
{
public:


private:


public:

	// コンストラクタ
	EnemyGeneratorTask(
		const GameContext& gameContext,
		DirectX::SpriteBatch& spriteBatch,
		ID3D11ShaderResourceView* pTexture
	);

	// 更新
	bool Update(float elapsedTime) override;

private:

	// ゲームコンテキストへのポインタ
	const GameContext& m_gameContext;

	// スプライトバッチへのポインタ
	DirectX::SpriteBatch& m_spriteBatch;

	// テクスチャへのポインタ
	ID3D11ShaderResourceView* m_pTexture;

};