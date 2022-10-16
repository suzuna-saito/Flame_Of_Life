/*
@file Renderer.h
@brief �`��̐i�s���s���N���X
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

//�����̃C���X�^���X�̏�����
Renderer* Renderer::mRenderer = nullptr;

/*
@fn	�p�[�e�B�N���p���_��ݒ�
*/
void Renderer::SetParticleVertex()
{
	m2DParticleVertex->SetActive();
	m3DParticleVertex->SetActive();
}

/*
@fn	�R���X�g���N�^
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
@fn	�f�X�g���N�^
*/
Renderer::~Renderer()
{
}

/*
@fn		�C���X�^���X���쐬����
*/
void Renderer::CreateInstance()
{
	if (mRenderer == nullptr)
	{
		mRenderer = new Renderer();
	}
}

/*
@fn		�C���X�^���X���폜����
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
@fn		����������
@return true : ���� , false : ���s(bool�^)
*/
bool Renderer::Initialize(float _screenWidth, float _screenHeight, bool _fullScreen)
{
	mScreenWidth = _screenWidth;
	mScreenHeight = _screenHeight;

	// OpenGL�̊e������ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// OpenGL�̎g�p�o�[�W������3.3�Ɏw��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�e�`�����l��8�r�b�g�̃J���[�o�b�t�@���g��
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// �n�[�h�E�F�A�A�N�Z�����[�V�������g��
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//�E�B���h�E�̍쐬
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
		printf("SDLRenderer�̍쐬�Ɏ��s : %s", SDL_GetError());
		return false;
	}

	// OpenGL�̃R���e�L�X�g���쐬
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW�̏�����
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ŏo�閳�Q�ȃG���[�R�[�h���N���A����
	glGetError();

	// �V�F�[�_�[�̃��[�h
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}


	////// �J�����O
	//glFrontFace(GL_CCW);
	//glEnable(GL_FRONT_FACE);

	//�X�v���C�g�p�̒��_�z����쐬
	CreateSpriteVerts();

	CreateParticleVerts();

	// SDL_ttf�̏�����
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	// UI�̏������W�ɉ��Z�������W
	mAddPosition = Vector2::Zero;

	return true;
}

/*
@fn	�I������
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
@fn	���[�h�����f�[�^�̉��
*/
void Renderer::UnloadData()
{
	// ���ׂẴe�N�X�`���̃f�[�^�����
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// ���ׂẴ��b�V���̃f�[�^�����
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
	// �t���[���̍ŏ��ŃJ���[�o�b�t�@�ƃf�v�X�o�b�t�@���N���A
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// �[�x�o�b�t�@�ւ̏������݂𖳌��ɂ���
	glDepthMask(GL_FALSE);
	// RGBA�J���[�l�ƃJ���[�o�b�t�@�[���̒l���u�����h
	glEnable(GL_BLEND);

	// �f�v�X�o�b�t�@�@�𖳌��ɂ���
	glDisable(GL_DEPTH_TEST);
	// �X�v���C�g�V�F�[�_�[���A�N�e�B�u�ɂ���/�X�v���C�g���_�z���L���ɂ���
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();
	for (auto UI : mUis)
	{
		if (UI->GetVisible())
		{
			UI->Draw(mSpriteShader);
		}
	}

	// 2D�G�t�F�N�g�������
	if (!mParticles[EffectType::e2D].empty())
	{
		// �p�[�e�B�N���̕`��(2D)
		DrawParticle(EffectType::e2D);
	}

	// �[�x�o�b�t�@�ւ̏������݂�L���ɖ߂�
	glDepthMask(GL_TRUE);
	// �f�v�X�o�b�t�@�@��L���ɂ���
	glEnable(GL_DEPTH_TEST);

	// RGBA�J���[�l�ƃJ���[�o�b�t�@���̒l���u�����h
	glEnable(GL_BLEND);
	// ����L���ɂ���
	glEnable(GL_ALPHA_TEST);
	// �s�N�Z���̐F�ɐV�����F��g�ݍ��킹�鏈��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// ���b�V���R���|�[�l���g�̕`��
	// ��{�I�ȃ��b�V���V�F�[�_�[���A�N�e�B�u�ɂ���
	mMeshShader->SetActive();
	// �r���[�ˉe�s����X�V����
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
	SetLightUniforms(mMeshShader, mView);
	// ���ׂẴ��b�V���̕`��
	for (auto mc : mMeshComponents)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

	// �����ɂ���
	glDisable(GL_BLEND);
	// ���𖳌��ɂ���
	glDisable(GL_ALPHA_TEST);

	// ���b�V���R���|�[�l���g�̕`��
	// ��{�I�ȃ��b�V���V�F�[�_�[���A�N�e�B�u�ɂ���
	mSkinnedShader->SetActive();
	// �r���[�ˉe�s����X�V����
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);
	// �V�F�[�_�[�ɓn�����C�e�B���O�����X�V����
	SetLightUniforms(mSkinnedShader, mView);
	// ���ׂẴ��b�V���̕`��
	for (auto skMc : mSkeletalMeshes)
	{
		if (skMc->GetVisible())
		{
			skMc->Draw(mSkinnedShader);
		}
	}

	// �[�x�o�b�t�@�ւ̏������݂𖳌��ɂ���
	glDepthMask(GL_FALSE);
	// RGBA�J���[�l�ƃJ���[�o�b�t�@�[���̒l���u�����h
	glEnable(GL_BLEND);

	//// 2D�G�t�F�N�g�������
	//if (!mParticles[EffectType::e2D].empty())
	//{
	//	// �p�[�e�B�N���̕`��(2D)
	//	DrawParticle(EffectType::e2D);
	//}
	// 3D�G�t�F�N�g�������
	if(!mParticles[EffectType::e3D].empty())
	{
		// �p�[�e�B�N���̕`��(3D)
		DrawParticle(EffectType::e3D);
	}

	// �[�x�o�b�t�@�ւ̏������݂�L���ɖ߂�
	glDepthMask(GL_TRUE);


	// �����蔻���`�悷��
	PHYSICS->DebugShowBox();

	// �o�b�t�@������
	SDL_GL_SwapWindow(mWindow);
}



void Renderer::AddUI(UIComponent* _ui)
{
	// (DrawOrder�����������Ԃɕ`�悷�邽��)������UI����}������ꏊ�̌���
	// ���g��DrawOrder���擾
	int myUiDrawOrder = _ui->GetDrawOrder();
	// ������UI�Ԃ��
	auto iterUi = mUis.begin();
	for (;
		iterUi != mUis.end();
		++iterUi)
	{
		// ���g��DrawOrder�ƁA���񂵂Ă���DrawOrder���ׂĎ��g�̂ق������������
		if (myUiDrawOrder < (*iterUi)->GetDrawOrder())
		{
			break;
		}
	}

	// ���������ꏊ��iter�̏ꏊ�ɑ}��
	mUis.insert(iterUi, _ui);
}

void Renderer::RemoveUI(UIComponent* _ui)
{
	// �폜����N���X�̃|�C���^������
	auto iterUi = find(mUis.begin(), mUis.end(), _ui);
	// ��������UI���폜
	mUis.erase(iterUi);
}

void Renderer::AddParticle(ParticleComponent* _particleComponent)
{
	// ���݂̃G�t�F�N�g�̃G�t�F�N�g�^�C�v��ۑ�
	EffectType type;
	if (_particleComponent->GetEffectType() == EffectType::e2D)
	{
		type = EffectType::e2D;	// 2D
	}
	else
	{
		type = EffectType::e3D;	// 3D
	}

	// (DrawOrder�����������Ԃɕ`�悷�邽��)������G�t�F�N�g����}������ꏊ�̌���
	// ���g��DrawOrder���擾
	int myDrawOrder = _particleComponent->GetDrawOrder();
	// ������G�t�F�N�g�Ԃ��(�G�t�F�N�g�^�C�v��)
	auto iter = mParticles[type].begin();
	for (;
		iter != mParticles[type].end();
		++iter)
	{
		// ���g��DrawOrder�ƁA���񂵂Ă���DrawOrder���ׂĎ��g�̂ق������������
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// ���������ꏊ��iter�̏ꏊ�ɑ}��
	mParticles[type].insert(iter, _particleComponent);
}

void Renderer::RemoveParticle(ParticleComponent* _particleComponent)
{
	// �폜����N���X�̃|�C���^������
	// �G�t�F�N�g�̃^�C�v�ɂ���ĉ񂷃L�[��ς���
	EffectType nowEffectType = _particleComponent->GetEffectType();

	auto iter = find(mParticles[nowEffectType].begin(), mParticles[nowEffectType].end(), _particleComponent);
	// ��������UI���폜
	mParticles[nowEffectType].erase(iter);
}

/*
@fn		���b�V���R���|�[�l���g�̒ǉ�
@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
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
@fn		���b�V���R���|�[�l���g�̍폜
@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
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
@param _fileName ���f���ւ̃A�h���X
@return �X�P���g�����f���̎擾(class Skeleton)
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
@param _fileName �A�j���[�V�����ւ̃A�h���X
@return �X�P���g���A�j���[�V�����̎擾(class Animation)
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
@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
@return Texture�N���X�̃|�C���^(class Texture)
*/
Texture* Renderer::GetTexture(const std::string& _fileName)
{
	Texture* texture = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto itr = mTextures.find(_fileName);
	if (itr != mTextures.end())
	{
		texture = itr->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�����e�N�X�`�����쐬
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
@param	_fileName �擾���������b�V���̃t�@�C����
@return Mesh�N���X�̃|�C���^(class Mesh)
*/
Mesh* Renderer::GetMesh(const std::string& _fileName)
{
	Mesh* m = nullptr;
	//���łɍ쐬����ĂȂ������ׂ�
	auto iter = mMeshes.find(_fileName);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	//�쐬�ς݂łȂ��ꍇ�A�V�������b�V�����쐬
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
@fn		�V�F�[�_�[�̓ǂݍ���
@return true : ���� , false : ���s(bool�^)
*/
bool Renderer::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[�̍쐬
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// �r���[�s��̐ݒ�
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

	// �r���[�s��̐ݒ�
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		mScreenWidth, mScreenHeight, 25.0f, 7000.0f);

	// �W���̃��b�V���V�F�[�_�[�̍쐬
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
	{
		return false;
	}

	// ���b�V��
	mMeshShader->SetActive();
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mBasicShader = new Shader();
	if (!mBasicShader->Load("Shaders/BasicMesh.vert", "Shaders/BasicMesh.frag"))
	{
		return false;
	}
	// �V���v���ȃ��b�V���V�F�[�_�[
	mBasicShader->SetActive();
	mBasicShader->SetMatrixUniform("uViewProj", mView * mProjection);

	mParticleShader = new Shader();
	if (!mParticleShader->Load("Shaders/Phong.vert", "Shaders/Particle.frag"))
	{
		printf("�V�F�[�_�[�ǂݍ��ݎ��s\n");
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
@fn	Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // ����
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // �E��
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // �E��
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // ����
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

/*
@fn	Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
*/
void Renderer::CreateParticleVerts()
{
	// 2D�o�[�e�b�N�X
	{
		float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // ����
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // �E��
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // �E��
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // ����
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		m2DParticleVertex = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);

	}

	// 3D�o�[�e�b�N�X
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

	// �u�����h���[�h������Ԏ擾
	//ParticleComponent::ParticleBlendType blendType, prevType;
	//auto itr = mParticles[_effectType].begin();
	//blendType = prevType = (*itr)->GetBlendType();

	// �V�F�[�_�[ON
	mParticleShader->SetActive();
	// �r���[�v���W�F�N�V�����s��
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

	// ���ׂẴp�[�e�B�N����`��
	for (auto particle : mParticles[_effectType])
	{
		// �p�[�e�B�N���̕`��t���O��true�̎�
		if (particle->GetVisible())
		{
			////�u�����h���[�h�ύX���K�v�Ȃ�ύX����
			//blendType = particle->GetBlendType();
			//if (blendType != prevType)
			//{
			//	ChangeBlendMode(blendType);
			//}

			// �p�[�e�B�N���`��
			particle->Draw(mParticleShader);

			// �O��`���ԂƂ��ĕۑ�
			//prevType = blendType;
		}
	}
}

/*
@fn	Particle�̕`��
@param	_framebuffer �t���[���o�b�t�@
@param	_view �r���[�s��
@param	_proj �v���W�F�N�V�����s��
@param	_viewPortScale �\���̈�X�P�[��
@param	_lit ���������V�F�[�_�[�̕ϐ��ɃZ�b�g���邩�̃t���O
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
@fn		���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
@param	_view �r���[�s��
*/
void Renderer::SetLightUniforms(Shader* _shader, const Matrix4& _view)
{
	// �r���[�s����t�s��ɂ���
	Matrix4 invView = _view;
	invView.Invert();
	_shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// �����̐ݒ�
	_shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// ���s�����̐ݒ�
	_shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.m_direction);
	_shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.m_diffuseColor);
	_shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.m_specColor);
}

/*
@fn		���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
@param  _blendType �p�[�e�B�N���ɑ΂���u�����h�̎��
*/
void Renderer::ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType)
{
	switch (_blendType)
	{
	case ParticleComponent::ParticleBlendType::eAddBlend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);  //���Z����
		break;
	case ParticleComponent::ParticleBlendType::eAlphaBlend:
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // �A���t�@�u�����h
		break;
	case ParticleComponent::ParticleBlendType::eMultBlend:
		glBlendFunc(GL_ZERO, GL_SRC_COLOR); //��Z����
		break;
	default:
		break;
	}
}

/*
@fn		�e�N�X�`���̕ύX
@param	_changeTextureID �ύX����e�N�X�`����id
*/
void Renderer::ChangeTexture(int _changeTextureID)
{
	glBindTexture(GL_TEXTURE_2D, _changeTextureID);
}

/*
@fn	���[���h��Ԃ̃J�������W���v�Z
*/
Vector3 Renderer::CalcCameraPos()
{
	// �r���[�s���胏�[���h�ł̃J�����ʒu�Z�o
	Matrix4 transMat = mView;

	// �r���[�s��̈ړ������������
	Vector3 v;
	v.x = -1.0f * mView.mat[3][0];
	v.y = -1.0f * mView.mat[3][1];
	v.z = -1.0f * mView.mat[3][2];

	//�ړ���������菜�������Ɠ]�u���āA��]�����̋t�ϊ������
	transMat.mat[3][0] = transMat.mat[3][1] = transMat.mat[3][2] = 0.0f;
	transMat.Transpose();

	return Vector3(Vector3::Transform(v, transMat));
}
