/*
@brief	�v���v���Z�b�T
*/
#pragma once

class Candle :public GameObject
{
public:
	// �R���X�g���N�^
	Candle(const Vector3& _pos, const Vector3& _size, const Tag& _objectTag, const SceneBase::Scene _sceneTag);

	// �f�X�g���N�^
	~Candle() {};

	/*
	@fn		�낤�����̃A�b�v�f�[�g
	@param	_deltaTime �Ō�̃t���[������������̂ɗv��������
	*/
	void UpdateGameObject(float _deltaTime)override;


private:
	//�Q�[���I�u�W�F�N�g�̃��b�V���|�C���^�ϐ�
	MeshComponent* mMeshComponent;

	// �l�p�̒n�ʂ̓����蔻��𐶐�
	BoxCollider* mSelfBoxCollider;


	/*
	@fn �����蔻�肪�s���Hit�����ۂɌĂ΂��֐�(��������p)
	@param	��������GameObject
	*/
	void OnCollision(const GameObject& _hitObject)override;


	// �낤�����̉΂������ǂ���
	bool mFireFlag;
	// �낤�����̉΂�`�悵�Ă��邩�ǂ���
	bool mDrawFireFlag;

	// �΂������낤�����̖{��
	static int mCandleCount;

public: // �Z�b�^�[�A�Q�b�^�[
	// �΂������낤�����̖{����Ԃ�
	int mGetCandleNum() { return mCandleCount; }


};

