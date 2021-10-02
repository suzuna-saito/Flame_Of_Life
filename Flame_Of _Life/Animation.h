/*
@fil	Animation.h
@brief	Skeleton��p�����A�j���[�V�����̃f�[�^�N���X
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


class Animation
{
public:
	/*
	@fn �A�j���[�V�����ǂݍ���
	@param _fileName �A�j���[�V�����ւ̃p�X
	*/
	bool Load(const std::string& _fileName);
private:
	//�A�j���[�V�����̂��߂̃{�[����
	size_t mNumBones;
	//�A�j���[�V�����̃t���[����
	size_t mNumFrames;
	//�A�j���[�V�����̍Đ�����
	float mDuration;
	//�A�j���[�V�����̃t���[���Ԃ̎���
	float mFrameDuration;
	/*
	�g���b�N��̊e�t���[���̕ϊ����B
	�O���̃x�N�g���̊e�C���f�b�N�X�̓{�[���A
	�����̃x�N�g���̓t���[���B�@�@�@�@�@�@�@
	mTracks[�{�[��][�t���[����]
	*/
	std::vector<std::vector<class BoneTransform>> mTracks;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@return �{�[����(unsigned int�^)
	*/
	size_t GetNumBones() const { return mNumBones; }
	/*
	@return �t���[����(unsigned int�^)
	*/
	size_t GetNumFrames() const { return mNumFrames; }
	/*
	@return �Đ�����(float�^)
	*/
	float GetDuration() const { return mDuration; }
	/*
	@return	�t���[���Ԃ̎���(float�^)
	*/
	float GetFrameDuration() const { return mFrameDuration; }

	//�w�肳�ꂽ�z����A�A�j���[�V�����̎w�肳�ꂽ���ԂɁA
	//�e�{�[���̃O���[�o���i���݂́j�|�[�Y�}�g���b�N�X�Ŗ��߂�B
	//���Ԃ� > = 0.0f���� <= ���Ԃł���Ɨ\�z�����
	void GetGlobalPoseAtTime(std::vector<class Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;
};
