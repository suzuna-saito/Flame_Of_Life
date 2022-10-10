#pragma once

/*
* エフェクトを3D空間上に描画するクラス
*/
class ParticleComponent : public Component
{
public:
	// パーティクルに対するブレンドのタイプ
	typedef enum class ParticleBlendType :unsigned char
	{
		eAlphaBlend,// アルファブレンド
		eAddBlend,	// 加算合成
		eMultBlend	// 乗算合成
	};

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="_owner">アタッチするゲームオブジェクトのポインタ</param>
	/// <param name="_billFlag">カメラの方向を向くかどうか true:向く</param>
	/// <param name="_updateOrder">コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
	ParticleComponent(GameObject* _owner, bool _billFlag ,int _updateOrder = 100);
	// デストラクタ
	~ParticleComponent();

	/*
	@fn		フレーム毎の処理
	@param	_deltaTime 最後のフレームを完了するのに要した時間
	*/
	virtual void Update(float _deltaTime) override {};

	/*
	@fn		描画処理
	@param	_shader 使用するシェーダークラスのポインタ
	*/
	void Draw(class Shader* _shader);

	// カメラ距離でのソート用
	bool operator < (const ParticleComponent& _rhs) const;
	bool operator > (const ParticleComponent& _rhs) const;
private:
	// 角度
	Vector3 mAngle;
	//テクスチャID
	int mTextureID;
	//ブレンドタイプ
	ParticleBlendType mBlendType;
	//描画を行うか
	bool mVisible;
	// ビルボード行列
	Matrix4 mStaticBillboardMat;
	// カメラのワールド座標
	Vector3 mStaticCameraWorldPos;
	//描画順(数字が少ないものから描画される)
	int mDrawOrder;
	//反転を行うか
	bool mReverce;
	// カメラの方向を向くかどうか _true 向く,_false 向かない
	bool mBillboardFlag;
public: //ゲッターセッター
	/*
	@return テクスチャID(int型)
	*/
	int GetTextureID() { return mTextureID; }

	/*
	@return ブレンドタイプ(enum型 PARTICLE_ENUM)
	*/
	ParticleBlendType GetBlendType() { return mBlendType; }

	/*
	@fn		描画をするかどうかを取得する
	@return	true : 描画する , false : 描画しない(bool型)
	*/
	bool GetVisible() const { return mVisible; }

	/*
	@return 描画順(int型)
	*/
	int GetDrawOrder() { return mDrawOrder; }

	/*
	@param _texId テクスチャID
	*/
	void SetTextureID(int _texId) { mTextureID = _texId; }

	/*
	@param mAngle 角度（ｘ軸）
	*/
	void SetAngle(const Vector3& _angle) { mAngle = _angle; }

	/*
	@param _mat ビルボード行列
	*/
	void SetBillboardMat(const Matrix4& _mat) { mStaticBillboardMat = _mat; }

	/*
	@param _brendType カメラのワールド座標
	*/
	void SetBlendMode(ParticleBlendType _blendType) { mBlendType = _blendType; }

	/*
	@fn		描画をするかどうかを設定
	@param	_visible true : 描画する , false : 描画しない
	*/
	void SetVisible(bool _visible) { mVisible = _visible; }

	/*
	@param _drawOrder 描画順
	*/
	void SetDrawOrder(int _drawOrder) { mDrawOrder = _drawOrder; }

	/*
	@param _flag 反転を行うか
	*/
	void SetReverce(bool _flag) { mReverce = _flag; }
};

/*
@return ビルボード行列(Matrix4)
*/
Matrix4 GetBillboardMatrix();