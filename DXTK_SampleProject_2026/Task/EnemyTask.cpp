//--------------------------------------------------------------------------------------
// File: EnemyTask.cpp
//
// 敵タスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "EnemyTask.h"
#include "BulletTask.h"

using namespace DirectX;

// コンストラクタ
EnemyTask::EnemyTask(
    const GameContext& gameContext,
    DirectX::SpriteBatch& spriteBatch,
    ID3D11ShaderResourceView* pTexture
)
    : m_gameContext(gameContext)
    , m_spriteBatch(spriteBatch)
    , m_pTexture(pTexture)
{
    // タグを設定
    SetTag(L"Enemy");
}

// デストラクタ
EnemyTask::~EnemyTask()
{
    if (m_onDestroy)
    {
        // 敵が消滅した時に呼び出される関数を実行
        m_onDestroy();
    }
}

// 更新
bool EnemyTask::Update(float elapsedTime)
{
    // 下へ移動
    m_position.y += SPEED * elapsedTime;

    // 画面外へ出たらタスクを消去
    RECT rect = m_gameContext.deviceResources.GetOutputSize();
    float moveBottomMax = static_cast<float>(rect.bottom);
    if (m_position.y > moveBottomMax)
    {
        return false;
    }

    return true;
}

// 描画
void EnemyTask::Render()
{
    // テクスチャ上の矩形
    RECT srcRect = { 96, 0, 96 + 32, 32 };

    // 敵の描画（2倍の大きさで表示）
    m_spriteBatch.Draw(m_pTexture, m_position, &srcRect, Colors::White, 0.0f, { 0.0f, 0.0f }, 2.0f);
}

