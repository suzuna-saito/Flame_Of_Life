/*
@brief	インクルード
*/
#include "pch.h"

/*
@fn	コンストラクタ
*/
Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
	, mLuminance(0)
{
}

/*
@fn	デストラクタ
*/
Texture::~Texture()
{
}

/*
@fn		テクスチャのロード
@param	_fileName テクスチャのファイル名
@return	true : 成功 , false : 失敗(bool型)
*/
bool Texture::Load(const std::string& _fileName)
{
	int channels = 0;

	// SDLサーフェスをテクスチャから作成
	SDL_Texture* tex = nullptr;
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("テクスチャ読み込みに失敗 %s", _fileName.c_str());
		return false;
	}

	//サーフェスからテクスチャを作る
	tex = SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), surf);
	if (!tex)
	{
		printf("サーフェスからテクスチャの作成に失敗 : %s", _fileName.c_str());
		return false;
	}

	// 画像の幅、高さを取得
	mWidth = surf->w;
	mHeight = surf->h;
	channels = surf->format->BytesPerPixel;

	// OpenGLにテクスチャ登録
	int format = GL_RGB;
	int depth, pitch;
	depth = 24;
	pitch = 3 * mWidth; // 1ピクセルあたり3byte * 1行のピクセル数
	if (channels == 4)
	{
		format = GL_RGBA;
		depth = 32;
		pitch = 4 * mWidth;
	}

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// @@@
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, surf->pixels);

	SDL_FreeSurface(surf);

	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// 異方性フィルタリングが使えるかどうか
	if (GLEW_EXT_texture_filter_anisotropic)
	{
		// 最大の異方性を示す値を取得する
		GLfloat largest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
		// 異方性フィルタリングを有効にする
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
	}

	return true;
}

/*
@fn	ロードしたテクスチャの解放
*/
void Texture::Unload()
{
	glDeleteTextures(1, &mTextureID);
}

/*
@fn		サーフェイスから作成
@param	_surface コピーで使われるピクセルの集まりの構造体
*/
void Texture::CreateFromSurface(SDL_Surface* _surface)
{
	mWidth = _surface->w;
	mHeight = _surface->h;

	// Generate a GL texture
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_BGRA,
		GL_UNSIGNED_BYTE, _surface->pixels);

	// Use linear filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/*
@fn		レンダリング用のテクスチャを作成
@param	_width テクスチャの横幅
@param	_height テクスチャの縦幅
@param	_format ピクセルデータのフォーマット
*/
void Texture::CreateForRendering(int _width, int _height, unsigned int _format)
{
	mWidth = _width;
	mHeight = _height;
	// テクスチャIDの作成
	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// 画像の幅と高さを設定（初期データは指定しない）
	glTexImage2D(GL_TEXTURE_2D, 0, _format, mWidth, mHeight, 0, GL_RGB,
		GL_FLOAT, nullptr);

	// レンダリング先のテクスチャには最近傍フィルタリングのみを使う
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

/*
@fn	テクスチャをアクティブにする
*/
void Texture::SetActive()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
}