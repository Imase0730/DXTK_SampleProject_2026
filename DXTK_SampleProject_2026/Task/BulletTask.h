//--------------------------------------------------------------------------------------
// File: BulletTask.h
//
// 弾タスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../ImaseLib/Task.h"
#include "../Scene/GameContext.h"

class PlayerTask;

class BulletTask : public Imase::Task
{
public:

	// 大きさ(dot)
	static constexpr int SIZE = 16;

public:

	// コンストラクタ
	BulletTask(
		GameContext* pGameContext,
		DirectX::SpriteBatch* pSpriteBatch,
		ID3D11ShaderResourceView* pTexture,
		DirectX::SimpleMath::Vector2 position,
		DirectX::SimpleMath::Vector2 velocity
	);

	// デストラクタ
	~BulletTask();

	// 更新
	bool Update(float elapsedTime) override;

	// 描画
	void Render() override;

	// 消滅した時に呼び出される関数を設定する関数
	void SetOnDestroy(std::function<void()> func)
	{
		m_onDestroy = func;
	}

private:

	// ゲームコンテキストへのポインタ
	GameContext* m_pGameContext = nullptr;

	// スプライトバッチへのポインタ
	DirectX::SpriteBatch* m_pSpriteBatch = nullptr;

	// テクスチャへのポインタ
	ID3D11ShaderResourceView* m_pTexture = nullptr;

	// 消滅した時に呼び出される関数
	std::function<void()> m_onDestroy;

	// 位置
	DirectX::SimpleMath::Vector2 m_position = { 0.0f, 0.0f };

	// 速度(dot/s)
	DirectX::SimpleMath::Vector2 m_velocity = { 0.0f, 0.0f };

};