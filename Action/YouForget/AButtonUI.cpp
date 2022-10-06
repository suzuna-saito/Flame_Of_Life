#include "pch.h"

AButtonUI::AButtonUI()
	: UIBase()
	, mAddScale(-0.01f)
{
	// GameObject�N���X�̕ϐ�������
	mPosition = Vector3(800.0f,0.0f,-400.0f);	// �|�W�V����
	mScale = Vector3(2.0f, 2.0f, 0.0f);			// �X�P�[��

	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUiComponent = new UIComponent(this, mPosition, mScale);
	// �e�N�X�`���𐶐�
	mUiComponent->SetTexture(RENDERER->GetTexture("Assets/UI/ResultBase/Button2.png"));
}

void AButtonUI::UpdateGameObject(float _deltaTime)
{
	// mScale��2.0f��菬�����A�܂��́A2.5f���傫��������
	if (mScale.x <= 2.0f || mScale.x >= 2.5f)
	{
		mAddScale *= -1;	// ������ς���
	}
	// �X�P�[���l��mAddScale�𑫂�
	mScale += Vector3(mAddScale, mAddScale, 0.0f);
	// �X�P�[���l���Z�b�g
	mUiComponent->SetScale(mScale);

}
