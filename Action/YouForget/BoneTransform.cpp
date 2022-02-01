/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn �s����o��
@return ��]�ƕ��s�ړ�����A�s���Ԃ�
*/
Matrix4 BoneTransform::ToMatrix() const
{
	// ��]�ƕ��s�ړ�����A�s���Ԃ�
	Matrix4 rot = Matrix4::CreateFromQuaternion(mRotation);
	Matrix4 trans = Matrix4::CreateTranslation(mTranslation);

	return rot * trans;
}

/*
@fn		�{�[�����
@param	_nowFrameBone	���݂̃t���[���̃|�[�Y
@param	_nextFrameBone	���̃t���[���̃|�[�Y
@param	_interpolation	��Ԓl
*/
BoneTransform BoneTransform::Interpolate(const BoneTransform& _nowFramePone, const BoneTransform& _nextFramePose, float _interpolation)
{
	BoneTransform retVal;
	retVal.mRotation = Quaternion::Slerp(_nowFramePone.mRotation, _nextFramePose.mRotation, _interpolation);        // a����b �ɐ��lf�ŋ��ʐ��`���(slerp)����
	retVal.mTranslation = Vector3::Lerp(_nowFramePone.mTranslation, _nextFramePose.mTranslation, _interpolation);   // ���s�ړ�������f �Ő��`���(lerp)����
	return retVal;
}
