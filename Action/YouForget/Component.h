/*
@file	Component.h
@brief	全てのコンポーネントの管理を行う
*/

/*
@brief	プリプロセッサ
*/
#pragma once


class GameObject;

class Component
{
public:
	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_updateOrder コンポーネントの更新順番（数値が小さいほど早く更新される
	*/
	Component(GameObject* _owner, int _updateOrder = 100);

	/*
	@fn	デストラクタ
	*/
	virtual ~Component();

	/*
	@fn		フレーム毎の処理
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float _deltaTime) {};

	/*
	@fn		入力処理
	@param	_state InputState構造体
	*/
	virtual void ProcessInput(const struct InputState& _state) {}

	/*
	@fn	Transformのワールド変換
	*/
	virtual void OnUpdateWorldTransform() {}

	/*
	@fn		ヒットしたオブジェクトが二つ以上あった場合、どのオブジェクトと押し戻しをするか
			タグで調べた後にまたTransformのワールド変換をする
	@detail ヒットしたオブジェクト二つの間にいた場合、引っかかったり、すり抜けするので
			それを防ぐためにもう一度Transformのワールド変換をする
	*/
	virtual void Refresh() {}

protected:
	//アタッチしているゲームオブジェクトのポインタ
	GameObject* mOwner;
	// コンポーネントの更新順番（数値が小さいほど早く更新される）
	int mUpdateOrder;

public: //ゲッターセッター

	/*
	@return 更新順番(int型)
	*/
	int GetUpdateOder() { return mUpdateOrder; }

	/*
	@return アタッチしているゲームオブジェクトへのポインタ(GameObject型)
	*/
	GameObject* GetOwner() { return mOwner; }
};

