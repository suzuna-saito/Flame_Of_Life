/*
@brief	プリプロセッサ
*/
#pragma once

/*
@brief	インクルード
*/

class Texture;
class SpriteComponent;

class Sprite : public GameObject
{
public:

	/*
	@fn		コンストラクタ
	@param	_fileName 画像ファイルの名前
	*/
	Sprite(const std::string _fileName);

	/*
	@fn	デストラクタ
	*/
	~Sprite() {};

	/*
	@fn		指定のファイルの描画をけす
	*/
	void NotVisible();
private:

	//テクスチャを生成
	Texture* mSpriteTexture;
	//SpriteComponentを生成
	SpriteComponent* mSpriteComponent;

	

};

