#include "pch.h"

int main(int argc, char** argv)
{
	// �Q�[���N���X�̒�`
	Game game;
	// �Q�[���N���X�̏�����������������
	if (game.Initialize())
	{
		// �ŏ��̃V�[���𐶐�
		game.SetNewScene(SceneBase::SceneType::eFirst);
		// �Q�[�����[�v�ɓ���
		game.GameLoop();
	}

	//�Q�[���N���X�̏I������
	game.Termination();

	return 0;
}