/*
@brief	�v���v���Z�b�T
*/
#pragma once

#include "Math.h"

//�{�[���̍ő吔
const size_t MAX_SKELETON_BONES = 196;

struct MatrixPalette
{
	//�s��p���b�g
	Matrix4 mEntry[MAX_SKELETON_BONES];
};
