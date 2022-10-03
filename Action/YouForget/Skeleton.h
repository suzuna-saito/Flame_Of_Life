#pragma once

/*
* 骨格
*/
class Skeleton
{
public:
	// それぞれのボーンの骨格定義(構造体)
	struct Bone
	{
		BoneTransform mLocalBindPose;	// ローカルバインドポーズ
		string mName;					// ボーン名
		int mParent;					// 親ID
	};

	/// <summary>
	/// スケルトンのファイルからのロード
	/// </summary>
	/// <param name="_filename">ファイルの名前</param>
	/// <returns>true:成功、false:失敗</returns>
	bool Load(const char* _filename);

private:
	/// <summary>
	/// スケルトンがロードされたときに自動的に呼び出され各ボーンのグローバル逆バインドポーズを計算
	/// </summary>
	void ComputeGlobalInvBindPose();

	vector<Bone> mBones;					// ボーン配列
	vector<Matrix4> mGlobalInvBindPoses;	// それぞれのボーンの逆バインドポーズ行列

public: //ゲッターセッター
	// ボーン数を返す
	size_t GetNumBones() const { return mBones.size(); }
	// ボーン配列(Bone型)を返す
	const vector<Bone>& GetBones() const { return mBones; }
	// 逆バインドポーズ行列(Matrix4型)
	const vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
};
