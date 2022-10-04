/*
プリプロセッサ
*/
#pragma once

class MeshComponent;
class SamplePlayer;

class FireObject :public GameObject
{
public:

	// コンストラクタ
	FireObject(Candle* _owner, const Tag& _objectTag, const SceneBase::SceneType _sceneTag);

	/*
	@fn	デストラクタ
	*/
	~FireObject() {};

	// 更新
	void UpdateGameObject(float _deltaTime)override;

private:

	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	Candle* mOwner;

	const float MFireSize;    // 炎のサイズ
	const float MAddPos;
public://ゲッターセッター

};

