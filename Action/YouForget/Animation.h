#pragma once

/*
* Skeletonを用いたアニメーションのデータクラス
*/
class Animation
{
public:
	// コンストラクタ
	Animation();
	// デストラクタ
	~Animation() {};

	/// <summary>
	/// アニメーション読み込み
	/// </summary>
	/// <param name="_fileName">アニメーションへのパス</param>
	/// <returns>アニメーションの読み込みができればtrueを返す</returns>
	bool Load(const char* _fileName);

private:
	size_t mNumBones;     //アニメーションのためのボーン数
	size_t mNumFrames;    //アニメーションのフレーム数
	float mDuration;      //アニメーションの再生時間
	float mFrameDuration; //アニメーションのフレーム間の時刻

	/*
	 トラック上の各フレームの変換情報
	 外側のベクトルの各インデックスはボーン
	 内側のベクトルはフレーム
	*/
	vector<vector<class BoneTransform>> mTracks;

public: //ゲッターセッター
	// 再生時間を返す
	float GetDuration() const { return mDuration; }

	/// <summary>
	/// 指定された配列をアニメーションの指定された時間に
	/// 各ボーンのグローバル（現在の）ポーズマトリックスで埋める
	/// 時間は 0.0f以上かつ、期間以下であると予想される
	/// </summary>
	/// <param name="_outPoses">ポーズマトリックス</param>
	/// <param name="_inSkeleton">ボーン</param>
	/// <param name="_inTime">指定時間</param>
	void GetGlobalPoseAtTime(vector<Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;
};
