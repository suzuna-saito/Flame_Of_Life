/*
@brief	�C���N���[�h
*/
#include "pch.h"
//#include "Ground.h"
//#include "SamplePlayer.h"
#include "SceneBase.h"

/*
@fn	�R���X�g���N�^
*/
MapCreate::MapCreate() :GameObject(SceneBase::other, Tag::Other)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
	mOffset = 200;
}

/*
@fn	�f�X�g���N�^
*/
MapCreate::~MapCreate()
{
	mGroundMapData.clear();
}

/*
@fn		json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
@return	�t�@�C�����J������(bool�^)
*/
bool MapCreate::OpenFile()
{
	mScene = SceneBase::GetScene();

	//-----------------------------------------------
	//----------------tutorial-----------------------
	//-----------------------------------------------

	if (mScene == SceneBase::tutorial)
	{
		//���f�[�^�̓ǂݍ���
		if (!readTiledJson(mGroundMapData, "Assets/Config/tste2tmx.json", "layer1"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//�v���C���[�f�[�^�̓ǂݍ���
		if (!readTiledJson(mPlayerMapData, "Assets/Config/tste2tmx.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}
	}

	return false;
}

void MapCreate::CreateGround()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(-mOffset * ix, mOffset * iz, 0.0f);
			const Vector3 objectSize = Vector3(100, 100, 100);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(1):
					//new Ground(objectPos, objectSize, ground, SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}
}


/*
@fn	�v���C���[�𐶐�����
*/
void MapCreate::CreatePlayer()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mPlayerMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-mOffset * ix, mOffset * iz, 200.0f);
			Vector3 objectSize = Vector3(1.2f, 1.2f, 1.2f);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(2):
					//new SamplePlayer(objectPos, objectSize, player, SceneBase::tutorial);
					break;
				}
				break;
			}
		}
	}

}

bool MapCreate::readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName)
{
	//RapidJson�h�L�������g�Ƃ��ĊJ���邩�H
	rapidjson::Document doc;
	if (!openJsonFile(doc, _fileName))
	{
		return false;
	}

	//�J����document��type��map���H
	if (!IsExistMemberAndValue(doc, "type", "map"))
	{
		return false;
	}
	//�J����document��layer�͂��邩�H
	if (!IsExistArrayName(doc, "layers"))
	{
		return false;
	}
	//layer�����擾
	auto layer = doc["layers"].GetArray();
	int layerSize = layer.Size();

	//layer������Y��layer�̓Y�����𒲂ׂ�
	std::string layerNameString(_layerName);
	int layerIndex = findLayerIndex(layer, layerNameString);
	if (layerIndex < 0)
	{
		return false;
	}

	//layer���Ƀf�[�^�͂��邩�H
	rapidjson::Value::ConstMemberIterator itr = layer[layerIndex].FindMember("data");
	if (itr == layer[layerIndex].MemberEnd())
	{
		printf("���C���[��:%s�Ƀ}�b�v�f�[�^������܂���\n", _layerName);
		return false;
	}

	//���C���[���rapidjson�z��쐬
	const rapidjson::Value& rapidArrayData = layer[layerIndex]["data"].GetArray();
	int width, height;
	width = layer[layerIndex]["width"].GetInt();
	height = layer[layerIndex]["height"].GetInt();

	//���[�U�[�z��m�ہ@�s�����A������̏��ԂɃT�C�Y�m��
	_mapData.resize(height);
	for (auto& mapIter : _mapData)
	{
		mapIter.resize(width);
	}

	//���[�U�[�z��i2�����j�Ƀf�[�^���R�s�[
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			//�Ȃ���ID��+1����Ă���̂ŕ␳����
			_mapData[y][x] = rapidArrayData[y * width + x].GetInt();
		}
	}
	return true;
}

int MapCreate::findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName)
{
	int layerSize = _layer.Size();
	int i;
	std::string layerNameString(_layerName);
	for (i = 0; i < layerSize; i++)
	{
		std::string currentLayerName = _layer[i]["name"].GetString();
		printf("%s\n", currentLayerName.c_str());
		if (layerNameString == currentLayerName)
		{
			break;
		}
	}
	if (i == layerSize)
	{
		return -1;
	}
	return i;
}
