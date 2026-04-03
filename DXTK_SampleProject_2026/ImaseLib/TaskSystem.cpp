//--------------------------------------------------------------------------------------
// File: TaskSystem.cpp
//
// シーンシステムクラス
//
// Date: 2026.4.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "TaskSystem.h"
#include "Task.h"
#include <algorithm>

namespace Imase
{
    // コンストラクタ
    TaskSystem::TaskSystem()
    {
        // ルートタスク作成
        m_root = std::make_unique<Task>();
        m_root->SetSystem(this, m_nextID++);
    }

    // デストラクタ
    // デストラクタに=defaultを付ける理由
    // ムーブコンストラクタやコピーコンストラクタを明示的に定義した際、
    // デストラクタが暗黙的に生成されなくなる（または動作が変わる）のを防ぐ
    // メンバ変数に前方参照のクラスのunique_ptrがある場合cpp側にデストラクタを記述する
    TaskSystem::~TaskSystem() = default;

    // 子の追加
    void TaskSystem::RequestAddChild(Task* parent, std::unique_ptr<Task> child)
    {
        m_pendingAdd.push_back({ parent, std::move(child) });
    }

    // 親の変更
    void TaskSystem::RequestChangeParent(Task* t, Task* newParent)
    {
        m_pendingChangeParent.push_back({ t, newParent });
    }

    // 更新
    void TaskSystem::Update(float dt)
    {
        // 更新
        m_root->UpdateTree(dt);

        //--------------------------------
        // AddChild適用
        //--------------------------------
        for (auto& p : m_pendingAdd)
        {
            // 親が無効 or 死んでいるなら無視
            if (!p.parent || p.parent->IsKill()) continue;

            // 親を設定
            p.child->m_parent = p.parent;

            // ID登録
            p.child->SetSystem(this, m_nextID++);

            // 親の子に追加
            p.parent->m_children.emplace_back(std::move(p.child));
        }
        m_pendingAdd.clear();

        //--------------------------------
        // 死んでいるタスクを削除
        //--------------------------------
        m_root->Cleanup();

        //--------------------------------
        // ChangeParent適用
        //--------------------------------
        for (auto& p : m_pendingChangeParent)
        {
            Task* t = p.task;
            Task* newParent = p.newParent;

            // 無効チェック
            if (!t || !newParent || t == newParent) continue;

            // 死亡チェック
            if (t->IsKill() || newParent->IsKill()) continue;

            // rootは変更不可
            if (!t->m_parent) continue;

            //--------------------------------
            // 循環防止
            //--------------------------------
            for (Task* cur = newParent; cur; cur = cur->m_parent)
            {
                if (cur == t)
                {
                    newParent = nullptr;
                    break;
                }
            }
            if (!newParent) continue;

            //--------------------------------
            // 元親から取り外し
            //--------------------------------
            auto& siblings = t->m_parent->m_children;

            auto it = std::find_if(
                siblings.begin(),
                siblings.end(),
                [t](const Task::Ptr& ptr)
                {
                    return ptr.get() == t;
                });

            if (it == siblings.end())
                continue;

            //--------------------------------
            // 所有権移動
            //--------------------------------
            Task::Ptr self = std::move(*it);
            siblings.erase(it);

            //--------------------------------
            // 新しい親へ
            //--------------------------------
            self->m_parent = newParent;
            newParent->m_children.emplace_back(std::move(self));
        }
        m_pendingChangeParent.clear();
    }

    // 描画
    void TaskSystem::Render()
    {
        // 表示＆生きているタスクのリスト作成（親→子）
        std::vector<Task*> list;
        m_root->Collect(list);

        // 描画順をソート
        std::stable_sort(list.begin(), list.end(),
            [](Task* a, Task* b)
            {
                return a->GetOt() < b->GetOt();
            });

        // 描画
        for (auto* task : list)
        {
            if (!task->IsKill())
            {
                task->Render();
            }
        }
    }
}