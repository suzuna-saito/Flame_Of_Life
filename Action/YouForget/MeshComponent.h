#pragma once

/*
* メッシュデータの管理と描画を行う
*/
class MeshComponent : public Component
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	/// <param name="_skelton">スケルトンデータを用いるか(デフォはfalse(用いない))</param>
	MeshComponent(class GameObject* _owner, bool _skelton = false);

	// デストラクタ
	~MeshComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shadere">使用するシェーダークラスのポインタ</param>
	virtual void Draw(class Shader* _shader);

protected:
	/// <summary>
	/// テクスチャをステージごとにセット
	/// </summary>
	/// <param name="_shader">使用するシェーダークラスのポインタ</param>
	void SetTextureToShader(class Shader* _shader);

	class Mesh* mMesh;	// メッシュデータクラスへのポインタ

	bool mVisible;		// 描画をするかどうか
	bool mSkeltonFlag;	// スケルトンデータを用いるか

public: //ゲッターセッター
	// 描画をするかどうかを取得 true:描画する
	bool GetVisible() const { return mVisible; }

	// スケルトンデータを用いるか取得 true:用いない
	bool GetIsSkeltal()const { return mSkeltonFlag; }

	/// <summary>
	/// 描画をするかどうかを設定
	/// </summary>
	/// <param name="_visible">描画するかどうか true:描画する</param>
	void SetVisible(bool _visible) { mVisible = _visible; }
	
	/// <summary>
	/// メッシュコンポーネントが使うMeshの設定
	/// </summary>
	/// <param name="_mesh">設定するMeshクラスのポインタ</param>
	void SetMesh(class Mesh* _mesh) { mMesh = _mesh; }
};