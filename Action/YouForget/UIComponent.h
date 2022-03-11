/*
@file  SpriteComponent.h
@brief 画像データクラスを管理し、スクリーン上に描画するクラス
*/

/*
@brief プリプロセッサ
*/
#pragma once

/*
@brief 前方宣言
*/
class GameObject;
class Shader;
class Texture;
class Vector3;

class UIComponent : public Component
{
public:

	/*
	@fn		コンストラクタ
	@param	_owner アタッチするゲームオブジェクトのポインタ
	@param	_drawOrder 描画の順番（数値が小さいほど早く描画される）
	*/
	UIComponent(GameObject* _owner, int _drawOrder = 100);

	/*
	@fn		デストラクタ
	*/
	~UIComponent();

	/*
	@fn		描画処理
	@param _shader 使用するシェーダークラスのポインタ
	*/
	virtual void Draw(Shader* _shader, const Vector3& _Offset);

protected:

	//クラスのポインタ
	Texture* mTexture;
	//描画される順番（数値が少ないほど早く更新される）
	int mDrawOrder;
	//テクスチャの横幅
	int mTextureWidth;
	//テクスチャの縦幅
	int mTextureHeight;
	//描画を行うか
	bool mVisible;
	//UIのID、カウント用
	static int mUIid;
	//このUIのID
	int mMyUIid;

public://ゲッターセッター

	/*
	@return テクスチャの横幅(int型)
	*/
	int GetTexWidth() const { return mTextureWidth; }

	/*
	@return テクスチャの縦幅(int型)
	*/
	int GetTexHeight() const { return mTextureHeight; }

	/*
	@return 描画順(int型)
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@fn		描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない(bool型)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return	UIのid(int型)
	*/
	int GetUIid() { return mMyUIid; }

	/*
	@fn		テクスチャをセットし縦横の長さを計算する
	@param	_texture 使用するテクスチャのポインタ
	*/
	virtual void SetTexture(Texture* _texture);

	/*
	@fn		描画をするかどうかを設定
	@param	_visible true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }
};

