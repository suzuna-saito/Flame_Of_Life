/*
@file Renderer.h
@brief �`��̐i�s���s���N���X
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


#define RENDERER Renderer::mRenderer

//���s�����p�̍\����
struct DirectionalLight
{
	// ���̕���
	Vector3 m_direction;
	// �g�U���ːF
	Vector3 m_diffuseColor;
	// ���ʔ��ːF
	Vector3 m_specColor;
};

/*
@enum �e�N�X�`���X�e�[�W
*/
enum class TextureStage
{
	DiffuseMap,
	NormalMap,
	SpecularMap,
	EmissiveMap,
	ShadowMap,
};

class Texture;
class Shader;
//class VertexArray;
class Font;

class Renderer
{
public:

	/*
	@fn	�C���X�^���X���쐬����
	*/
	static void CreateInstance();

	/*
	@fn	�C���X�^���X���폜����
	*/
	static void DeleteInstance();

	/*
	@fn		����������
	@return true : ���� , false : ���s(bool�^)
	*/
	bool Initialize(float _screenWidth, float _screenHeight, bool _fullScreen);

	/*
	@fn	�I������
	*/
	void Shutdown();

	/*
	@fn	���[�h�����f�[�^�̉��
	*/
	void UnloadData();

	/*
	@fn	�`�揈��
	*/
	void Draw();


	/// <summary>
	/// UI�̒ǉ�
	/// </summary>
	/// <param name="_ui">�ǉ�����UI�N���X�̃|�C���^</param>
	void AddUI(UIComponent* _ui);
	/// <summary>
	/// UI�̍폜
	/// </summary>
	/// <param name="_ui">�폜����UI�N���X�̃|�C���^</param>
	void RemoveUI(UIComponent* _ui);

	/// <summary>
	/// �p�[�e�B�N���̒ǉ�
	/// </summary>
	/// <param name="_particleComponent">�ǉ�����ParticleObject�N���X�̃|�C���^</param>
	void AddParticle(ParticleComponent* _particleComponent);
	/// <summary>
	/// �p�[�e�B�N���̍폜
	/// </summary>
	/// <param name="_particleComponent">�폜����ParticleObject�N���X�̃|�C���^</param>
	void RemoveParticle(ParticleComponent* _particleComponent);

	/*
	@fn		���b�V���R���|�[�l���g�̒ǉ�
	@param	_meshComponent�@�ǉ�����MeshComponent�N���X�̃|�C���^
	*/
	void AddMeshComponent(MeshComponent* _meshComponent);

	/*
	@fn		���b�V���R���|�[�l���g�̍폜
	@param	_meshComponent�@�폜����MeshComponent�N���X�̃|�C���^
	*/
	void RemoveMeshComponent(MeshComponent* _meshComponent);

	//�����̃C���X�^���X
	static Renderer* mRenderer;

private:

	//�R���X�g���N�^�A�f�X�g���N�^�̉B��
	Renderer();
	~Renderer();

	// �X�P���g���f�[�^
	std::unordered_map<std::string, class Skeleton*> mSkeletons;
	// �A�j���[�V�����f�[�^
	std::unordered_map<std::string, class Animation*> mAnims;
	// �X�P���g�����b�V���̕`��Ɏg����
	std::vector<class SkeletalMeshComponent*>       mSkeletalMeshes;

	//�����_���[�̏�Ԃ��܂ލ\����
	SDL_Renderer* mSdlRenderer;

	/*
	@fn		���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _shader �Z�b�g����Shader�N���X�̃|�C���^
	@param	_view �r���[�s��
	*/
	void SetLightUniforms(Shader* _shader, const Matrix4& _view);


	/*
	@fn		�V�F�[�_�[�̓ǂݍ���
	@return true : ���� , false : ���s(bool�^)
	*/
	bool LoadShaders();

	/*
	@fn	Sprite�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateSpriteVerts();

	/*
	@fn	Particle�p�̒��_�o�b�t�@�ƃC���f�b�N�X�o�b�t�@�̍쐬
	*/
	void CreateParticleVerts();

	// Particle�̕`��
	void DrawParticle();

	/*
	@fn	Particle�̕`��
	@param	_framebuffer �t���[���o�b�t�@
	@param	_view �r���[�s��
	@param	_proj �ˉe�s��
	@param	_viewPortScale �\���̈�X�P�[��
	@param	_lit ���������V�F�[�_�[�̕ϐ��ɃZ�b�g���邩�̃t���O
	*/
	void Draw3DScene(unsigned int _framebuffer, const Matrix4& _view, const Matrix4& _proj,
		float _viewPortScale = 1.0f, bool _lit = true);

	/*
	@fn		���������V�F�[�_�[�̕ϐ��ɃZ�b�g����
	@param  _blendType �p�[�e�B�N���ɑ΂���u�����h�̎��
	*/
	void ChangeBlendMode(ParticleComponent::ParticleBlendType _blendType);

	/*
	@fn		�e�N�X�`���̕ύX
	@param	_changeTextureID �ύX����e�N�X�`����id
	*/
	void ChangeTexture(int _changeTextureID);

	/*
	@fn	���[���h��Ԃ̃J�������W���v�Z
	*/
	Vector3 CalcCameraPos();

	//�t�@�C�����Ń��b�V�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Mesh*> mMeshes;
	//���b�V���R���|�[�l���g�̃|�C���^�̉ϒ��R���e�i
	std::vector<MeshComponent*> mMeshComponents;
	//UI�̃|�C���^�̉ϒ��R���e�i
	std::vector<UIComponent*> mUis;
	//�p�[�e�B�N���̃|�C���^
	std::vector<ParticleComponent*> mParticles;
	//�t�@�C�����Ńe�N�X�`�����擾���邽�߂̘A�z�z��
	std::unordered_map<std::string, Texture*> mTextures;

	// �t�H���g�}�b�v
	std::unordered_map<std::string, class Font*> fonts;

	// ���ԕ\���p�̃t�H���gtexture
	// ���F
	std::vector<Texture*> timeFontTextures;

	//�N���X�̃|�C���^
	//�X�v���C�g
	Shader* mSpriteShader;

	//�X�v���C�g�p���_
	class VertexArray* mSpriteVerts;

	//���b�V��
	Shader* mMeshShader;

	//�X�L�����b�V��
	class Shader* mSkinnedShader;
	Shader* mBasicShader;
	//�p�[�e�B�N��
	Shader* mParticleShader;
	//�p�[�e�B�N���p���_
	class VertexArray* mParticleVertex;

	//�r���[�s��
	Matrix4 mView;
	//�ˉe�s��
	Matrix4 mProjection;

	// �������ԗp�t�H���gtexture�̍ő吔�i��肽�������̍ő�l�j
	const int MaxTimeFontTextures;
	// �������ԗp�t�H���g�̃T�C�Y
	const int TimeFontSize;

	//�X�N���[���̉���
	float mScreenWidth;
	//�X�N���[���̏c��
	float mScreenHeight;
	//����
	Vector3 mAmbientLight;
	//���s����
	DirectionalLight mDirLight;
	//�E�B���h�E
	SDL_Window* mWindow;

	//�R���e�L�X�g
	SDL_GLContext mContext;

	// UI�̏������W�ɉ��Z�������W
	Vector2 mAddPosition;

	//���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��
	unsigned int mUndefineTexID;

public://�Q�b�^�[�Z�b�^�[

	/*
	@fn		�C���X�^���X���擾����
	@return Renderer�N���X�̃C���X�^���X(class Renderer)
	*/
	static Renderer* GetInstance() { return mRenderer; }

	/*
	@param	_fileName�@�擾�������e�N�X�`���̃t�@�C����
	@return Texture�N���X�̃|�C���^(class Texture)
	*/
	Texture* GetTexture(const std::string& _fileName);

	/*
	* @@@
	@brief	�J�E���g�_�E���^�C�����Ƃ�TimeTexture������Ă���֐��i���j
	@param	�J�E���g�_�E���^�C��
	@return �J�E���g�_�E���^�C�����Ƃ�TimeTexture
	*/
	Texture* GetTimeTexture(int _time);

	// @@@
	// �e�X�g�@�A�C�e���̐�
	Texture* GetItemCountTexture(int _count);
	/*
	@param _fileName ���f���ւ̃A�h���X
	@return �X�P���g�����f���̎擾(class Skeleton)
	*/
	const class Skeleton* GetSkeleton(const char* _fileName);

	/*
	@param _fileName �A�j���[�V�����ւ̃A�h���X
	@return �X�P���g���A�j���[�V�����̎擾(class Animation)
	*/
	const class Animation* GetAnimation(const char* _fileName);                     // �X�P���^���A�j���[�V�����̎擾

	/*
	@param	_fileName �擾���������b�V���̃t�@�C����
	@return Mesh�N���X�̃|�C���^(class Mesh)
	*/
	Mesh* GetMesh(const std::string& _fileName);

	/*
	@return	���s�����̍\����(struct DirectionalLight�j
	*/
	DirectionalLight& GetDirectionalLight() { return mDirLight; }


	/*
	@return	�r���[�s��(class Matrix4)
	*/
	Matrix4 GetViewMatrix() const { return mView; };

	/*
	@return	�ˉe�s��(class Matrix4)
	*/
	Matrix4 GetProjectionMatrix() { return mProjection; }

	/*
	@return	�ˉe�s��(class Matrix4)
	*/
	SDL_Renderer* GetSDLRenderer() { return mSdlRenderer; }

	/*
	@return	���ݒ�e�N�X�`���̏ꍇ�Ɋ��蓖�Ă��鍕�F�e�N�X�`��(unsigned int�^)
	*/
	unsigned int GetUndefineTexID() { return mUndefineTexID; }

	/*
	@param	_view �r���[�s��
	*/
	void SetViewMatrix(const Matrix4& _view) { mView = _view; }

	/*
	@param	_ambient�i������\���j
	*/
	void SetAmbientLight(const Vector3& _ambient) { mAmbientLight = _ambient; }

	/*
	@fn	�p�[�e�B�N���p���_��ݒ�
	*/
	void SetParticleVertex();

};