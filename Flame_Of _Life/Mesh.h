/*
@file	Mesh.h
@brief	メッシュデータ
*/

/*
@brief	プリプロセッサ
*/
#pragma once

class Renderer;
class VertexArray;
class Texture;

enum class TextureStage;

class Mesh
{
public:

	/*
	@fn	コンストラクタ
	*/
	Mesh();

	/*
	@fn	デストラクタ
	*/
	~Mesh() {};

	/*
	@fn		メッシュデータの読み込み
	@param	_fileName ロードしたいメッシュのファイル名
	@param	_renderer Rendererクラスのポインタ
	@return true : 成功 , false : 失敗(bool型)
	*/
	bool Load(const std::string& _fileName, Renderer* _renderer);

	/*
	@fn	ロードしたメッシュデータの解放
	*/
	void Unload();

private:

	//このメッシュに使うテクスチャのポインタの可変長コンテナ
	std::vector<Texture*> mTextures;
	//このメッシュに使う頂点データ
	std::vector<Vector3> mVerts;
	//クラスのポインタ
	VertexArray* mVertexArray;

	//このメッシュに使うシェーダーの名前
	std::string mShaderName;
	//オブジェクト空間での境界球の半径
	float mRadius;
	//鏡面反射成分の大きさ
	float mSpecPower;
	// 自己発光強度(HDR)
	float mLuminance;
	// 透明度
	float mAlpha;

	//メッシュの矩形当たり判定
	AABB mBox;

	// テクスチャステージに割り当てられたテクスチャ
	std::unordered_map<TextureStage, int> mStageDefTexture;

public://ゲッターセッター

	/*
	@return	VertexArray型のポインタ(class VertexArray)
	*/
	VertexArray* GetVertexArray() { return mVertexArray; }

	/*
	@param	_index テクスチャサイズ
	@return Textureクラスのポインタ(class Texture)
	*/
	Texture* GetTexture(size_t _index);

	/*
	@param	_stage テクスチャステージ
	@return テクスチャのID(int型)
	*/
	int GetTextureID(TextureStage _stage);

	/*
	@return Textureクラスのポインタ(std::string型)
	*/
	const std::string& GetShaderName() const { return mShaderName; }

	/*
	@return 半径(float型)
	*/
	float GetRadius() const { return mRadius; }

	/*
	@return 鏡面反射成分(float型)
	*/
	float GetSpecPower() const { return mSpecPower; }

	/*
	@return 自己発光強度(float型)
	*/
	float GetLuminace() const { return mLuminance; }

	/*
	@return 透明度(float型)
	*/
	float GetAlpha() const { return mAlpha; }

	/*
	@return メッシュの矩形当たり判定(struct AABB)
	*/
	const AABB& GetBox() const { return mBox; }

	/*
	@return 頂点データ(Vector3型)
	*/
	std::vector<Vector3> GetVerts() { return mVerts; }
};