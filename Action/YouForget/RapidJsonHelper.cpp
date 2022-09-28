#include "pch.h"

bool OpenJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// �t�@�C�����J���邩
	ifstream file(_inFileName);
	// �t�@�C�����J���Ȃ�������
	if (!file)
	{
		printf("���̃t�@�C���͊J���܂���ł��� : %s", _inFileName);
		return false;   // false��Ԃ�
	}
	// filestream�Ƀt�@�C�����������荞��
	stringstream fileStream;
	fileStream << file.rdbuf();	// �t�@�C���̃X�g���[���o�b�t�@�𕶎���X�g���[���ɑ}��
	// contents�ɕ������ۑ�
	string contents = fileStream.str();
	// �t�@�C���������json������ɕϊ�
	rapidjson::StringStream jsonStr(contents.c_str());
	// �t�@�C�������
	file.close();

	// ��̓I�u�W�F�N�g�쐬
	_inputDocument.ParseStream(jsonStr);
	// �I�u�W�F�N�g�Ƃ��ēǂ߂Ȃ�������
	if (!_inputDocument.IsObject())
	{
		printf("����json�t�@�C����jsonObject�Ƃ��ēǂ߂܂���ł��� : %s", _inFileName);
		return false;   // false��Ԃ�
	}

	return true;
}

bool IsExistMember(const rapidjson::Document& _inputDocument, const char* _memberName)
{
	// _memberName�����̃h�L�������g���ɑ��݂��邩�m�F
	rapidjson::Value::ConstMemberIterator itr;
	itr = _inputDocument.FindMember(_memberName);
	// ���݂��Ȃ�������
	if (itr == _inputDocument.MemberEnd())
	{
		return false;   // false��Ԃ�
	}

	return true;
}

bool IsExistMemberAndValue(const rapidjson::Document& _inputDocument, const char* _memberName, const char* _matchValue)
{
	// �����o�[�����݂��Ȃ�������
	if (!IsExistMember(_inputDocument, _memberName))
	{
		return false;   // false��Ԃ�
	}

	string findValueString;
	findValueString = string(_matchValue);

	// �l����v���Ȃ�������
	if (findValueString != _inputDocument[_memberName].GetString())
	{
		printf("���̃����o�͒l����v���܂���ł��� : %s", _memberName);
		return false;   // false��Ԃ�
	}

	return true;
}

bool IsExistArrayName(const rapidjson::Document& _inputDocument, const char* _memberName)
{
	// �����o�[�����݂��Ȃ�������
	if (!IsExistMember(_inputDocument, _memberName))
	{
		return false;   // false��Ԃ�
	}

	// �����o�����݂��A���ꂪArray�̏ꍇ��true��Ԃ��B�����łȂ����false��Ԃ��܂��B
	return _inputDocument[_memberName].IsArray();
}

float ForceGetFloat(const rapidjson::Value& _val)
{
	// string�̌^�Ɉ�x�ϊ�
	string tmp;
	tmp = _val.GetString();
	// atof()�c�����X�g�����O���畂�������_�ւ̕ϊ�
	return static_cast<float>(atof(tmp.c_str()));
}
