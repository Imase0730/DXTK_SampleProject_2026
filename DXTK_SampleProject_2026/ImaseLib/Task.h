#pragma once
#include <vector>
#include <memory>
#include <string>
#include <cstdint>

namespace Imase
{
    class TaskSystem;

    class Task
    {
    public:
        using Ptr = std::unique_ptr<Task>;

    private:
        
        // タスクシステムへのポインタ
        TaskSystem* m_system = nullptr;
        
        // 親タスクへのポインタ
        Task* m_parent = nullptr;
        
        // 子タスクへのポインタの配列
        std::vector<Ptr> m_children;

        // ID
        uint64_t m_id = 0;

        // Updateを実行する場合はtrue
        bool m_active = true;
        // Renderを実行する場合はtrue
        bool m_visible = true;
        // 死んでいる場合はtrue
        bool m_kill = false;

        // 描画順
        int m_ot = 0;

    public:
        virtual ~Task() = default;

        //--------------------------------
        // オーバーライドして使用する関数
        //--------------------------------
        // 更新（戻り値がfalseの場合タスクが消える）
        virtual bool Update(float) { return true; }
        // 描画
        virtual void Render() {}

        //--------------------------------
        // 基本
        //--------------------------------
        
        // タスクを殺す関数
        void Kill() { m_kill = true; }
        // タスクが死んでいるか調べる関数
        bool IsKill() const { return m_kill; }
        
        // 描画順を設定
        void SetOt(int v) { m_ot = v; }
        // 描画順を取得
        int GetOt() const { return m_ot; }

        //--------------------------------
        // 子生成（テンプレート）
        //--------------------------------
        template<class T, class... Args>
        T* AddChild(Args&&... args)
        {
            auto child = std::make_unique<T>(std::forward<Args>(args)...);
            T* raw = child.get();

            AddChildInternal(std::move(child));
            return raw;
        }

        //--------------------------------
        void ChangeParent(Task* newParent);

        //--------------------------------
        void SetSystem(TaskSystem* sys, uint64_t id)
        {
            m_system = sys;
            m_id = id;
        }

        Task* GetParent() const { return m_parent; }

        //--------------------------------
        // 内部用
        //--------------------------------
        void AddChildInternal(Ptr child);

        //--------------------------------
        void UpdateTree(float dt)
        {
            if (m_active)
            {
                if (!Update(dt))
                    m_kill = true;
            }

            for (auto& c : m_children)
                c->UpdateTree(dt);
        }

        // 表示＆生きているタスクのリストを作成する関数（親→子）
        void Collect(std::vector<Task*>& out)
        {
            if (m_visible && !m_kill)
            {
                // リストへ登録
                out.push_back(this);
            }

            for (auto& child : m_children)
            {
                // 子へ
                child->Collect(out);
            }
        }

        void Cleanup()
        {
            for (auto& c : m_children)
                c->Cleanup();

            m_children.erase(
                std::remove_if(m_children.begin(), m_children.end(),
                    [](const Ptr& t) { return t->m_kill; }),
                m_children.end());
        }

        friend class TaskSystem;
    };
}

//#pragma once
//#include <vector>
//#include <memory>
//#include <string>
//#include <algorithm>
//#include <cstdint>
//
//namespace Imase
//{
//    class TaskSystem;
//
//    class Task
//    {
//    public:
//        using Ptr = std::unique_ptr<Task>;
//
//    private:
//
//        // タスクシステムへのポインタ
//        TaskSystem* m_system = nullptr;
//
//        // 親タスクへのポインタ
//        Task* m_parent = nullptr;
//
//        // 子タスクへのポインタの配列
//        std::vector<Ptr> m_children;
//
//        // ID
//        uint64_t m_id = 0;
//
//        // 名前
//        std::wstring m_name;
//
//        // タグ
//        std::wstring m_tag;
//
//        // Updateを実行する場合はtrue
//        bool m_active = true;
//
//        // Renderを実行する場合はtrue
//        bool m_visible = true;
//
//        // 死んでいる場合はtrue
//        bool m_kill = false;
//
//        // 描画順
//        int m_ot = 0;
//
//        Task* AddChildInternal(std::unique_ptr<Task> child);
//
//    public:
//        virtual ~Task() = default;
//
//        //--------------------------------
//        // オーバーライド用
//        //--------------------------------
//        // 更新
//        virtual bool Update(float) { return true; }
//        // 描画
//        virtual void Render() {}
//
//        //--------------------------------
//        // 基本
//        //--------------------------------
//        // IDの取得
//        uint64_t GetID() const { return m_id; }
//
//        // 名前を設定
//        void SetName(const std::wstring& n) { m_name = n; }
//        // 名前を取得
//        const std::wstring& GetName() const { return m_name; }
//
//        // タグを設定
//        void SetTag(const std::wstring& t) { m_tag = t; }
//        // タグを取得
//        const std::wstring& GetTag() const { return m_tag; }
//
//        // 描画順を設定
//        void SetOt(int v) { m_ot = v; }
//        // 描画順を取得
//        int GetOt() const { return m_ot; }
//
//        // タスクを殺す関数
//        void Kill() { m_kill = true; }
//        // タスクが死んでいるか調べる関数
//        bool IsKill() const { return m_kill; }
//
//        //--------------------------------
//        // 子生成
//        //--------------------------------
//        template<class T, class... Args>
//        T* AddChild(Args&&... args)
//        {
//            //if (!m_system) return nullptr;
//
//            //return m_system->AddChild<T>(this, std::forward<Args>(args)...);
//            auto child = std::make_unique<T>(std::forward<Args>(args)...);
//            T* ptr = child.get();
//            AddChildInternal(std::move(child));
//        }
//
//        //--------------------------------
//        // 親変更
//        //--------------------------------
//        void ChangeParent(Task* newParent)
//        {
//            if (!m_system) return;
//
//            m_system->ChangeParent(this, newParent);
//        }
//
//        //--------------------------------
//        // タスクシステムを設定
//        //--------------------------------
//        void SetSystem(TaskSystem* sys, uint64_t id)
//        {
//            m_system = sys;
//            m_id = id;
//        }
//
//        // 親を取得する関数
//        Task* GetParent() const { return m_parent; }
//
//        //--------------------------------
//        // 更新
//        //--------------------------------
//        void UpdateTree(float dt)
//        {
//            // 親が非アクティブでも子は更新される仕様
//            if (m_active)
//            {
//                // 更新
//                if (!Update(dt))
//                {
//                    // タスクを殺す
//                    m_kill = true;
//                }
//            }
//
//            // 子の更新
//            for (auto& child : m_children)
//            {
//                child->UpdateTree(dt);
//            }
//        }
//
//        // 死んでいないタスクだけ抽出する
//        void Collect(std::vector<Task*>& out)
//        {
//            if (m_visible && !m_kill)
//            {
//                // 配列に登録
//                out.push_back(this);
//            }
//
//            // 子へ
//            for (auto& child : m_children)
//            {
//                child->Collect(out);
//            }
//        }
//
//        // クリーンアップ
//        void Cleanup()
//        {
//            // 子のクリーンアップ
//            for (auto& child : m_children)
//            {
//                child->Cleanup();
//            }
//
//            // 子の中で死んでいるタスクを削除
//            m_children.erase(
//                std::remove_if(m_children.begin(), m_children.end(),
//                    [](const Ptr& t) { return t->m_kill; }),
//                m_children.end());
//        }
//
//        friend class TaskSystem;
//    };
//}
