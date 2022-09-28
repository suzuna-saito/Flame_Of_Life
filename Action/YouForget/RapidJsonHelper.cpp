#include "pch.h"

bool OpenJsonFile(rapidjson::Document& _inputDocument, const char* _inFileName)
{
	// ファイルを開けるか
	ifstream file(_inFileName);
	// ファイルが開けなかったら
	if (!file)
	{
		printf("このファイルは開けませんでした : %s", _inFileName);
		return false;   // falseを返す
	}
	// filestreamにファイル文字列を取り込む
	stringstream fileStream;
	fileStream << file.rdbuf();	// ファイルのストリームバッファを文字列ストリームに挿入
	// contentsに文字列を保存
	string contents = fileStream.str();
	// ファイル文字列をjson文字列に変換
	rapidjson::StringStream jsonStr(contents.c_str());
	// ファイルを閉じる
	file.close();

	// 解析オブジェクト作成
	_inputDocument.ParseStream(jsonStr);
	// オブジェクトとして読めなかったら
	if (!_inputDocument.IsObject())
	{
		printf("このjsonファイルはjsonObjectとして読めませんでした : %s", _inFileName);
		return false;   // falseを返す
	}

	return true;
}

bool IsExistMember(const rapidjson::Document& _inputDocument, const char* _memberName)
{
	// _memberNameがこのドキュメント内に存在するか確認
	rapidjson::Value::ConstMemberIterator itr;
	itr = _inputDocument.FindMember(_memberName);
	// 存在しなかったら
	if (itr == _inputDocument.MemberEnd())
	{
		return false;   // falseを返す
	}

	return true;
}

bool IsExistMemberAndValue(const rapidjson::Document& _inputDocument, const char* _memberName, const char* _matchValue)
{
	// メンバーが存在しなかったら
	if (!IsExistMember(_inputDocument, _memberName))
	{
		return false;   // falseを返す
	}

	string findValueString;
	findValueString = string(_matchValue);

	// 値が一致しなかったら
	if (findValueString != _inputDocument[_memberName].GetString())
	{
		printf("このメンバは値が一致しませんでした : %s", _memberName);
		return false;   // falseを返す
	}

	return true;
}

bool IsExistArrayName(const rapidjson::Document& _inputDocument, const char* _memberName)
{
	// メンバーが存在しなかったら
	if (!IsExistMember(_inputDocument, _memberName))
	{
		return false;   // falseを返す
	}

	// メンバが存在し、それがArrayの場合はtrueを返す。そうでなければfalseを返します。
	return _inputDocument[_memberName].IsArray();
}

float ForceGetFloat(const rapidjson::Value& _val)
{
	// stringの型に一度変換
	string tmp;
	tmp = _val.GetString();
	// atof()…文字ストリングから浮動小数点への変換
	return static_cast<float>(atof(tmp.c_str()));
}
