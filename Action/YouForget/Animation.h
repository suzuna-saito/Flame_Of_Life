#pragma once

/*
* Skeleton��p�����A�j���[�V�����̃f�[�^�N���X
*/
class Animation
{
public:
	// �R���X�g���N�^
	Animation();
	// �f�X�g���N�^
	~Animation() {};

	/// <summary>
	/// �A�j���[�V�����ǂݍ���
	/// </summary>
	/// <param name="_fileName">�A�j���[�V�����ւ̃p�X</param>
	/// <returns>�A�j���[�V�����̓ǂݍ��݂��ł����true��Ԃ�</returns>
	bool Load(const char* _fileName);

private:
	size_t mNumBones;     //�A�j���[�V�����̂��߂̃{�[����
	size_t mNumFrames;    //�A�j���[�V�����̃t���[����
	float mDuration;      //�A�j���[�V�����̍Đ�����
	float mFrameDuration; //�A�j���[�V�����̃t���[���Ԃ̎���

	/*
	 �g���b�N��̊e�t���[���̕ϊ����
	 �O���̃x�N�g���̊e�C���f�b�N�X�̓{�[��
	 �����̃x�N�g���̓t���[��
	*/
	vector<vector<class BoneTransform>> mTracks;

public: //�Q�b�^�[�Z�b�^�[
	// �Đ����Ԃ�Ԃ�
	float GetDuration() const { return mDuration; }

	/// <summary>
	/// �w�肳�ꂽ�z����A�j���[�V�����̎w�肳�ꂽ���Ԃ�
	/// �e�{�[���̃O���[�o���i���݂́j�|�[�Y�}�g���b�N�X�Ŗ��߂�
	/// ���Ԃ� 0.0f�ȏォ�A���Ԉȉ��ł���Ɨ\�z�����
	/// </summary>
	/// <param name="_outPoses">�|�[�Y�}�g���b�N�X</param>
	/// <param name="_inSkeleton">�{�[��</param>
	/// <param name="_inTime">�w�莞��</param>
	void GetGlobalPoseAtTime(vector<Matrix4>& _outPoses, const class Skeleton* _inSkeleton, float _inTime) const;
};
