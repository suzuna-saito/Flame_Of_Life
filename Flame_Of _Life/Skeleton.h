/*
@file	Skeleton.h
@brief	骨格
*/

/*
@brief	プリプロセッサ
*/
#pragma once


class Skeleton
{
public:
	/*
	@struct それぞれのボーンの骨格定義
	*/
	struct Bone
	{
		//ローカルバインドポーズ
		BoneTransform mLocalBindPose;
		//ボーン名
		std::string mName;
		//親ID
		int mParent;
	};

	/*
	@fn スケルトンのファイルからのロード
	@param _filename ファイルの名前
	@return 成功、失敗
	*/
	bool Load(const std::string& _filename);
protected:
	/*
	@fn スケルトンがロードされたときに自動的に呼び出され各ボーンのグローバル逆バインドポーズを計算
	*/
	void ComputeGlobalInvBindPose();
private:
	//ボーン配列
	std::vector<Bone> mBones;
	//それぞれのボーンの逆バインドポーズ行列
	std::vector<Matrix4> mGlobalInvBindPoses;
public: //ゲッターセッター
	/*
	@return ボーン数(unsigned int型)
	*/
	size_t GetNumBones() const { return mBones.size(); }
	/*
	@param	_idx ボーンのid
	@return ボーンのid(Bone型)
	*/
	const Bone& GetBone(size_t _idx) const { return mBones[_idx]; }
	/*
	@return ボーン配列(Bone型)
	*/
	const std::vector<Bone>& GetBones() const { return mBones; }
	/*
	@return 逆バインドポーズ行列(Matrix4型)
	*/
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
};
