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

	/*
	@fn	�X�C�b�`�i���́j�𐶐�����
	*/
	void CreateSwitch();

	/*
	@fn	�A�C�e���𐶐�����
	*/
	void CreateItem();
private:

	bool readTiledJson(vector<vector<int>>& _mapData, const char* _fileName, const char* _layerName);

	int  findLayerIndex(rapidjson::GenericArray<false, rapidjson::Value>& _layer, string& _layerName);

	//���}�b�v�f�[�^
	vector<vector<int>> mGroundMapData;

	//�v���C���[�}�b�v�f�[�^
	vector<vector<int>> mPlayerMapData;
	//�낤�����}�b�v�f�[�^
	vector<vector<int>> mCandleMapData;
	//�X�C�b�`�i���́j�}�b�v�f�[�^
	vector<vector<int>> mSwitchMapData;
	//�A�C�e���}�b�v�f�[�^
	vector<vector<int>> mItemMapData;

	//���݂̃V�[��
	SceneBase::Scene mScene;
	//���̃}�b�v�f�[�^
	int	mSizeX;
	//�����̃}�b�v�f�[�^
	int	mSizeY;
	//���s�̃}�b�v�f�[�^
	int	mSizeZ;

	// ���̍��������炷
	float mChagePosY;
	float mHardChagePosY;

	//�I�u�W�F�N�g���Ƃ̋���
	float mOffsetX;
	float mOffsetY;
	float mOffsetZ;

	// ���̃X�P�[��
	const float MGroundScale;
	// �낤�����̃X�P�[��
	const float MCandleScale;
	// �v���C���[�̃X�P�[��
	const float MPlayerScale;
	// �X�C�b�`�i���́j�̃X�P�[��
	const float MSwitchScale;

	/* �A�C�e���֘A */
	// �L�i�A�C�e���j�̃X�P�[��
	const float MCatScale;
	const float MCharaScale;
	const float MLighterScale;
	const float MChairScale;
	const float MTreeScale;
	const float MSwordScale;
	
	int mItemCount;

	const float MPlayerZPos;
	// �n�ʂɖ��܂�Ȃ����߂ɂ낤�����ɑ����Ă�����|�W�V��������
	const float MCandleZPos;
	// �n�ʂɖ��܂�Ȃ����߂ɃA�C�e���ɑ����Ă�����|�W�V��������
	const float MItemZPos;
};

