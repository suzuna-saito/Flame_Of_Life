/*
@brief �C���N���[�h
*/
#include "pch.h"

/*
@fn		�R���X�g���N�^
@param	_Pos �{�^���摜�̐����ꏊ(�X�N���[�����W)
@param	_ObjectTag �A�^�b�`�����Q�[���I�u�W�F�N�g�̃^�O
@param	_SceneTag �V�[���̃^�O
*/
ButtonUI::ButtonUI(const Vector2& _Pos, const Tag& _ObjectTag, const SceneBase::Scene _SceneTag)
	:UIBase(_Pos, "Assets/UI/Button.png", _SceneTag, _ObjectTag)
{
	mUI = new UIComponent(this,0);
	mUI->SetTexture(RENDERER->GetTexture("Assets/UI/Button.png"));

	mPosition = Vector3(_Pos.x, _Pos.y, 0.0f);
}

/*
@fn		�{�^���摜�̃A�b�v�f�[�g
@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
*/
void ButtonUI::UpdateGameObject(float _deltaTime)
{
}
