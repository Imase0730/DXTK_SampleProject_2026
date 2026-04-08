//--------------------------------------------------------------------------------------
// File: EnemyTask.h
//
// 敵タスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

#include "../ImaseLib/Task.h"
#include "../Scene/GameContext.h"
#include "GameTypes.h"

class EnemyTask : public Imase::Task, public IFaction
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
	EnemyTask(
		const GameContext& gameContext,
		DirectX::SpriteBatch& spriteBatch,
		ID3D11ShaderResourceView* pTexture
	);

	// デストラクタ
	~EnemyTask();

	// 更新
	bool Update(float elapsedTime) override;

	// 描画
	void Render() override;

	// 位置を設定する関数
	void SetPosition(DirectX::SimpleMath::Vector2 position) { m_position = position; }

	// 消滅した時に呼び出される関数を設定する関数
	void SetOnDestroy(std::function<void()> func)
	{
		m_onDestroy = func;
	}

	// 当たり判定用のグループを取得する関数
	Faction GetFaction() const override
	{
		return Faction::Enemy;
	}

private:

	// ゲームコンテキストへのポインタ
	const GameContext& m_gameContext;

	// スプライトバッチへのポインタ
	DirectX::SpriteBatch& m_spriteBatch;

	// テクスチャへのポインタ
	ID3D11ShaderResourceView* m_pTexture;

	// 消滅した時に呼び出される関数
	std::function<void()> m_onDestroy;

	// 位置
	DirectX::SimpleMath::Vector2 m_position = { 0.0f, 0.0f };



};