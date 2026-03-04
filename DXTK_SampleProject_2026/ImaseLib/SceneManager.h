//--------------------------------------------------------------------------------------
// File: SceneManager.h
//
// シーンを管理するクラス
//
// Date: 2026.3.3
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#pragma once

namespace Imase
{
	template <class T>
	class SceneManager;

	// シーンの基底クラス
	template <class T>
	class Scene
	{
	private:

		// シーンマネージャーへのポインタ
		SceneManager<T>* m_sceneManager;

	public:

		// コンストラクタ
		Scene(SceneManager<T>* sceneManager) : m_sceneManager(sceneManager) {}

		// デストラクタ
		virtual ~Scene() = default;

		// 更新
		virtual void Update(float elapsedTime) = 0;

		// 描画
		virtual void Render() = 0;

		// デバイスに依存するリソースを作成する関数
		virtual void CreateDeviceDependentResources() {}

		// ウインドウサイズに依存するリソースを作成する関数
		virtual void CreateWindowSizeDependentResources() {}

		// デバイスロストした時に呼び出される関数
		virtual void OnDeviceLost() {}

	public:

		// シーンの切り替え関数
		template <class U>
		void ChangeScene();

		// ゲームコンテキスト取得関数
		T* GetGameContexts();

	};

	// シーンマネージャークラス
	template <class T>
	class SceneManager
	{
	private:

		// 共通でアクセスしたいオブジェクトへのポインタ
		T* m_gameContexts;

		// 実行中のシーンへのポインタ
		std::unique_ptr<Scene<T>> m_scene;

		// 次のシーンへのポインタ
		std::unique_ptr<Scene<T>> m_nextScene;

	public:

		// コンストラクタ
		SceneManager(T* gameContexts = nullptr)
			: m_gameContexts(gameContexts)
			, m_scene(nullptr)
			, m_nextScene(nullptr)
		{
		};

		// デストラクタ
		virtual ~SceneManager() = default;

		// 更新
		void Update(float elapsedTime);

		// 描画
		void Render();

		// デバイスに依存するリソースを作成する関数
		void CreateDeviceDependentResources();
		
		// ウインドウサイズに依存するリソースを作成する関数
		void CreateWindowSizeDependentResources();

		// デバイスロストした時に呼び出される関数
		virtual void OnDeviceLost();

		// シーンの設定関数
		template <class U>
		void SetScene();

		// 次のシーンの設定関数
		template <class U>
		void SetNextScene();

		// ゲームコンテキスト設定関数
		void SetGameContexts(T* gameContexts) { m_gameContexts = gameContexts; }

		// ゲームコンテキスト取得関数
		T* GetGameContexts() { return m_gameContexts; }

	};

	// シーンの切り替え関数
	template <class T>
	template <class U>
	void Scene<T>::ChangeScene()
	{
		m_sceneManager->SetNextScene<U>();
	}

	// ユーザーが設定したゲームコンテキスト取得関数
	template <class T>
	T* Scene<T>::GetGameContexts()
	{
		assert(m_sceneManager);

		return m_sceneManager->GetGameContexts();
	}

	// シーンの設定関数
	template <class T>
	template <class U>
	void SceneManager<T>::SetScene()
	{
		// シーンを生成
		m_scene = std::make_unique<U>(this);
	}

	// シーンの設定関数
	template <class T>
	template <class U>
	void SceneManager<T>::SetNextScene()
	{
		if (!m_nextScene)
		{
			// シーンを生成
			m_nextScene = std::make_unique<U>(this);
		}
	}

	// 更新関数
	template <class T>
	void SceneManager<T>::Update(float elapsedTime)
	{
		// シーンの切り替え処理
		if (m_nextScene)
		{
			// シーンを切り替え
			m_scene = std::move(m_nextScene);
		}

		// シーンの更新
		if (m_scene) m_scene->Update(elapsedTime);
	}

	// 描画関数
	template <class T>
	void SceneManager<T>::Render()
	{
		// シーンの描画
		if (m_scene) m_scene->Render();
	}

	// デバイスに依存するリソースを作成する関数
	template <class T>
	void SceneManager<T>::CreateDeviceDependentResources()
	{
		if (m_scene) m_scene->CreateDeviceDependentResources();
	}

	// ウインドウサイズに依存するリソースを作成する関数
	template <class T>
	void SceneManager<T>::CreateWindowSizeDependentResources()
	{
		if (m_scene) m_scene->CreateWindowSizeDependentResources();
	}

	// デバイスロストした時に呼び出される関数
	template <class T>
	void SceneManager<T>::OnDeviceLost()
	{
		if (m_scene) m_scene->OnDeviceLost();
	}

}

