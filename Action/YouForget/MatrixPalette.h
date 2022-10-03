#pragma once

//ボーンの最大数
// スケルトンクラスで使われている
const size_t MAX_SKELETON_BONES = 196;

// @@@
// SkeletalMeshComponentでしかつかわれてない
// てかこれなんだ
struct MatrixPalette
{
	//行列パレット
	Matrix4 mEntry[MAX_SKELETON_BONES];
};
