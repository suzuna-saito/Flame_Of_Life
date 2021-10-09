/*
@brief	�v���v���Z�b�T
*/
#pragma once


class MapCreate : public GameObject
{
public:

	/*
	@fn	�R���X�g���N�^
	*/
	MapCreate();

	/*
	@fn	�f�X�g���N�^
	*/
	~MapCreate();

	/*
	@fn		json�t�@�C����RapidJson�œǂݍ���Ń}�b�v�f�[�^���e�z��Ɋi�[����
	@return	�t�@�C�����J������(bool�^)
	*/
	bool OpenFile();

	/*
	@fn	���𐶐�����
	*/
	void CreateGround();

	/*
	@fn	�v���C���[�𐶐�����
	*/
	void CreatePlayer();

	/*
	@fn	�낤�����𐶐�����
	*/
	void CreateCandle();
private:

	bool readTiledJson(std::vector<std::vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, std::string& _layerName);

	//���}�b�v�f�[�^
	std::vector<std::vector<int>> mGroundMapData;
	//�v���C���[�}�b�v�f�[�^
	std::vector<std::vector<int>> mPlayerMapData;
	//�낤�����}�b�v�f�[�^
	std::vector<std::vector<int>> mCandleMapData;

	//���݂̃V�[��
	int mScene;
	//���̃}�b�v�f�[�^
	int	mSizeX;
	//�����̃}�b�v�f�[�^
	int	mSizeY;
	//���s�̃}�b�v�f�[�^
	int	mSizeZ;

	//�I�u�W�F�N�g���Ƃ̋���
	float mOffset;

	// ���̃X�P�[��
	const float MGroundScale;
	// �낤�����̃X�P�[��
	const float MCandleScale;
	// �v���C���[�̃X�P�[��
	const float MPlayerScale;

	// �낤����(�v���C���[�܂�)�̏����|�W�V��������
	const float MCandleZPos;
};

