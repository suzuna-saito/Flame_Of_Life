/*
@file	MeshComponent.h
@brief	メッシュデータの管理と描画を行う
*/

/*
@brief	プリプロセッサ
*/
#pragma once


class Shader;
class Mesh;

class MeshComponent : public Component
{
public:
	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_skelton スケルトンデータを用いるか。(デフォはfalse)
	@sa		SkeletalMeshComponent.h
	*/
	MeshComponent(GameObject* _owner, bool _skelton = false);

	/*
	@fn		デストラクタ
	*/
	~MeshComponent();

	/*
	@fn		描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	virtual void Draw(Shader* _shader);
protected:
	/*
	@fn		テクスチャをステージごとにセット
	@brief	ディフューズマップ	stage00
			法線マップ			stage01
			スペキュラーマップ	stage02
			自己放射マップ		stage03
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	virtual void SetTextureToShader(class Shader* _shader);
	//メッシュデータクラスへのポインタ
	Mesh* mMesh;
	//テクスチャサイズ
	size_t mTextureIndex;
	//描画をするかどうか
	bool mVisible;
	//スケルトンデータを用いるか
	bool mSkeltonFlag;

public: //ゲッターセッター
	/*
	@fn		描画をするかどうかを設定
	@param	_visible true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@fn		描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない(bool型)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return スケルトンデータを用いるか(bool型)
	*/
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	/*
	@return 設定されたMeshクラスのポインタ(bool型)
	*/
	virtual Mesh* GetMesh() { return mMesh; }

	/*
	@fn		メッシュコンポーネントが使うMeshの設定
	@param	_mesh 設定するMeshクラスのポインタ
	*/
	virtual void SetMesh(Mesh* _mesh) { mMesh = _mesh; }

	/*
	@fn		メッシュコンポーネントが使うTextureインデックスの設定
	@param _index テクスチャサイズ
	*/
	void SetTextureIndex(size_t _index) { mTextureIndex = _index; }
};