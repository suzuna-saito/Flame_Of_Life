/*
@fil	Animation.h
@brief	Skeletonを用いたアニメーションのデータクラス
*/

/*
@brief	プリプロセッサ
*/
#pragma once


class Animation
{
public:
	/*
	@fn アニメーション読み込み
	@param _fileName アニメーションへのパス
	*/
	bool Load(const std::string& _fileName);
private:
	//アニメーションのためのボーン数
	size_t mNumBones;
	//アニメーションのフレーム数
	size_t mNumFrames;
	//アニメーションの再生時間
	float mDuration;
	//アニメーションのフレーム間の時刻
	float mFrameDuration;
	/*
	トラック上の各フレームの変換情報。
	外側のベクトルの各インデックスはボーン、
	内側のベクトルはフレーム。　　　　　　　
	mTracks[ボーン][フレーム数]
	*/
	std::vector<std::vector<class BoneTransform>> mTracks;
public: //ゲッターセッター
	/*
	@return ボーン数(unsigned int型)
	*/
	size_t GetNumBones() const { return mNumBones; }
	/*
	@return フレーム数(unsigned int型)
	*/
	size_t GetNumFrames() const { return mNumFrames; }
	/*
	@return 再生時間(float型)
	*/
	float GetDuration() const { return mDuration; }
	/*
	@return	フレーム間の時刻(float型)
	*/
	float GetFrameDuration() const { return mFrameDuration; }

	//指定された配列を、アニメーションの指定された時間に、
	//各ボーンのグローバル（現在の）ポーズマトリックスで埋める。
	//時間は > = 0.0fかつ <= 期間であると予想される
	void GetGlobalPoseAtTime(std::vector<class Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;
};
