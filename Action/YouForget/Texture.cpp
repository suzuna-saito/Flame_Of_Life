#include "pch.h"

Texture::Texture()
	: mTextureID(0)
	, mWidth(0)
	, mHeight(0)
{
}

bool Texture::Load(const string& _fileName)
{
	// チャンネル数を格納するローカル変数
	int channels = 0;

	// チャンネル数を格納するローカル変数
	SDL_Surface* surf = IMG_Load(_fileName.c_str());
	if (!surf)
	{
		printf("テクスチャ読み込みに失敗 %s", _fileName.c_str());
		return false;	// falseを返す
	}

	// SDLサーフェスをテクスチャから作成
	SDL_Texture* tex = nullptr;
	// SDL_CreateTextureFromSurface(レンダリングコンテキスト、テクスチャで使うピクセルデータを持つSDL_Surface)
	tex = SDL_CreateTextureFromSurface(RENDERER->GetSDLRenderer(), surf);
	if (!tex)
	{
		printf("サーフェスからテクスチャの作成に失敗 : %s", _fileName.c_str());
		return false;	// falseを返す
	}

	// 画像の幅、高さ、チャンネル数を取得
	mWidth = surf->w;						// 幅
	mHeight = surf->h;						// 高さ
	channels = surf->format->BytesPerPixel;	// チャンネルを取得

	// OpenGLにテクスチャ登録
	int format = GL_RGB;	// アルファなしフルカラー（3）
	int depth, pitch;
	depth = 24;				// 深度　24
	pitch = 3 * mWidth;		// 1ピクセルあたり3byte * 1行のピクセル数
	// チャンネル数が4つだったら
	if (channels == 4)
	{
		format = GL_RGBA;	// アルファ付きフルカラーに設定（4）
		depth = 32;			// 深度　32に設定
		pitch = 4 * mWidth;	// 1ピクセルあたり4byte * 1行のピクセル数 
	}

	// テクスチャ名を1つ生成
	glGenTextures(1, &mTextureID);
	// 指定した名前のテクスチャを有効にする(2次元テクスチャ)
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	// 画像データを関連付ける(ターゲット、レベル（0はベース画像レベル）、色成分の数、画像幅、画像高さ、
	//						0でなければならない、画素データの形式、画素データのデータ型、メモリ上の画像データへのポインタ)
	glTexImage2D(GL_TEXTURE_2D, 0, format, mWidth, mHeight, 0, format, GL_UNSIGNED_BYTE, surf->pixels);
	// RGBサーフェイスを解放する
	SDL_FreeSurface(surf);

	// 指定されたテクスチャオブジェクトのミップマップを生成
	// (テクスチャオブジェクトをバインドする対象を指定)
	glGenerateMipmap(GL_TEXTURE_2D);
	// テクスチャ パラメーターを設定(2次元テクスチャを使用、
	//							縮小時、拡大時のフィルタリング方法をそれぞれ指定、補完するフィルター（双線形補間）を設定)
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

void Texture::Unload()
{
	// 名前付きテクスチャを削除
	glDeleteTextures(1, &mTextureID);
}