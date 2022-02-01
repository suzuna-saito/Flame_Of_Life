/*
@file Shader.h
@brief シェーダーデータ
*/

/*
@brief	プリプロセッサ
*/
#pragma once

class Shader
{
public:

	/*
	@fn	コンストラクタ
	*/
	Shader();

	/*
	@fn	デストラクタ
	*/
	~Shader();

	/*
	@fn		頂点シェーダーとフラグメントシェーダーのロード
	@param	_vertName 頂点シェーダーのファイル名
	@param	_fragName 頂点シェーダーのファイル名
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool Load(const std::string& _vertName, const std::string& _fragName);

	/*
	@fn	ロードしたシェーダーの解放
	*/
	void Unload();

	/*
	@fn	シェーダープログラムをアクティブにする
	*/
	void SetActive();

	/*
	@fn		行列のUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_matrix 設定する行列
	*/
	void SetMatrixUniform(const char* _name, const Matrix4& _matrix);

	/*
	@fn		行列のUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_matrices 設定する行列
	@param	_count 行列の数
	*/
	void SetMatrixUniforms(const char* _name, Matrix4* _matrices, unsigned _count);

	/*
	@fn		Vector3のUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_vector 設定するVector3
	*/
	void SetVectorUniform(const char* _name, const Vector3& _vector);

	/*
	@fn		floatのUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_value 設定するfloat
	*/
	void SetFloatUniform(const char* _name, const float& _value);

	/*
	@fn		intのUniform変数を設定する
	@param	_name 設定するUniform変数名
	@param	_value 設定するint
	*/
	void SetIntUniform(const char* _name, const int _value);

private:

	/*
	@fn		シェーダーをコンパイルする
	@param	_fileName コンパイルするシェーダーのファイル名
	@param	_shaderType シェーダーの種類
	@param	_outShader シェーダーのID用の参照変数
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool CompileShader(const std::string& _fileName, GLenum _shaderType, GLuint& _outShader);

	/*
	@fn		シェーダーがコンパイル出来ているか確認
	@param	_shader シェーダーのID
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool IsCompiled(GLuint _shader);

	/*
	@fn		シェーダーがリンク出来ているか確認
	@return	true : 成功 , false : 失敗(bool型)
	*/
	bool IsVaildProgram();

	//頂点シェーダー
	GLuint mVertexShader;
	//フラグメントシェーダー
	GLuint mFragShader;
	//シェーダープログラム
	//頂点シェーダーとフラグメントシェーダーを結合
	GLuint mShaderProgram;
};

