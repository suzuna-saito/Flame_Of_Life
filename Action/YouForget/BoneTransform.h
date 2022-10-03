#pragma once

/*
* モデルのボーン変換
*/
class BoneTransform
{
public:
	Quaternion mRotation;	//回転
	Vector3 mTranslation;	//移動

	/// <summary>
	/// 行列を出力
	/// </summary>
	/// <returns>回転と平行移動から行列を返す</returns>
	Matrix4 ToMatrix() const;

	/// <summary>
	/// ボーン補間
	/// </summary>
	/// <param name="_nowFramePone">現在のフレームのポーズ</param>
	/// <param name="_nextFramePose">次のフレームのポーズ</param>
	/// <param name="_interpolation">補間値</param>
	/// <returns>補間された値</returns>
	static BoneTransform Interpolate(const BoneTransform& _nowFramePone, const BoneTransform& _nextFramePose, float _interpolation);
};
