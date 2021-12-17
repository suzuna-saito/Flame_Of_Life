//-----------------------------------------------------------------------------
//	@brief	�C���N���[�h
//-----------------------------------------------------------------------------
#include "pch.h"

// �ÓI�����o�[�̏�����
bool CountUp::countStartFlag = false;

/*
@brief	�R���X�g���N�^
@param	�J�E���g���鎞��
@param	���݂̃V�[��
*/
CountUp::CountUp(SceneBase::Scene _sceneTag)
	: GameObject(_sceneTag, Tag::UI, false)
	, AddTimeCount(60)
	, time(0)
	, MMaxTime(999)
	, MPosition(Vector3(-700.0f, 450.0f, 0.0f))
{
	// �|�W�V�������Z�b�g
	SetPosition(MPosition);

	// SpriteComponent�̏�����
	sprite = new SpriteComponent(this);
}

/*
@fn �f�X�g���N�^
@brief  object�̍폜���s��
*/
CountUp::~CountUp()
{
}

/*
@fn �A�b�v�f�[�g�֐�
@brief	�X�V�������s��
@param	_deltaTime �O�̃t���[���ł�����������
*/
void CountUp::UpdateGameObject(float _deltaTime)
{
	// �Q�[���X�^�[�g������J�E���g�J�n
	if (countStartFlag == true && frameCount != MMaxTime)
	{
		// �t���[���J�E���g�𐔂���
		frameCount++;
		// �J�E���g��60�ɂȂ�����
		if (frameCount >= AddTimeCount)
		{
			// time�𑝂₷
			time += 1;
			frameCount = 0;
		}
	}

	//@@@
	// texture���ɍ����vector�z��Ɋi�[���Ă���s����0��`�悷��Ƃ�null�ɃA�N�Z�X���Ă��܂��̂����
	if (time == 0)
	{
		sprite->SetTexture(RENDERER->GetTimeTexture(-1));
	}
	else
	{
		// ���F�ŕ`��
		sprite->SetTexture(RENDERER->GetTimeTexture(time - 1));
	}
}