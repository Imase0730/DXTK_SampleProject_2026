//--------------------------------------------------------------------------------------
// File: PlayerTask.h
//
// プレイヤータスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../ImaseLib/Task.h"
#include "../Scene/GameContext.h"

class PlayerTask : public Imase::Task
{
public:

	// 大きさ(dot)
	static constexpr int SIZE = 64;

	// 移動の速さ(dot/s)
	static constexpr int SPEED = 300;

private:

	// 発射した弾の数
	int m_bulletCount = 0;

	// 画面上の弾の最大数
	static constexpr int MAX_BULLET = 3;

public:

	// コンストラクタ
	PlayerTask(
		GameContext* pGameContext,
		DirectX::SpriteBatch* pSpriteBatch,
		ID3D11ShaderResourceView* pTexture
	);

	// 更新
	bool Update(float elapsedTime) override;

	// 描画
	void Render() override;

	// 位置を設定する関数
	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

private:

	// ゲームコンテキストへのポインタ
	GameContext* m_pGameContext = nullptr;

	// スプライトバッチへのポインタ
	DirectX::SpriteBatch* m_pSpriteBatch = nullptr;

	// テクスチャへのポインタ
	ID3D11ShaderResourceView* m_pTexture = nullptr;

	// 位置
	DirectX::SimpleMath::Vector2 m_position = { 0.0f, 0.0f };

};