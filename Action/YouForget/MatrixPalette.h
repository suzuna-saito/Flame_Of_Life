#pragma once

//�{�[���̍ő吔
// �X�P���g���N���X�Ŏg���Ă���
const size_t MAX_SKELETON_BONES = 196;

// @@@
// SkeletalMeshComponent�ł��������ĂȂ�
// �Ă�����Ȃ�
struct MatrixPalette
{
	//�s��p���b�g
	Matrix4 mEntry[MAX_SKELETON_BONES];
};
