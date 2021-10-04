/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_nowScene ���݂̃V�[��
*/
GameScene::GameScene(const Scene& _nowScene)
{
	// ���C�g��ݒ�(�ݒ肵�Ȃ��Ɖ����f��Ȃ�)
	RENDERER->SetAmbientLight(Vector3(0.8f, 0.8f, 0.8f));
	DirectionalLight& dir = RENDERER->GetDirectionalLight();
	dir.m_direction = Vector3(0.0f, 0.0f, 0.0f);
	//dir.diffuseColor = Vector3(1.0f, 1.0f, 1.0f);
	dir.m_diffuseColor = Vector3(0.5f, 0.5f, 0.8f);
	dir.m_specColor = Vector3(0.8f, 0.8f, 0.8f);

	SetScene(_nowScene);

	mMapCreate = new MapCreate();

	if (!mMapCreate->OpenFile())
	{
		// ���̐���
		mMapCreate->CreateGround();
		// �v���C���[�̐���
		mMapCreate->CreatePlayer();
	}

}

/*
@fn	�f�X�g���N�^
*/
GameScene::~GameScene()
{
	GAME_OBJECT_MANAGER->RemoveGameObjects(tutorial);
}

/*
@fn	���݂̃V�[�����ɖ��t���[���X�V����������
*/
SceneBase* GameScene::update()
{
	return this;
}