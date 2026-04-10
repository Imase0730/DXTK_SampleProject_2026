//--------------------------------------------------------------------------------------
// File: ExplosionTask.h
//
// 爆発エフェクトタスク
//
// Date: 2026.4.10
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../ImaseLib/Task.h"
#include "../Scene/GameContext.h"

class ExplosionTask : public Imase::Task
{
public:

	// 大きさ(dot)
	static constexpr int SIZE = 64;

	// 移動の速さ(dot/s)
	static constexpr int SPEED = 300;

	// 弾の発射の速さ(dot/s)
	static constexpr int BULLET_SPEED = 500;

private:

	// 弾の発射間隔
	static constexpr float SHOOT_INTERVAL = 1.0f;

public:

	// コンストラクタ
	ExplosionTask(
		const GameContext& gameContext,
		DirectX::SpriteBatch& spriteBatch,
		ID3D11ShaderResourceView* pTexture,
		DirectX::SimpleMath::Vector2 position
	);

	// 更新
	bool Update(float elapsedTime) override;

	// 描画
	void Render() override;

private:

	// ゲームコンテキストへのポインタ
	const GameContext& m_gameContext;

	// スプライトバッチへのポインタ
	DirectX::SpriteBatch& m_spriteBatch;

	// テクスチャへのポインタ
	ID3D11ShaderResourceView* m_pTexture;

	// 位置
	DirectX::SimpleMath::Vector2 m_position = { 0.0f, 0.0f };

	// 弾の発射用のタイマー
	float m_shootTimer = 0.0f;

};