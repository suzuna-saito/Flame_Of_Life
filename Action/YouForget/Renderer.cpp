/*
@file Renderer.h
@brief 描画の進行を行うクラス
*/

/*
@brief	インクルード
*/
#include "pch.h"

//自分のインスタンスの初期化
Renderer* Renderer::mRenderer = nullptr;

/*
@fn	パーティクル用頂点を設定
*/
void Renderer::SetParticleVertex()
{
	m2DParticleVertex->SetActive();
	m3DParticleVertex->SetActive();
}

/*
@fn	コンストラクタ
*/
Renderer::Renderer()
	: mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
	, mMeshShader(nullptr)
	, mBasicShader(nullptr)
	, mParticleShader(nullptr)
	, m2DParticleVertex(nullptr)
	, m3DParticleVertex(nullptr)
	, mSkinnedShader(nullptr)
	, mContext(nullptr)
	, mWindow(nullptr)
	, mSdlRenderer(nullptr)
	, mView(Matrix4::Identity)
	, mProjection(Matrix4::Identity)
	, mAmbientLight(Vector3::Zero)
	, mAddPosition(Vector2::Zero)
	, mScreenWidth(0.0f)
	, mScreenHeight(0.0f)
	, mUndefineTexID(0)
	, MaxTimeFontTextures(999)
	, TimeFontSize(72)
{
}

/*
@fn	デストラクタ
*/
Renderer::~Renderer()
{
}

/*
@fn		インスタンスを作成する
*/
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/*
@fn		インスタンスを削除する
*/
void Renderer::DeleteInstance()
{
	if (mRenderer != nullptr)
	{
		delete mRenderer;
		mRenderer = nullptr;
	}
}

/*
@fn		初期化処理
@return true : 成功 , false : 失敗(bool型)
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight, bool _fullScreen)
{
	mScreenWidth = _screenWidth;
	mScreenHeight = _screenHeight;

	// OpenGLの各属性を設定する
	// コアOpenGLプロファイルを使う
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGLの使用バージョンを3.3に指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA各チャンネル8ビットのカラーバッファを使う
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// ハードウェアアクセラレーションを使う
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウの作成
	mWindow = SDL_CreateWindow("OpenGL Game", 0, 0,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);

	if (_fullScreen)
	{
		SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);
	}

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mSdlRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mSdlRenderer)
	{
		printf("SDLRendererの作成に失敗 : %s", SDL_GetError());
		return false;
	}

	// OpenGLのコンテキストを作成
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEWの初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームで出る無害なエラーコードをクリアする
	glGetError();

	// シェーダーのロード
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}


	////// カリング
	//glFrontFace(GL_CCW);
	//glEnable(GL_FRONT_FACE);

	//スプライト用の頂点配列を作成
	CreateSpriteVerts();

	CreateParticleVerts();

	// SDL_ttfの初期化
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	// UIの初期座標に加算される座標
	mAddPosition = Vector2::Zero;

	return true;
}

/*
@fn	終了処理
*/
void Renderer::Shutdown()
{
	delete mSpriteVerts;
	mSpriteShader->Unload();
	delete mSpriteShader;
	mMeshShader->Unload();
	delete mMeshShader;
	mBasicShader->Unload();
	delete mBasicShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyRenderer(mSdlRenderer);
	SDL_DestroyWindow(mWindow);
}

/*
@fn	ロードしたデータの解放
*/
void Renderer::UnloadData()
{
	// すべてのテクスチャのデータを解放
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// すべてのメッシュのデータを解放
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	// Unload skeletons
	for (auto s : mSkeletons)
	{
		delete s.second;
	}
	// Unload animations
	for (auto a : mAnims)
	{
		delete a.second;
	}

	mMeshes.clear();
}

void Renderer::Draw()
{
	// フレームの最初でカラーバッファとデプスバッファをクリア
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// 深度バッファへの書き込みを無効にする
	glDepthMask(GL_FALSE);
	// RGBAカラー値とカラーバッファー内の値をブレンド
	glEnable(GL_BLEND);

	// デプスバッファ法を無効にする
	glDisable(GL_DEPTH_TEST);
	// スプライトシェーダーをアクティブにする/スプライト頂点配列を有効にする
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	for (auto UI : mUis)
	{
		if (UI->GetVisible())
		{
			UI->Draw(mSpriteShader);
		}
	}

	// 2Dエフェクトがあれば
	if (!mParticles[EffectType::e2D].empty())
	{
		// パーティクルの描画(2D)
		DrawParticle(EffectType::e2D);
	}

	// 深度バッファへの書き込みを有効に戻す
	glDepthMask(GL_TRUE);
	// デプスバッファ法を有効にする
	glEnable(GL_DEPTH_TEST);

	// RGBAカラー値とカラーバッファ内の値をブレンド
	glEnable(GL_BLEND);
	// αを有効にする
	glEnable(GL_ALPHA_TEST);
	// ピクセルの色に新しい色を組み合わせる処理
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// メッシュコンポーネントの描画
	// 基本的なメッシュシェーダーをアクティブにする
	mMeshShader->SetActive();
	// ビュー射影行列を更新する
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// シェーダーに渡すライティング情報を更新する
	SetLightUniforms(mMeshShader, mView);
	// すべてのメッシュの描画
	for (auto mc : mMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

	// 無効にする
	glDisable(GL_BLEND);
	// αを無効にする
	glDisable(GL_ALPHA_TEST);

	// メッシュコンポーネントの描画
	// 基本的なメッシュシェーダーをアクティブにする
	mSkinnedShader->SetActive();
	// ビュー射影行列を更新する
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// シェーダーに渡すライティング情報を更新する
	SetLightUniforms(mSkinnedShader, mView);
	// すべてのメッシュの描画
	for (auto skMc : mSkeletalMeshes)
	{
		if (skMc->GetVisible())
		{
			skMc->Draw(mSkinnedShader);
		}
	}

	// 深度バッファへの書き込みを無効にする
	glDepthMask(GL_FALSE);
	// RGBAカラー値とカラーバッファー内の値をブレンド
	glEnable(GL_BLEND);

	//// 2Dエフェクトがあれば
	//if (!mParticles[EffectType::e2D].empty())
	//{
	//	// パーティクルの描画(2D)
	//	DrawParticle(EffectType::e2D);
	//}
	// 3Dエフェクトがあれば
	if(!mParticles[EffectType::e3D].empty())
	{
		// パーティクルの描画(3D)
		DrawParticle(EffectType::e3D);
	}

	// 深度バッファへの書き込みを有効に戻す
	glDepthMask(GL_TRUE);


	// 当たり判定を描画する
	PHYSICS->DebugShowBox();

	// バッファを交換
	SDL_GL_SwapWindow(mWindow);
}



void Renderer::AddUI(UIComponent* _ui)
{
	// (DrawOrderが小さい順番に描画するため)今あるUIから挿入する場所の検索
	// 自身のDrawOrderを取得
	int myUiDrawOrder = _ui->GetDrawOrder();
	// 今あるUIぶん回す
	auto iterUi = mUis.begin();
	for (;
		iterUi != mUis.end();
		++iterUi)
	{
		// 自身のDrawOrderと、今回しているDrawOrderを比べて自身のほうが小さければ
		if (myUiDrawOrder < (*iterUi)->GetDrawOrder())
		{
			break;
		}
	}

	// 検索した場所のiterの場所に挿入
	mUis.insert(iterUi, _ui);
}

void Renderer::RemoveUI(UIComponent* _ui)
{
	// 削除するクラスのポインタを検索
	auto iterUi = find(mUis.begin(), mUis.end(), _ui);
	// 見つかったUIを削除
	mUis.erase(iterUi);
}

void Renderer::AddParticle(ParticleComponent* _particleComponent)
{
	// 現在のエフェクトのエフェクトタイプを保存
	EffectType type;
	if (_particleComponent->GetEffectType() == EffectType::e2D)
	{
		type = EffectType::e2D;	// 2D
	}
	else
	{
		type = EffectType::e3D;	// 3D
	}

	// (DrawOrderが小さい順番に描画するため)今あるエフェクトから挿入する場所の検索
	// 自身のDrawOrderを取得
	int myDrawOrder = _particleComponent->GetDrawOrder();
	// 今あるエフェクトぶん回す(エフェクトタイプ別)
	auto iter = mParticles[type].begin();
	for (;
		iter != mParticles[type].end();
		++iter)
	{
		// 自身のDrawOrderと、今回しているDrawOrderを比べて自身のほうが小さければ
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// 検索した場所のiterの場所に挿入
	mParticles[type].insert(iter, _particleComponent);
}

void Renderer::RemoveParticle(ParticleComponent* _particleComponent)
{
	// 削除するクラスのポインタを検索
	// エフェクトのタイプによって回すキーを変える
	EffectType nowEffectType = _particleComponent->GetEffectType();

	auto iter = find(mParticles[nowEffectType].begin(), mParticles[nowEffectType].end(), _particleComponent);
	// 見つかったUIを削除
	mParticles[nowEffectType].erase(iter);
}

/*
@fn		メッシュコンポーネントの追加
@param	_meshComponent　追加するMeshComponentクラスのポインタ
*/
void Renderer::AddMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		mMeshComponents.emplace_back(_meshComponent);
	}
}

/*
@fn		メッシュコンポーネントの削除
@param	_meshComponent　削除するMeshComponentクラスのポインタ
*/
void Renderer::RemoveMeshComponent(MeshComponent* _meshComponent)
{
	if (_meshComponent->GetIsSkeltal())
	{
		SkeletalMeshComponent* sk = static_cast<SkeletalMeshComponent*>(_meshComponent);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(mMeshComponents.begin(), mMeshComponents.end(), _meshComponent);
		mMeshComponents.erase(iter);
	}
}


// @@@
Texture* Renderer::GetTimeTexture(int _time)
{
	return timeFontTextures[_time + 1];
}

Texture* Renderer::GetItemCountTexture(int _count)
{
	return timeFontTextures[_count];
}

/*
@param _fileName モデルへのアドレス
@return スケルトンモデルの取得(class Skeleton)
*/
const Skeleton* Renderer::GetSkeleton(const char* _fileName)
{
	std::string file(_fileName);
	auto iter = mSkeletons.find(file);
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(_fileName))
		{
			mSkeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

/*
@param _fileName アニメーションへのアドレス
@return スケルトンアニメーションの取得(class Animation)
*/
const Animation* Renderer::GetAnimation(const char* _fileName)
{
	auto iter = mAnims.find(_fileName);
	if (iter != mAnims.end())
	{
		return iter->second;
	}
	else
	{
		Animation* anim = new Animation();
		if (anim->Load(_fileName))
		{
			mAnims.emplace(_fileName, anim);
		}
		else
		{
			delete anim;
			anim = nullptr;
		}
		return anim;
	}
}

/*
@param	_fileName　取得したいテクスチャのファイル名
@return Textureクラスのポインタ(class Texture)
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//すでに作成されてないか調べる
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//作成済みでない場合、新しくテクスチャを作成
	else
	{
		texture = new Texture();
		if (texture->Load(_fileName))
		{
			mTextures.emplace(_fileName, texture);
		}
		else
		{
			delete texture;
			texture = nullptr;
		}
	}

	return texture;
}

/*
@param	_fileName 取得したいメッシュのファイル名
@return Meshクラスのポインタ(class Mesh)
*/
Mesh* Renderer::GetMesh(const std::string& _fileName)
{
	Mesh* m = nullptr;
	//すでに作成されてないか調べる
	auto iter = mMeshes.find(_fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//作成済みでない場合、新しくメッシュを作成
	else
	{
		m = new Mesh();
		if (m->Load(_fileName, this))
		{
			mMeshes.emplace(_fileName, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

/*
@fn		シェーダーの読み込み
@return true : 成功 , false : 失敗(bool型)
*/
bool Renderer::LoadShaders()
{
	// スプライトシェーダーの作成
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// ビュー行列の設定
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	// ビュー行列の設定
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		mScreenWidth, mScreenHeight, 25.0f, 7000.0f);

	// 標準のメッシュシェーダーの作成
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
	{
		return false;
	}

	// メッシュ
	mMeshShader->SetActive();
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mBasicShader = new Shader();
	if (!mBasicShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag"))
	{
		return false;
	}
	// シンプルなメッシュシェーダー
	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mParticleShader = new Shader();
	if (!mParticleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("シェーダー読み込み失敗\n");
	}

	mSkinnedShader = new Shader();
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/SkinnedPhong.frag"))
	{
		return false;
	}
	mSkinnedShader->SetActive();
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);



	return true;
}

/*
@fn	Sprite用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

/*
@fn	Particle用の頂点バッファとインデックスバッファの作成
*/
void Renderer::CreateParticleVerts()
{
	// 2Dバーテックス
	{
		float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // 左上
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // 右上
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // 右下
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // 左下
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m2DParticleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);

	}

	// 3Dバーテックス
	{
		float vertices[] = {
			-0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
			 0.5f, 0.f, 0.5f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
			 0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
			-0.5f, 0.f,-0.5f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
		};

		unsigned int indices[] = {
			0, 2, 1,
			2, 0, 3
		};

		m3DParticleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
	}
}

void Renderer::DrawParticle(EffectType _effectType)
{
	CreateParticleVerts();

	// ブレンドモード初期状態取得
	//ParticleComponent::ParticleBlendType blendType, prevType;
	//auto itr = mParticles[_effectType].begin();
	//blendType = prevType = (*itr)->GetBlendType();

	// シェーダーON
	mParticleShader->SetActive();
	// ビュープロジェクション行列
	Matrix4 viewProjectionMat;

	if (_effectType == EffectType::e2D)
	{
		viewProjectionMat = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);

		mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);
	}
	else
	{
		viewProjectionMat = mView * mProjection;

		mParticleShader->SetMatrixUniform("uViewProj", viewProjectionMat);
	}

	// すべてのパーティクルを描画
	for (auto particle : mParticles[_effectType])
	{
		// パーティクルの描画フラグがtrueの時
		if (particle->GetVisible())
		{
			////ブレンドモード変更が必要なら変更する
			//blendType = particle->GetBlendType();
			//if (blendType != prevType)
			//{
			//	ChangeBlendMode(blendType);
			//}

			// パーティクル描画
			particle->Draw(mParticleShader);

			// 前回描画状態として保存
			//prevType = blendType;
		}
	}
}

/*
@fn	Particleの描画
@param	_framebuffer フレームバッファ
@param	_view ビュー行列
@param	_proj プロジェクション行列
@param	_viewPortScale 表示領域スケール
@param	_lit 光源情報をシェーダーの変数にセットするかのフラグ
*/
void Renderer::Draw3DScene(unsigned int _framebuffer, const Matrix4& _view, const Matrix4& _proj, float _viewPortScale, bool _lit)
{
	// Set the current frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);

	// Set viewport size based on scale
	glViewport(0, 0,
		static_cast<int>(mScreenWidth * _viewPortScale),
		static_cast<int>(mScreenHeight * _viewPortScale)
	);

	// Clear color buffer/depth buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw mesh components
	// Enable depth buffering/disable alpha blend
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// Set the mesh shader active
	mMeshShader->SetActive();
	// Update view-mProjection matrix
	mMeshShader->SetMatrixUniform("uViewProj", _view * _proj);
	// Update lighting uniforms
	if (_lit)
	{
		SetLightUniforms(mMeshShader, _view);
	}
	for (auto mc : mMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

}

/*
@fn		光源情報をシェーダーの変数にセットする
@param  _shader セットするShaderクラスのポインタ
@param	_view ビュー行列
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// ビュー行列を逆行列にする
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// 環境光の設定
	_shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// 平行光源の設定
	_shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.m_direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.m_diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.m_specColor);
}

/*
@fn		光源情報をシェーダーの変数にセットする
@param  _blendType パーティクルに対するブレンドの種類
*/
void Renderer::ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType)
{
	switch (_blendType)
	{
	case ParticleComponent::ParticleBlendType::eAddBlend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //加算合成
		break;
	case ParticleComponent::ParticleBlendType::eAlphaBlend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // アルファブレンド
		break;
	case ParticleComponent::ParticleBlendType::eMultBlend:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //乗算合成
		break;
	default:
		break;
	}
}

/*
@fn		テクスチャの変更
@param	_changeTextureID 変更するテクスチャのid
*/
void Renderer::ChangeTexture(int _changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, _changeTextureID);
}

/*
@fn	ワールド空間のカメラ座標を計算
*/
Vector3 Renderer::CalcCameraPos()
{
	// ビュー行列よりワールドでのカメラ位置算出
	Matrix4 transMat = mView;

	// ビュー行列の移動成分抜き取る
	Vector3 v;
	v.x = -1.0f * mView.mat[3][0];
	v.y = -1.0f * mView.mat[3][1];
	v.z = -1.0f * mView.mat[3][2];

	//移動成分を取り除いたあと転置して、回転部分の逆変換を作る
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}
