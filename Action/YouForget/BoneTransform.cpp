#include "pch.h"

Matrix4 BoneTransform::ToMatrix() const
{
	// 回転と平行移動から行列を返す
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

BoneTransform BoneTransform::Interpolate(const BoneTransform& _nowFramePone, const BoneTransform& _nextFramePose, const float _interpolation)
{
	BoneTransform retVal;
	// aからb に数値fで球面線形補間(slerp)する
	retVal.mRotation = Quaternion::Slerp(_nowFramePone.mRotation, _nextFramePose.mRotation, _interpolation);
	// 平行移動成分はf で線形補間(lerp)する
	retVal.mTranslation = Vector3::Lerp(_nowFramePone.mTranslation, _nextFramePose.mTranslation, _interpolation);

	return retVal;
}