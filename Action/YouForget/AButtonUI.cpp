#include "pch.h"

AButtonUI::AButtonUI()
	: UIBase()
	, mMaxScale(1.5f)
	, mMinScale(1.2f)
	, mAddScale(0.005f)
{
	// GameObject�N���X�̕ϐ�������
	mPosition = Vector3(820.0f,-420.0f,0.0f);		// �|�W�V����
	mScale = Vector3(mMaxScale, mMaxScale, 0.0f);	// �X�P�[��

	// UIComponent�𐶐����邱�ƂŎ����ŕ`�悳���悤�ɂȂ�
	mUIComponent = new UIComponent(this, mPosition, mScale);
	// �e�N�X�`���𐶐�
	mUIComponent->SetTexture(RENDERER->GetTexture("Assets/UI/ResultBase/Button2.png"));
}

void AButtonUI::UpdateGameObject(float _deltaTime)
{
	// mScale���ŏ��l��菬�����A�܂��́A�ő�l���傫��������
	if (mScale.x <= mMinScale || mScale.x >= mMaxScale)
	{
		mAddScale *= -1;	// ������ς���
	}
	// �X�P�[���l��mAddScale�𑫂�
	mScale += Vector3(mAddScale, mAddScale, 0.0f);
	// �X�P�[���l���Z�b�g
	mUIComponent->SetScale(mScale);

}
