/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
MapCreate::MapCreate() 
	:GameObject(SceneBase::other, Tag::Other)
	, MGroundScale(6.0f)
	, MCandleScale(4.0f)
	, MPlayerScale(5.0f)
	, MCandleZPos(60.0f)
	, MOffsetX(160.0f)
	, MOffsetY(-220.0f)
{
	mSizeX = 0;
	mSizeY = 0;
	mSizeZ = 0;
}

/*
@fn	�f�X�g���N�^
*/
MapCreate::~MapCreate()
{
	mGroundMapData.clear();
	mGroundMapData2.clear();
	mGroundMapData3.clear();
	mPlayerMapData.clear();
	mCandleMapData.clear();
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
		if (!readTiledJson(mGroundMapData, "Assets/Config/test.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//�v���C���[�f�[�^�̓ǂݍ���
		if (!readTiledJson(mPlayerMapData, "Assets/Config/test.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//�낤�����f�[�^�̓ǂݍ���
		if (!readTiledJson(mCandleMapData, "Assets/Config/test.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}

	//-----------------------------------------------
	//----------------stage0l------------------------
	//-----------------------------------------------
	if (mScene == SceneBase::stage01)
	{
		//���f�[�^�̓ǂݍ���
		if (!readTiledJson(mGroundMapData, "Assets/Config/map.json", "Ground"))
		{
			printf("don't have Layer/Ground\n");
			return true;
		}
		if (!readTiledJson(mGroundMapData2, "Assets/Config/map.json", "Ground2"))
		{
			printf("don't have Layer/Ground2\n");
			return true;
		}
		if (!readTiledJson(mGroundMapData3, "Assets/Config/map.json", "Ground3"))
		{
			printf("don't have Layer/Ground3\n");
			return true;
		}

		mSizeX = mGroundMapData[0].size();
		mSizeY = mGroundMapData[0].size();
		//mSizeZ = mGroundMapData.size();

		//�v���C���[�f�[�^�̓ǂݍ���
		if (!readTiledJson(mPlayerMapData, "Assets/Config/map.json", "Player"))
		{
			printf("don't have Layer/player\n");
			return true;
		}

		//�낤�����f�[�^�̓ǂݍ���
		if (!readTiledJson(mCandleMapData, "Assets/Config/map.json", "Candle"))
		{
			printf("don't have Layer/Candle\n");
			return true;
		}

	}


	return false;
}

/*
@fn	���𐶐�����
*/
void MapCreate::CreateGround()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mGroundMapData[(int)iz][(int)ix];
			const Vector3 objectPos = Vector3(-MOffsetX * ix, MOffsetY * iz, 0.0f);
			const Vector3 objectSize = Vector3(MGroundScale, MGroundScale, MGroundScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(1):
					new Ground(objectPos, objectSize, ground, SceneBase::stage01);
					break;
				case(3):
					new Ground(objectPos+Vector3(0.0f,0.0f,3.0f), objectSize, ground, SceneBase::stage01);
					break;
				case(4):
					new Ground(objectPos/* + Vector3(0.0f, 0.0f, 10.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				case(5):
					new Ground(objectPos/* + Vector3(0.0f, 0.0f, 15.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				case(6):
					new Ground(objectPos/* + Vector3(0.0f, 0.0f, 20.0f)*/, objectSize, ground, SceneBase::stage01);
					break;
				case(7):
					new Ground(objectPos /*+ Vector3(0.0f, 0.0f, 25.0f)*/, objectSize, ground, SceneBase::stage01);
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
			Vector3 objectPos = Vector3(-MOffsetX * ix, MOffsetY * iz, MCandleZPos);
			Vector3 objectSize = Vector3(MPlayerScale, MPlayerScale, MPlayerScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, player, SceneBase::tutorial);
					break;
				}
				break;

			case SceneBase::stage01:

				switch (name)
				{
				case(2):
					new Player(objectPos, objectSize, player, SceneBase::stage01);
					break;
				}
				break;
			}
		}
	}

}

/*
@fn	�낤�����𐶐�����
*/
void MapCreate::CreateCandle()
{
	for (float iz = 0; iz < mSizeY; iz++)
	{
		for (float ix = 0; ix < mSizeX; ix++)
		{
			const unsigned int name = mCandleMapData[(int)iz][(int)ix];
			Vector3 objectPos = Vector3(-MOffsetX * ix, MOffsetY * iz, MCandleZPos);
			Vector3 objectSize = Vector3(MCandleScale, MCandleScale, MCandleScale);

			switch (mScene)
			{
			case SceneBase::tutorial:

				switch (name)
				{
				case(3):
					new Candle(objectPos, objectSize, candle, SceneBase::tutorial);
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
