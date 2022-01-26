/*
@file	GameObjectManager.h
@brief	ゲームオブジェクトの更新を行う
*/

/*
@brief	プリプロセッサ
*/
#pragma once

#define GAME_OBJECT_MANAGER GameObjectManager::GetInstance()


class GameObjectManager
{
public:

	/*
	@return 自身のインスタンスを返す
	*/
	static GameObjectManager* GetInstance() { return mManager; }

	/*
	@fn インスタンスを生成
	*/
	static void CreateInstance();

	/*
	@fn インスタンスを削除
	*/
	static void DeleteInstance();

	/*
	@fn		ゲームオブジェクトのアップデート処理
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime);

	/*
	@fn		ゲームオブジェクトの入力処理
	@param	_state 各入力機器の入力状態
	@brief	キーボード、マウス、コントローラー
	*/
	void ProcessInput(const InputState& _state);

	/*
	@fn		ゲームオブジェクトの追加
	@param	_object 追加するGameObjectクラスのポインタ
	*/
	void AddGameObject(GameObject* _object);

	/*
	@fn		ゲームオブジェクトの削除
	@param	_object 削除するGameObjectクラスのポインタ
	*/
	void RemoveGameObject(GameObject* _object);

	/*
	@fn		シーンごとの全てのゲームオブジェクトの削除
	@param	_scene 削除するシーンのタグ
	*/
	void RemoveGameObjects(SceneBase::Scene _scene);

	/*
	@fn		使用したすべてのゲームオブジェクトを解放する
	@detail シーン遷移の際に使用される。GameObject内の再利用フラグが建っているオブジェクトは解放しない
	*/
	void RemoveAllUsedGameObject();

	/*
	@fn		特定のゲームオブジェクトを探す
	@param	_tag ゲームオブジェクトのタグ
	*/
	GameObject* FindGameObject(Tag _tag);

	/*
	@fn		特定のゲームオブジェクトを探す
	@param	_tag ゲームオブジェクトのタグ
	*/
	std::vector<GameObject*> FindGameObjects(Tag _tag);

private:

	/*
	@fn	コンストラクタ
	*/
	GameObjectManager();

	/*
	@fn	デストラクタ
	*/
	~GameObjectManager();

	//自身のインスタンス
	static GameObjectManager* mManager;

	//ゲームオブジェクトのポインタの可変長コンテナ
	//カメラを格納するための可変長コンテナ
	std::vector<GameObject*> mCameraObjects;
	//タイトル時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mTitleObjects;
	//チュートリアル時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mTutorialObjects;
	//Easyステージの時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mEasyStageObjects;
	//Normalステージの時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mNormalStageObjects;
	//Hardステージの時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mHardStageObjects;
	//リザルト時の全てのゲームオブジェクトを格納するための可変長コンテナ
	std::vector<GameObject*> mResultObjects;
	//Update中に追加されたゲームオブジェクトのポインタを一時的に保存する可変長コンテナ
	std::vector<GameObject*> mPendingGameObjects;

	//Update中かどうか
	bool mUpdatingGameObject;

};
