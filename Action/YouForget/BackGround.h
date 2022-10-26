#pragma once

class BackGround :public GameObject
{
public:
	/*
	@fn		コンストラクタ
	@param	_pos ポジション
	@param	_size サイズ
	@param	_objectTag オブジェクトのタグ
	@param	_sceneTag シーンタグ
	*/

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos"></param>
	/// <param name="_size"></param>
	/// <param name="_objectTag"></param>
	/// <param name="_sceneTag"></param>
	/// <param name="_type"></param>
	BackGround(const Vector3& _pos, const Vector3& _size, const CollisionTag& _objectTag, const SceneBase::SceneType _sceneTag, const int _type);

	// デストラクタ
	~BackGround() {};

	/*
	@fn		床のアップデート
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	//void UpdateGameObject(float _deltaTime)override;

private:
	//ゲームオブジェクトのメッシュポインタ変数
	MeshComponent* mMeshComponent;

	const int mType;
};

