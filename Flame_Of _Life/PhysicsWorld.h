/*
@file	PhysicsWorld.h
@brief	�����蔻����s��
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


#define PHYSICS PhysicsWorld::GetInstance()

class GameObject;
class BoxCollider;
class SphereCollider;
class ColliderComponent;


typedef std::function<void(GameObject&)> OnCollisionFunc;
typedef std::map<ColliderComponent*, std::function<void(GameObject&)>> OnCollisionMap;

class PhysicsWorld
{
public:

	/*
	@fn	�C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/*
	@fn	�C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/*
	@fn	�����蔻��
	*/
	void HitCheck();

	/*
	@fn		��`�̓����蔻��
	@brief	��`�̓����蔻�肪�ǂ̃I�u�W�F�N�g�Ɠ����������^�O�Œ��ׂ�
	@param _box BoxCollider�N���X�̃|�C���^
	*/
	void HitCheck(BoxCollider* _box);

	/*
	@fn		���̓����蔻��
	@brief	���̓����蔻�肪�ǂ̃I�u�W�F�N�g�Ɠ����������^�O�Œ��ׂ�
	@param _sphere SphereCollider�N���X�̃|�C���^
	*/
	void HitCheck(SphereCollider* _sphere);

	/*
	@fn		��`�̓����蔻���ǉ�
	@param	_box�@�ǉ�����BoxCollider�N���X�̃|�C���^
	*/
	void AddBox(BoxCollider* _box, OnCollisionFunc _func);

	/*
	@fn		��`�̓����蔻����폜
	@param	_box�@�폜����BoxCollider�N���X�̃|�C���^
	*/
	void RemoveBox(BoxCollider* _box);

	/*
	@fn		���̓����蔻���ǉ�
	@param	_sphere�@�ǉ�����SphereCollider�N���X�̃|�C���^
	*/
	void AddSphere(SphereCollider* _sphere, OnCollisionFunc _func);

	/*
	@fn		���̓����蔻����폜
	@param	_sphere�@�폜����SphereCollider�N���X�̃|�C���^
	*/
	void RemoveSphere(SphereCollider* _sphere);

	void DebugShowBox();                                               // �f�o�b�O�p�{�b�N�X�\��
	void ToggleDebugMode() { mBoolDebugMode = !mBoolDebugMode; }       // �f�o�b�O���[�h

private:

	/*
	@fn	�R���X�g���N�^�̉B��
	*/
	PhysicsWorld();

	//�����̃C���X�^���X
	static PhysicsWorld* mPhysics;

	/*
	@fn	��`�Ƌ�`�̓����蔻��
	*/
	void BoxAndBox();

	/*
	@fn	���Ƌ��̓����蔻��
	*/
	void SphereAndSphere();

	/*
	@fn	���Ƌ�`�̓����蔻��
	*/
	void SphereAndBox();

	void InitBoxVertices();
	void InitSquareVertices();
	void InitLineVertices();
	void DrawCollisions(std::vector<class BoxCollider*>& boxes, const Vector3& color);

	//��`�̓����蔻���S�Ċi�[���邽�߂̉ϒ��R���e�i
	std::vector<BoxCollider*> mBoxes;

	//���̋�`�����蔻���S�Ċi�[���邽�߂̉ϒ��R���e�i
	std::vector<BoxCollider*> mGroundBoxes;

	//���̓����蔻���S�Ċi�[���邽�߂̉ϒ��R���e�i
	std::vector<SphereCollider*> mSpheres;

	OnCollisionMap mCollisionFunction;

	std::vector<Vector3>      mLineColors;                             // �����蔻��{�b�N�X�̃J���[

	bool                      mBoolDebugMode;                          // �f�o�b�O���[�h

	unsigned int mBoxVAO;      // �{�b�N�X�`��p��VAO 
	unsigned int mSquareVAO;   // ���ʕ`��p��VAO
	unsigned int mLineVAO;     // ���C���pVAO
	class Shader* mLineShader; // ���C���`��p�V�F�[�_�[

public://�Q�b�^�[�Z�b�^�[

	/*
	@return PhysicsWorld�N���X�̃C���X�^���X(PhysicsWorld�^)
	*/
	static PhysicsWorld* GetInstance() { return mPhysics; }
};

/*
@fn �Փ˂������Ƃ��m�肵���Ƃ��A�߂荞�݂�߂��֐�
@param _movableBox �ړ�����
@param _fixedBox �ړ����Ȃ�����
@param _calcFixVec �ړ����̂̕␳�����x�N�g��
*/
void CalcCollisionFixVec(const AABB& _movableBox, const AABB& _fixedBox, Vector3& _calcFixVec);