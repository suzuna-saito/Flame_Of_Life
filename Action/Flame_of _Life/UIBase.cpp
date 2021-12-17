/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@param	_pos UI�̐����ꏊ(�X�N���[�����W)
@param	_uiFileName �摜�ւ̃A�h���X
@param	_objectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_sceneTag �V�[���̃^�O
@param	_scale �摜�̊g��T�C�Y
*/
UIBase::UIBase(const Vector2& _pos, const std::string& _uiFileName, SceneBase::Scene _sceneTag, const Tag& _objectTag, const float& _scale)
	: GameObject(_sceneTag, _objectTag)
{

}

/*
@fn �h���N���X�̍X�V�֐����Ăэ��W�Ɉړ��ʂ𑫂�������
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void UIBase::UpdateGameObject(float _deltaTime)
{

}