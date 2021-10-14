#pragma once

class Physics
{
public:
	struct collidePairs
	{
		Tag pair1;
		Tag pair2;
	};

	Physics();
	~Physics();

	void AddCollider(class ColliderComponent* collider);               // Collider�ǉ�
	void RemoveCollider(class ColliderComponent* collider);            // Collider�폜
	void Collision();                                                  // �R���W����
	void DebugShowBox();                                               // �f�o�b�O�p�{�b�N�X�\��
	void ToggleDebugMode() { mBoolDebugMode = !mBoolDebugMode; }       // �f�o�b�O���[�h

	void SetOneSideReactionCollisionPair(Tag noReactionType, Tag reactionType); // �����蔻��y�A�̃Z�b�g�i�Е��������A�N�V�����Ԃ��^�C�v�j

	void ClearOneSidePair();                                           // �����蔻��y�A�̃N���A
	void ClearDualPair();
	void ClearSelfPair();

private:

	void InitBoxVertices();
	void InitSquareVertices();
	void InitLineVertices();
	void DrawCollisions(std::vector<class ColliderComponent*>& boxs, const Vector3& color);

	bool                      mBoolDebugMode;                          // �f�o�b�O���[�h
	std::vector<collidePairs> mOneSideReactions;                       // �Е��������A�N�V�������s�������蔻��y�A���X�g
	std::vector<collidePairs> mDualReactions;                          // �����Ƃ����A�N�V�������s�������蔻��y�A���X�g
	std::vector<Tag>          mSelfReactions;                          // �����O���[�v���ł̓����蔻����s�����X�g
	std::vector<Vector3>      mLineColors;                             // �����蔻��{�b�N�X�̃J���[
	std::unordered_map<ColliderTag, std::vector<class ColliderComponent*>> mColliders;    // �����蔻��{�b�N�X���X�g

	unsigned int mBoxVAO;      // �{�b�N�X�`��p��VAO 
	unsigned int mSquareVAO;   // ���ʕ`��p��VAO
	unsigned int mLineVAO;     // ���C���pVAO
	class Shader* mLineShader; // ���C���`��p�V�F�[�_�[


};