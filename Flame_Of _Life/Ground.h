/*
@brief	プリプロセッサ
*/
#pragma once

class Ground :public GameObject
{
public:
	// コンストラクタ
	Ground(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	// デストラクタ
	~Ground() {};

	/*
	@fn		床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	void UpdateGameObject(float _deltaTime)override;

private:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	int mAlphaCount;

	float mAlphaAdd;
	float mAlphaSub;

	bool mAlphaChange;
};

