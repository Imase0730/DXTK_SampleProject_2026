//--------------------------------------------------------------------------------------
// File: BulletTask.cpp
//
// 弾タスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "BulletTask.h"
#include "PlayerTask.h"

// コンストラクタ
BulletTask::BulletTask(
    const GameContext& gameContext,
    DirectX::SpriteBatch& spriteBatch,
    ID3D11ShaderResourceView* pTexture,
    DirectX::SimpleMath::Vector2 position,
    DirectX::SimpleMath::Vector2 velocity,
    Faction faction
)
    : m_gameContext(gameContext)
    , m_spriteBatch(spriteBatch)
    , m_pTexture(pTexture)
    , m_position(position)
    , m_velocity(velocity)
    , m_faction(faction)
{
    // タグを設定
    SetTag(L"Bullet");
}

// デストラクタ
BulletTask::~BulletTask()
{
    if (m_onDestroy)
    {
        // 弾が消滅した時に呼び出される関数を実行
        m_onDestroy();
    }
}

// 更新
bool BulletTask::Update(float elapsedTime)
{
    // 移動
    m_position += m_velocity * elapsedTime;

    // 画面外に弾が出たか？
    RECT rect = m_gameContext.deviceResources.GetOutputSize();
    float moveUpMax = static_cast<float>(rect.top - BulletTask::SIZE);
    float moveDownMax = static_cast<float>(rect.bottom);
    if ( (m_position.y < moveUpMax)		// 画面外に出たら（上部）
      || (m_position.y > moveDownMax)	// 画面外に出たら（下部）
       )
    {
        // 弾を消去
        return false;
    }
    return true;
}

// 描画
void BulletTask::Render()
{
    // テクスチャ上の矩形
    RECT srcRect = { 62, 32, 62 + 16, 32 + 16 };

    // 弾の描画
    m_spriteBatch.Draw(m_pTexture, m_position, &srcRect);
}
