#pragma once

/*
* ���f���̃{�[���ϊ�
*/
class BoneTransform
{
public:
	Quaternion mRotation;	//��]
	Vector3 mTranslation;	//�ړ�

	/// <summary>
	/// �s����o��
	/// </summary>
	/// <returns>��]�ƕ��s�ړ�����s���Ԃ�</returns>
	Matrix4 ToMatrix() const;

	/// <summary>
	/// �{�[�����
	/// </summary>
	/// <param name="_nowFramePone">���݂̃t���[���̃|�[�Y</param>
	/// <param name="_nextFramePose">���̃t���[���̃|�[�Y</param>
	/// <param name="_interpolation">��Ԓl</param>
	/// <returns>��Ԃ��ꂽ�l</returns>
	static BoneTransform Interpolate(const BoneTransform& _nowFramePone, const BoneTransform& _nextFramePose, float _interpolation);
};
