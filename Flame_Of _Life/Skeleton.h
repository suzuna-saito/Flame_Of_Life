/*
@file	Skeleton.h
@brief	���i
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class Skeleton
{
public:
	/*
	@struct ���ꂼ��̃{�[���̍��i��`
	*/
	struct Bone
	{
		//���[�J���o�C���h�|�[�Y
		BoneTransform mLocalBindPose;
		//�{�[����
		std::string mName;
		//�eID
		int mParent;
	};

	/*
	@fn �X�P���g���̃t�@�C������̃��[�h
	@param _filename �t�@�C���̖��O
	@return �����A���s
	*/
	bool Load(const std::string& _filename);
protected:
	/*
	@fn �X�P���g�������[�h���ꂽ�Ƃ��Ɏ����I�ɌĂяo����e�{�[���̃O���[�o���t�o�C���h�|�[�Y���v�Z
	*/
	void ComputeGlobalInvBindPose();
private:
	//�{�[���z��
	std::vector<Bone> mBones;
	//���ꂼ��̃{�[���̋t�o�C���h�|�[�Y�s��
	std::vector<Matrix4> mGlobalInvBindPoses;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@return �{�[����(unsigned int�^)
	*/
	size_t GetNumBones() const { return mBones.size(); }
	/*
	@param	_idx �{�[����id
	@return �{�[����id(Bone�^)
	*/
	const Bone& GetBone(size_t _idx) const { return mBones[_idx]; }
	/*
	@return �{�[���z��(Bone�^)
	*/
	const std::vector<Bone>& GetBones() const { return mBones; }
	/*
	@return �t�o�C���h�|�[�Y�s��(Matrix4�^)
	*/
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
};
