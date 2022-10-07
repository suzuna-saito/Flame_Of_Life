#include "pch.h"

Matrix4 BoneTransform::ToMatrix() const
{
	// ��]�ƕ��s�ړ�����s���Ԃ�
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

BoneTransform BoneTransform::Interpolate(const BoneTransform& _nowFramePone, const BoneTransform& _nextFramePose, const float _interpolation)
{
	BoneTransform retVal;
	// a����b �ɐ��lf�ŋ��ʐ��`���(slerp)����
	retVal.mRotation = Quaternion::Slerp(_nowFramePone.mRotation, _nextFramePose.mRotation, _interpolation);
	// ���s�ړ�������f �Ő��`���(lerp)����
	retVal.mTranslation = Vector3::Lerp(_nowFramePone.mTranslation, _nextFramePose.mTranslation, _interpolation);

	return retVal;
}