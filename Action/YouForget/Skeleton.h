#pragma once

/*
* ���i
*/
class Skeleton
{
public:
	// ���ꂼ��̃{�[���̍��i��`(�\����)
	struct Bone
	{
		BoneTransform mLocalBindPose;	// ���[�J���o�C���h�|�[�Y
		string mName;					// �{�[����
		int mParent;					// �eID
	};

	/// <summary>
	/// �X�P���g���̃t�@�C������̃��[�h
	/// </summary>
	/// <param name="_filename">�t�@�C���̖��O</param>
	/// <returns>true:�����Afalse:���s</returns>
	bool Load(const char* _filename);

private:
	/// <summary>
	/// �X�P���g�������[�h���ꂽ�Ƃ��Ɏ����I�ɌĂяo����e�{�[���̃O���[�o���t�o�C���h�|�[�Y���v�Z
	/// </summary>
	void ComputeGlobalInvBindPose();

	vector<Bone> mBones;					// �{�[���z��
	vector<Matrix4> mGlobalInvBindPoses;	// ���ꂼ��̃{�[���̋t�o�C���h�|�[�Y�s��

public: //�Q�b�^�[�Z�b�^�[
	// �{�[������Ԃ�
	size_t GetNumBones() const { return mBones.size(); }
	// �{�[���z��(Bone�^)��Ԃ�
	const vector<Bone>& GetBones() const { return mBones; }
	// �t�o�C���h�|�[�Y�s��(Matrix4�^)
	const vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
};
