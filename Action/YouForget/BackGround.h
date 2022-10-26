#pragma once

class BackGround :public GameObject
{
public:
	// 背景にちりばめられている床の種類
	enum class BackGroundType :unsigned char
	{
		eBGtypeOne,	// 1
		eBGtypeTwo,	// 2
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_pos">ポジション</param>
	/// <param name="_type">背景にちりばめられている床の種類</param>
	BackGround(const Vector3 _pos, const BackGroundType _type);
	// デストラクタ
	~BackGround() {};

private:
	//ゲームオブジェクトのメッシュポインタ変数
	class MeshComponent* mMeshComponent;
};