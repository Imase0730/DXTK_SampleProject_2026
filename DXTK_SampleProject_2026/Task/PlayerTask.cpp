//--------------------------------------------------------------------------------------
// File: PlayerTask.cpp
//
// プレイヤータスク
//
// Date: 2026.4.5
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "PlayerTask.h"
#include "BulletTask.h"

using namespace DirectX;

// コンストラクタ
PlayerTask::PlayerTask(
    const GameContext& gameContext,
    DirectX::SpriteBatch& spriteBatch,
    ID3D11ShaderResourceView* pTexture
)
    : m_gameContext(gameContext)
    , m_spriteBatch(spriteBatch)
    , m_pTexture(pTexture)
{
    // タグを設定
    SetTag(L"Player");
}

// 更新
bool PlayerTask::Update(float elapsedTime)
{
    auto kb = Keyboard::Get().GetState();
    
    // 左キー
    if (kb.Left)
    {
        // 左に移動
        m_position.x -= SPEED * elapsedTime;
    }

    // 右キー
    if (kb.Right)
    {
        // 右に移動
        m_position.x += SPEED * elapsedTime;
    }

    // Zキー
    if (m_gameContext.keyboardTracker.pressed.Z)
    {
        // 弾数制限
        if (m_bulletCount < MAX_BULLET)
        {
            // 弾タスクを生成
            BulletTask* bullet = AddChild<BulletTask>(
                m_gameContext,
                m_spriteBatch,
                m_pTexture,
                SimpleMath::Vector2(m_position.x + (PlayerTask::SIZE - BulletTask::SIZE) / 2, m_position.y),
                SimpleMath::Vector2(0.0f, -300.0f),
                Faction::Player
            );
            // 弾タスクが消滅した時に呼び出される関数を登録
            bullet->SetOnDestroy([this]()
                {
                    m_bulletCount--;
                });
            // 弾の数を加算
            m_bulletCount++;
        }
    }

    // 画面外へ行かないようにX座標を補正
    RECT rect = m_gameContext.deviceResources.GetOutputSize();
    float moveRightMax = static_cast<float>(rect.left);
    if (m_position.x < moveRightMax)
    {
        m_position.x = moveRightMax;
    }
    float moveLeftMax = static_cast<float>(rect.right - PlayerTask::SIZE);
    if (m_position.x > moveLeftMax)
    {
        m_position.x = moveLeftMax;
    }

    return true;
}

// 描画
void PlayerTask::Render()
{
    // テクスチャ上の矩形
    RECT srcRect = { 0, 0, 32, 32 };

    // プレイヤーの描画（2倍の大きさで表示）
    m_spriteBatch.Draw(m_pTexture, m_position, &srcRect, Colors::White, 0.0f, { 0.0f, 0.0f }, 2.0f);
}

