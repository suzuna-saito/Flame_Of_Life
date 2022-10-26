#pragma once

/*
* エフェクトを3D空間上に描画するクラス
*/
class ParticleComponent : public Component
{
public:
	// エフェクトが2Ｄか3Ｄか
	enum class EffectType :unsigned char
	{
		e2D,		// 2Dエフェクト
		e3D,		// 3Dエフェクト
	};

	// パーティクルに対するブレンドのタイプ
	enum class ParticleBlendType :unsigned char
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
	/// <param name="_effectType">エフェクトのタイプ</param>
	/// <param name="_updateOrder">コンポーネントの更新順番（数値が小さいほど早く更新される）</param>
	ParticleComponent(GameObject* _owner, bool _billFlag , EffectType _effectType,int _updateOrder = 100);
	// デストラクタ
	~ParticleComponent();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="_shadere">使用するシェーダークラスのポインタ</param>
	void Draw(class Shader* _shadere);

private:
	/// <summary>
	/// ビルボード行列を取得(Matrix4)
	/// </summary>
	/// <returns>ビルボード行列</returns>
	Matrix4 GetBillboardMatrix();

	class Texture* mTexture;		// テクスチャ

	EffectType mEffectType;			// エフェクトが2Ｄか3Ｄか(ベースは3D)
	ParticleBlendType mBlendType;	// ブレンドタイプ

	Matrix4 mStaticBillboardMat;	// ビルボード行列

	Vector3 mAngle;					// エフェクトの角度

	int mDrawOrder;			// 描画順(数字が少ないものから描画される)
	int mTextureWidth;		// テクスチャの横幅
	int mTextureHeight;		// テクスチャの縦幅

	bool mVisible;			// 描画を行うか true:行う
	bool mBillboardFlag;	// カメラの方向を向くかどうか true:向く

public: // ゲッターセッター
	// エフェクトのタイプを取得
	const EffectType GetEffectType() const { return mEffectType; }
	// ブレンドタイプを取得
	const ParticleBlendType GetBlendType() const { return mBlendType; }

	// 描画順を取得
	const int GetDrawOrder() const { return mDrawOrder; }
	// 描画をするかどうかを取得 true:描画する
	const bool GetVisible() const { return mVisible; }

	/// <summary>
	/// ブレンドタイプを設定
	/// </summary>
	/// <param name="_blendType">ブレンド</param>
	void SetBlendMode(ParticleBlendType _blendType) { mBlendType = _blendType; }

	/// <summary>
	/// エフェクトの角度を設定
	/// </summary>
	/// <param name="_angle">エフェクトの角度</param>
	void SetAngle(const Vector3& _angle) { mAngle = _angle; }

	/// <summary>
	/// テクスチャをセットし縦横の長さを計算する
	/// </summary>
	/// <param name="_texture">使用するテクスチャのポインタ</param>
	void SetTexture(class Texture* _texture);

	/// <summary>
	/// 描画をするかどうかを設定
	/// </summary>
	/// <param name="_visible">描画フラグ true: 描画する</param>
	void SetVisible(bool _visible) { mVisible = _visible; }
};