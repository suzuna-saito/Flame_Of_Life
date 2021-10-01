/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn		�e�N�X�`���X�e�[�W��ǂݍ���
@param	_doc rapidJson�I�u�W�F�N�g
@param	_texStage �e�N�X�`���X�e�[�W
@param	_stgString �����o��
@return	�e�N�X�`����ID(int�^)
*/
int LoadStageTextures(const rapidjson::Document& _doc, TextureStage _texStage, const char* _stgString);

namespace
{
	union Vertex
	{
		float f;
		uint8_t b[4];
	};
}

/*
@fn	�R���X�g���N�^
*/
Mesh::Mesh()
	: mVertexArray(nullptr)
	, mRadius(0.0f)
	, mSpecPower(100.0f)
	, mLuminance(1.0f)
	, mAlpha(1.0f)
	, mBox(Vector3::Infinity, Vector3::NegInfinity)
{
	mStageDefTexture.emplace(TextureStage::DiffuseMap, 0);
	mStageDefTexture.emplace(TextureStage::NormalMap, 0);
	mStageDefTexture.emplace(TextureStage::SpecularMap, 0);
	mStageDefTexture.emplace(TextureStage::EmissiveMap, 0);
}

/*
@fn		���b�V���f�[�^�̓ǂݍ���
@param	_fileName ���[�h���������b�V���̃t�@�C����
@param	_renderer Renderer�N���X�̃|�C���^
@return true : ���� , false : ���s(bool�^)
*/
bool Mesh::Load(const std::string& _fileName, Renderer* _renderer)
{
	std::ifstream file(_fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Mesh %s", _fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Mesh %s is not valid json", _fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// �o�[�W�����̃`�F�b�N
	if (ver != 1)
	{
		SDL_Log("Mesh %s not version 1", _fileName.c_str());
		return false;
	}

	mShaderName = doc["shader"].GetString();

	// Skip the vertex format/shader for now
	// (This is changed in a later chapter's code)
	// ���_���C�A�E�g�ƃT�C�Y���t�@�C������Z�b�g
	VertexArray::Layout layout = VertexArray::PosNormTex;
	size_t vertSize = 8;

	std::string vertexFormat = doc["vertexformat"].GetString();
	if (vertexFormat == "PosNormSkinTex")
	{
		layout = VertexArray::PosNormSkinTex;
		// This is the number of "Vertex" unions, which is 8 + 2 (for skinning)s�@1�̒��_�̏W���̐��@�W�@�{�@�Q�i�X�L�j���O���j
		// 3 (�ʒuxyz) + 3(�@��xyz) + 2(Bone�Əd�݁j�{�@2(UV)  �̌v�@10���i40byte) �@
		vertSize = 10;
	}

	// �e�N�X�`���̃��[�h
	const rapidjson::Value& readTextures = doc["textures"];
	if (!readTextures.IsArray() || readTextures.Size() < 1)
	{
		SDL_Log("Mesh %s has no textures, there should be at least one", _fileName.c_str());
		return false;
	}
	mSpecPower = static_cast<float>(doc["specularPower"].GetDouble());

	// �G�~�b�V�u���x�l�i��`����Ă����)
	if (IsExistMember(doc, "luminance"))
	{
		mLuminance = ForceGetFloat(doc["luminance"]);
	}

	// �����x
	if (IsExistMember(doc, "alpha"))
	{
		mAlpha = ForceGetFloat(doc["alpha"]);
	}

	for (rapidjson::SizeType i = 0; i < readTextures.Size(); i++)
	{
		// ���łɃ��[�h���ꂽ�e�N�X�`������Ȃ������ׂ�
		std::string texName = readTextures[i].GetString();
		Texture* t = _renderer->GetTexture(texName);
		if (t == nullptr)
		{
			// �e�N�X�`�������[�h����
			t = _renderer->GetTexture(texName);
			if (t == nullptr)
			{
				// �e�N�X�`�������[�h�ł��Ȃ������ꍇ�A�f�t�H���g�̃e�N�X�`�����g�p
				t = _renderer->GetTexture("Assets/Default.png");
			}
		}
		mTextures.emplace_back(t);

		if (readTextures.Size() == 1)
		{
			mStageDefTexture[TextureStage::DiffuseMap] = t->GetTextureID();
		}
	}

	// �e�N�X�`���ǂݍ���(�V�t�@�C���`��)
	if (IsExistMember(doc, "diffusemap"))
	{
		mStageDefTexture[TextureStage::DiffuseMap] = LoadStageTextures(doc, TextureStage::DiffuseMap, "diffusemap");
	}
	mStageDefTexture[TextureStage::NormalMap] = LoadStageTextures(doc, TextureStage::NormalMap, "normalmap");
	mStageDefTexture[TextureStage::SpecularMap] = LoadStageTextures(doc, TextureStage::SpecularMap, "specularmap");
	mStageDefTexture[TextureStage::EmissiveMap] = LoadStageTextures(doc, TextureStage::EmissiveMap, "emissivemap");

	// ���_�z��f�[�^�����[�h
	const rapidjson::Value& vertsJson = doc["vertices"];
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", _fileName.c_str());
		return false;
	}

	std::vector<Vertex> vertices;
	vertices.reserve(vertsJson.Size() * vertSize);
	mRadius = 0.0f;
	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); i++)
	{
		// ���̂Ƃ���͂W�̗v�f�Ƃ���
		const rapidjson::Value& vert = vertsJson[i];
		if (!vert.IsArray())
		{
			SDL_Log("Unexpected vertex format for %s", _fileName.c_str());
			return false;
		}
		///////////////////////////////////////////////////////////////////////////////
		Vector3 pos(static_cast<float>(vert[0].GetDouble()),
			static_cast<float>(vert[1].GetDouble()),
			static_cast<float>(vert[2].GetDouble()));
		//verts.push_back(pos);
		mRadius = Math::Max(mRadius, pos.LengthSq());

		if (i == 0)
		{
			mBox.InitMinMax(pos);
		}
		mBox.UpdateMinMax(pos);

		// ���_���C�A�E�g�� PosNormTex�Ȃ�i�{�[���������j
		if (layout == VertexArray::PosNormTex)
		{
			Vertex v;
			// Add the floats�@float�l��ǉ�
			for (rapidjson::SizeType j = 0; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
		else
		{
			Vertex v;
			// Add pos/normal�@���_�Ɩ@����ǉ��@6��
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}

			// Add skin information�@�X�L�����ǉ��i�{�[���ԍ�:unsigned char��1�o�C�g���j
			for (rapidjson::SizeType j = 6; j < 14; j += 4)  //���[�v�Ƃ��Ă�2��]����@1��]�ڂ̓{�[���ԍ��A2��]�ڂ̓{�[���E�F�C�g��int�Ƃ��Ď���Ă���i�g�p���ɕ���������������ۂ��j
			{
				v.b[0] = vert[j].GetUint();
				v.b[1] = vert[j + 1].GetUint();
				v.b[2] = vert[j + 2].GetUint();
				v.b[3] = vert[j + 3].GetUint();
				vertices.emplace_back(v);
			}

			// Add tex coords�@�e�N�X�`�����W
			for (rapidjson::SizeType j = 14; j < vert.Size(); j++)
			{
				v.f = static_cast<float>(vert[j].GetDouble());
				vertices.emplace_back(v);
			}
		}
	}

	// ���a��2�悷��
	mRadius = Math::Sqrt(mRadius);

	// �v�f�z��f�[�^�̃��[�h
	const rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", _fileName.c_str());
		return false;
	}

	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); i++)
	{
		const rapidjson::Value& ind = indJson[i];
		if (!ind.IsArray() || ind.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", _fileName.c_str());
			return false;
		}

		indices.emplace_back(ind[0].GetUint());
		indices.emplace_back(ind[1].GetUint());
		indices.emplace_back(ind[2].GetUint());
	}

	// ������VertexArray�N���X�̍쐬
	mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned>(vertices.size()) / vertSize,
		layout, indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

/*
@fn	���[�h�������b�V���f�[�^�̉��
*/
void Mesh::Unload()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

/*
@param	_index �e�N�X�`���T�C�Y
@return Texture�N���X�̃|�C���^(class Texture)
*/
Texture* Mesh::GetTexture(size_t _index)
{
	if (_index < mTextures.size())
	{
		return mTextures[_index];
	}
	else
	{
		return nullptr;
	}
}

/*
@param	_stage �e�N�X�`���X�e�[�W
@return �e�N�X�`����ID(int�^)
*/
int Mesh::GetTextureID(TextureStage _stage)
{
	return mStageDefTexture[_stage];
}

/*
@fn		�e�N�X�`���X�e�[�W��ǂݍ���
@param	_doc rapidJson�I�u�W�F�N�g
@param	_texStage �e�N�X�`���X�e�[�W
@param	_stgString �����o��
@return	�e�N�X�`����ID(int�^)
*/
int LoadStageTextures(const rapidjson::Document& _doc, TextureStage _texStage, const char* _stgString)
{
	std::string noneTexture("none");
	std::string texName;
	Texture* t;
	if (IsExistMember(_doc, _stgString))
	{
		texName = _doc[_stgString].GetString();
		if (texName != noneTexture)
		{
			t = RENDERER->GetTexture(texName);
			if (t == nullptr)
			{
				t = RENDERER->GetTexture("Assets/Default.png");
			}
			return t->GetTextureID();
		}
	}
	return 0;
}
