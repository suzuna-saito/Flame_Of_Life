/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
Stage01::Stage01(const Scene& _nowScene)
	:SceneBase()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(stage01);
}

/*
@fn	�f�X�g���N�^
*/
Stage01::~Stage01()
{
}


void Stage01::Input(const InputState& _state)
{
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* Stage01::update()
{

	return this;
}
