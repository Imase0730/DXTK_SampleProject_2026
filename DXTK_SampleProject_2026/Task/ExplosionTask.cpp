//--------------------------------------------------------------------------------------
// File: ExplosionTask.cpp
//
// 爆発エフェクトタスク
//
// Date: 2026.4.10
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "ExplosionTask.h"

using namespace DirectX;

// コンストラクタ
ExplosionTask::ExplosionTask(
    const GameContext& gameContext,
    DirectX::SpriteBatch& spriteBatch,
    ID3D11ShaderResourceView* pTexture,
    DirectX::SimpleMath::Vector2 position
)
    : m_gameContext(gameContext)
    , m_spriteBatch(spriteBatch)
    , m_pTexture(pTexture)
    , m_position(position)
{
    // タグを設定
    SetTag(L"Explosion");
}

// 更新
bool ExplosionTask::Update(float elapsedTime)
{
    return true;
}

// 描画
void ExplosionTask::Render()
{
    // テクスチャ上の矩形
    RECT srcRect = { 96, 0, 96 + 32, 32 };

    // 敵の描画（2倍の大きさで表示）
    m_spriteBatch.Draw(m_pTexture, m_position, &srcRect, Colors::White, 0.0f, { 0.0f, 0.0f }, 2.0f);
}
