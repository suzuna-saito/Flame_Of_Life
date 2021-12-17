/*
@brief	プリプロセッサ
*/
#pragma once


class Texture
{
public:

	/*
	@fn	コンストラクタ
	*/
	Texture();

	/*
	@fn	デストラクタ
	*/
	~Texture();

	/*
	@fn		テクスチャのロード
	@param	_fileName テクスチャのファイル名
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool Load(const std::string& _fileName);

	/*
	@fn	ロードしたテクスチャの解放
	*/
	void Unload();

	/*
	@fn		サーフェイスから作成
	@param	_surface コピーで使われるピクセルの集まりの構造体
	*/
	void CreateFromSurface(struct SDL_Surface* _surface);

	/*
	@fn		レンダリング用のテクスチャを作成
	@param	_width テクスチャの横幅
	@param	_height テクスチャの縦幅
	@param	_format ピクセルデータのフォーマット
	*/
	void CreateForRendering(int _width, int _height, unsigned int _format);

private:

	//テクスチャid
	unsigned int mTextureID;
	//輝度
	float mLuminance;
	//テクスチャの横幅
	int mWidth;
	//テクスチャの縦幅
	int mHeight;

public://ゲッターセッター

	/*
	@return テクスチャの横幅(int型)
	*/
	int GetWidth() const { return mWidth; }

	/*
	@return テクスチャの縦幅(int型)
	*/
	int GetHeight() const { return mHeight; }

	/*
	@return テクスチャid(int型)
	*/
	int GetTextureID() const { return mTextureID; }

	/*
	@fn	テクスチャをアクティブにする
	*/
	void SetActive();

	/*
	@param _luminance 輝度
	*/
	void SetLuminace(float _luminance) { mLuminance = _luminance; }

};