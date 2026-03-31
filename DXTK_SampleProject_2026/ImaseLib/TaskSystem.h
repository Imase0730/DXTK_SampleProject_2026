#pragma once
#include "Task.h"
#include <unordered_map>
#include <queue>
#include <functional>

namespace Imase
{
    class TaskSystem
    {
    private:
        std::unique_ptr<Task> m_root;

        uint64_t m_nextID = 1;

        //--------------------------------
        // 遅延処理キュー
        //--------------------------------
        std::vector<std::function<void()>> m_pending;

        //--------------------------------
        // 検索
        //--------------------------------
        std::unordered_map<uint64_t, Task*> m_idMap;

    public:

        // コンストラクタ
        TaskSystem()
        {
            // ルートタスク作成
            m_root = std::make_unique<Task>();
            Register(m_root.get());
        }

        //--------------------------------
        // ID登録
        //--------------------------------
        void Register(Task* task)
        {
            task->SetSystem(this, m_nextID++);
            m_idMap[task->GetID()] = task;
        }

        //--------------------------------
        // タスク生成
        //--------------------------------
        template<class T, class... Args>
        T* AddTask(Args&&... args)
        {
            return AddChild(m_root.get(), std::forward<Args>(args)...);
        }

        template<class T, class... Args>
        T* AddChild(Task* parent, Args&&... args)
        {
            T* raw = nullptr;

            m_pending.emplace_back([=, &raw, this]()
                {
                    auto obj = std::make_unique<T>(args...);
                    raw = obj.get();

                    Register(raw);

                    obj->m_parent = parent;
                    parent->m_children.emplace_back(std::move(obj));
                });

            return raw;
        }

        //--------------------------------
        // 親変更（遅延）
        //--------------------------------
        void ChangeParent(Task* t, Task* newParent)
        {
            m_pending.emplace_back([=]()
                {
                    if (!t || !newParent || t == newParent)
                        return;

                    // 循環防止
                    for (Task* p = newParent; p; p = p->m_parent)
                        if (p == t) return;

                    auto& siblings = t->m_parent->m_children;

                    auto it = std::find_if(
                        siblings.begin(), siblings.end(),
                        [&](const Task::Ptr& p)
                        {
                            return p.get() == t;
                        });

                    if (it == siblings.end()) return;

                    auto self = std::move(*it);
                    siblings.erase(it);

                    self->m_parent = newParent;
                    newParent->m_children.emplace_back(std::move(self));
                });
        }

        //--------------------------------
        // 更新
        //--------------------------------
        void Update(float dt)
        {
            m_root->UpdateTree(dt);

            // 遅延処理適用
            for (auto& func : m_pending)
            {
                func();
            }
            m_pending.clear();

            m_root->Cleanup();
        }

        //--------------------------------
        // 描画
        //--------------------------------
        void Render()
        {
            std::vector<Task*> list;
            m_root->Collect(list);

            // 描画順にソート
            std::sort(list.begin(), list.end(),
                [](Task* a, Task* b)
                {
                    return a->GetOt() < b->GetOt();
                });

            for (auto* task : list)
            {
                task->Render();
            }
        }

        //--------------------------------
        // 検索
        //--------------------------------
        Task* FindByID(uint64_t id)
        {
            auto it = m_idMap.find(id);
            return (it != m_idMap.end()) ? it->second : nullptr;
        }

        //--------------------------------
        // タグ検索（簡易）
        //--------------------------------
        std::vector<Task*> FindByTag(const std::wstring& tag)
        {
            std::vector<Task*> result;

            for (auto& [id, task] : m_idMap)
            {
                if (task->GetTag() == tag)
                    result.push_back(task);
            }

            return result;
        }
    };
}