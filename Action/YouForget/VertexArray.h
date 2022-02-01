/*
@brief	プリプロセッサ
*/
#pragma once

class VertexArray
{
public:

	/*
	@enum 頂点レイアウト
	*/
	enum Layout
	{
		//位置&法線&テクスチャUV を持ったフォーマット
		PosNormTex,
		//位置&法線&"スキン用の影響ボーン＆重み情報" & テクスチャUV 
		PosNormSkinTex
	};

	/*
	@fn		コンストラクタ
	@param	_verts 頂点バッファの配列のポインタ
	@param	_numVerts 頂点数
	@param	_indices インデックスバッファの配列のポインタ
	@param	_numIndices インデックスの数
	*/
	VertexArray(const float* _verts, unsigned int _numVerts,
		const unsigned int* _indices, unsigned int _numIndices);

	/*
	@fn		頂点配列コンストラクタ
	@param	_verts 頂点バッファの配列のポインタ
	@param	_numVerts 頂点数
	@param	_layout 頂点レイアウト
	@param	_indices インデックスバッファの配列のポインタ
	@param	_numIndices インデックスの数
	*/
	VertexArray(const void* _verts, unsigned int _numVerts, Layout _layout,
		const unsigned int* _indices, unsigned int _numIndices);

	/*
	@fn	デストラクタ
	*/
	~VertexArray();

	/*
	@fn 頂点配列をアクティブにする（描画に使用できるようにする）
	*/
	void SetActive();

	/*
	@fn		インデックスバッファにあるインデックスの数を取得する
	@return インデックスの数(unsigned int型)
	*/
	unsigned int GetNumIndices() const { return mNumIndices; }

	/*
	@fn		頂点バッファにある頂点の数を取得する
	@return 頂点の数(unsigned int型)
	*/
	unsigned int GetNumVerts() const { return mNumVerts; }

private:

	//頂点バッファにある頂点の数
	unsigned int mNumVerts;
	//インデクスバッファにあるインデックスの数
	unsigned int mNumIndices;
	//頂点バッファのOpenGL ID
	unsigned int mVertexBuffer;
	//インデックスバッファのOpenGL ID
	unsigned int mIndexBuffer;
	//頂点配列オブジェクトのOpenGL ID
	unsigned int mVertexArray;
};

