/*
@file Shader.h
@brief �V�F�[�_�[�f�[�^
*/

/*
@brief	�C���N���[�h
*/
#include "pch.h"

/*
@fn	�R���X�g���N�^
*/
Shader::Shader()
	: mVertexShader(0)
	, mFragShader(0)
	, mShaderProgram(0)
{
}

/*
@fn	�f�X�g���N�^
*/
Shader::~Shader()
{
}

/*
@fn		���_�V�F�[�_�[�ƃt���O�����g�V�F�[�_�[�̃��[�h
@param	_vertName ���_�V�F�[�_�[�̃t�@�C����
@param	_fragName ���_�V�F�[�_�[�̃t�@�C����
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::Load(const std::string& _vertName, const std::string& _fragName)
{
	if (!CompileShader(_vertName, GL_VERTEX_SHADER, mVertexShader) ||
		!CompileShader(_fragName, GL_FRAGMENT_SHADER, mFragShader))
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader);
	glAttachShader(mShaderProgram, mFragShader);
	glLinkProgram(mShaderProgram);

	if (!IsVaildProgram())
	{
		return false;
	}

	return true;
}

/*
@fn	���[�h�����V�F�[�_�[�̉��
*/
void Shader::Unload()
{
	glDeleteProgram(mShaderProgram);
	glDeleteShader(mVertexShader);
	glDeleteShader(mFragShader);
}

/*
@fn	�V�F�[�_�[�v���O�������A�N�e�B�u�ɂ���
*/
void Shader::SetActive()
{
	glUseProgram(mShaderProgram);
}

/*
@fn		�s���Uniform�ϐ���ݒ肷��
@param	_name �ݒ肷��Uniform�ϐ���
@param	_matrix �ݒ肷��s��
*/
void Shader::SetMatrixUniform(const char* _name, const Matrix4& _matrix)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _name);
	// �V�F�[�_�[�ɍs��f�[�^�𑗂�
	glUniformMatrix4fv(loc, 1, GL_TRUE, _matrix.GetAsFloatPtr());
}

/*
@fn		�s���Uniform�ϐ���ݒ肷��
@param	_name �ݒ肷��Uniform�ϐ���
@param	_matrices �ݒ肷��s��
@param	_count �s��̐�
*/
void Shader::SetMatrixUniforms(const char* _name, Matrix4* _matrices, unsigned _count)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _name);
	// �s��z��f�[�^���V�F�[�_�[�ϐ��ɑ���
	glUniformMatrix4fv(loc, _count, GL_TRUE, _matrices->GetAsFloatPtr());
}

/*
@fn		Vector3��Uniform�ϐ���ݒ肷��
@param	_name �ݒ肷��Uniform�ϐ���
@param	_vector �ݒ肷��Vector3
*/
void Shader::SetVectorUniform(const char* _name, const Vector3& _vector)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _name);
	// �V�F�[�_�[��Vector�f�[�^�𑗂�
	glUniform3fv(loc, 1, _vector.GetAsFloatPtr());
}

/*
@fn		Vector3��Uniform�ϐ���ݒ肷��
@param	_name �ݒ肷��Uniform�ϐ���
@param	_vector �ݒ肷��Vector3
*/
void Shader::SetFloatUniform(const char* _name, const float& _value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _name);
	// �V�F�[�_�[��float�f�[�^�𑗂�
	glUniform1f(loc, _value);
}

/*
@fn		int��Uniform�ϐ���ݒ肷��
@param	_name �ݒ肷��Uniform�ϐ���
@param	_value �ݒ肷��int
*/
void Shader::SetIntUniform(const char* _name, const int _value)
{
	GLuint loc = glGetUniformLocation(mShaderProgram, _name);
	// �V�F�[�_�[��int�f�[�^�𑗂�
	glUniform1i(loc, _value);
}

/*
@fn		�V�F�[�_�[���R���p�C������
@param	_fileName �R���p�C������V�F�[�_�[�̃t�@�C����
@param	_shaderType �V�F�[�_�[�̎��
@param	_outShader �V�F�[�_�[��ID�p�̎Q�ƕϐ�
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::CompileShader(const std::string& _fileName, GLenum _shaderType, GLuint& _outShader)
{
	std::ifstream shaderFile(_fileName);
	if (shaderFile.is_open())
	{
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::ifstream().swap(shaderFile);
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		_outShader = glCreateShader(_shaderType);

		glShaderSource(_outShader, 1, &(contentsChar), nullptr);
		glCompileShader(_outShader);

		if (!IsCompiled(_outShader))
		{
			SDL_Log("Failed to compile shader %s", _fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", _fileName.c_str());
		return false;
	}

	return true;
}

/*
@fn		�V�F�[�_�[���R���p�C���o���Ă��邩�m�F
@param	_shader �V�F�[�_�[��ID
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::IsCompiled(GLuint _shader)
{
	GLint status;

	glGetShaderiv(_shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(_shader, 411, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

/*
@fn		�V�F�[�_�[�������N�o���Ă��邩�m�F
@return	true : ���� , false : ���s(bool�^)
*/
bool Shader::IsVaildProgram()
{
	GLint status;

	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}
	return true;
}
