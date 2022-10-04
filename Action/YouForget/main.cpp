//-----------------------------------------------------------------------------
//	@brief	 �C���N���[�h
//-----------------------------------------------------------------------------
#include "pch.h"

int main(int argc, char** argv)
{
	//�Q�[���N���X�̒�`
	Game game;
	//�Q�[���N���X�̏�����������������
	bool success = game.Initialize();
	game.SetFirstScene(new Title(SceneBase::SceneType::eTitle));

	if (success)
	{
		game.GameLoop();
	}

	//�Q�[���N���X�̏I������
	game.Termination();

	return 0;
}