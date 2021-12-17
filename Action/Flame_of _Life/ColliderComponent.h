/*
@file	ColliderComponent.h
@brief	�����蔻����s���R���|�[�l���g�̋K��N���X
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


/*
@enum�@GameObject�^�O
�Փˑ���𔻕ʂ��邽�߂Ɏg�p
*/
enum class ColliderTag : unsigned char
{
	start,

	OtherTag = start,
	CameraTag,
	playerTag,
	playerLegsTag,
	groundTag,
	itemTag,

	end,
};

// �O�u�C���N�������g
ColliderTag& operator ++(ColliderTag& rhs);


class ColliderComponent : public Component
{
public:
		/*
		@fn		�R���X�g���N�^
		@param	_owner �A�^�b�`����Q�[���I�u�W�F�N�g�̃|�C���^
		@param	_tag �A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O
		@param	_updateOrder �R���|�[�l���g�̍X�V���ԁi���l���������قǑ����X�V�����j
		@param  _collisionOrder �����蔻�莞�ɁA�߂荞�݂��瓮���������̗D��x�����߂鐔�l
		*/
	ColliderComponent(GameObject* _owner, ColliderTag _tag, int _updateOrder = 200, int _collisionOrder = 100);
protected:

	//�A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O
	ColliderTag mTag;

private:

		//���̂𔺂������蔻������邩�ǂ���
	bool mTriggerFlag;
	//���l���傫������D�悵�Ă߂荞�݂��瓮��������������i0�ȉ��͓������Ȃ��j
	int	 mCollisionOrder;
public: //�Q�b�^�[�Z�b�^�[
	/*
	@fn		�߂荞�ݓ������ۂ̗D��x���������l���擾����
	@return �D��x���������l(int�^)
	*/
	int GetCollisionOrder() const { return mCollisionOrder; }

	/*
	@fn		�A�^�b�`����Q�[���I�u�W�F�N�g�̓����蔻��̃^�O���擾����
	@return	�^�O�̔ԍ�(enum�^ ColliderTag)
	*/
	ColliderTag GetTag() const { return mTag; };
};

