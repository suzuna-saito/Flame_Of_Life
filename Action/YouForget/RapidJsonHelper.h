/*
@brief	�v���v���Z�b�T
*/
#pragma once


/*
@fn		json�t�@�C���̃I�[�v��
@param	_inputDocument rapidJson�I�u�W�F�N�g
@param	_inFileName �I�[�v��������Json�t�@�C���p�X
return	�t�@�C�����J�����Ƃ��ł�����(bool�^)
*/
bool openJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName);

/*
@fn		Doc���ɂ��̃����o�[�͑��݂��邩�H
@param	_inDocument rapidJson�I�u�W�F�N�g
@param	_memberName �����o��
@return	Document�Ƀ����o�����܂܂�Ă������ǂ���(bool�^)
*/
bool IsExistMember(const rapidjson::Document& _inDoc, const char* _memberName);

/*
@fn		���̃����o�[�����݂��A���l����v���邩�H
@param	_inDocument �h�L�������g
@param	_menberName �����o�[��
@param	_matchValue ���ׂ��������o�[���Ƀ}�b�`����l
@return	memberName�ɑΉ�����l��matchValue�������Ƃ��̂�true��Ԃ�(bool�^)
*/
bool IsExistMemberAndValue(const rapidjson::Document& _inDoc, const char* _memberName, const char* _matchValue);

/*
@param	_inDocument �h�L�������g
@param	_menberName �����o�[��
@return	Document���Ƀ����o�����܂܂�邩(bool�^)
*/
bool IsExistArrayName(const rapidjson::Document& _inDoc, const char* _memberName);


/*
@fn		Value�l�������I��float�l�Ƃ��Ď擾
@brief	JSON�l����e��int�ł������I��float�l�Ƃ��Ď擾
@param	_val Value�l
@return	JSON�l(float�^)
*/
float ForceGetFloat(const rapidjson::Value& _val);