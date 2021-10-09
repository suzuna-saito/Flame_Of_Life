/*
@brief	プリプロセッサ
*/
#pragma once

class Candle :public GameObject
{
public:
	// コンストラクタ
	Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	// デストラクタ
	~Candle() {};


private:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	// 四角の地面の当たり判定を生成
	BoxCollider* mSelfBoxCollider;

	// ろうそくの火がつくかどうか
	bool mFireFlag;
	// ろうそくの火を描画しているかどうか
	bool mDrawFireFlag;

public: // セッター、ゲッター
	bool SetFireFlag(bool _flag) { mFireFlag = _flag; }
};

