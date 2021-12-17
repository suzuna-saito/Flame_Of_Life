/*
@file Collision.h
@brief �����`����A�O�p�`���̃I�u�W�F�N�g�錾
*/

/*
@brief	�v���v���Z�b�T
*/
#pragma once


//����
struct LineSegment
{
	/*
	@param	_start �����̊J�n�n�_�̃|�W�V����
	@param	_end �����̏I���n�_�̃|�W�V����
	*/
	LineSegment(const Vector3& _start, const Vector3& _end);

	/*
	@fn		������̓_��Ԃ�
	@param	_t ���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����(Vector3�^)
	*/
	Vector3 PointOnSegment(float _t) const;

	/*
	@fn		�_�Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	_point �C�ӂ̓_�̃|�W�V����
	@return �ŒZ����(float�^)
	*/
	float MinDistanceSquared(const Vector3& _point)const;

	/*
	@fn		�����Ɛ����̊Ԃ̍ŒZ������Ԃ�
	@param	_line1 ���肷������̍\���̂P
	@param	_line2 ���肷������̍\���̂Q
	@return �ŒZ����(float�^)
	*/
	static float MinDistanceSquared(const LineSegment& _line1, const LineSegment& _line2);

	//�����̊J�n�n�_
	Vector3 m_start;
	//�����̏I���n�_
	Vector3 m_end;
};

//����
struct Plane
{
	/*
	@param	_normal ���ʂ̖@���x�N�g��
	@param	_distance ���ʂƌ��_�̕������ŒZ����
	*/
	Plane(const Vector3& _normal, float _distance);

	/*
	@param	_vec1 ���ʏ�̓_1
	@param	_vec2 ���ʏ�̓_2
	@param	_vec3 ���ʏ�̓_3
	*/
	Plane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3);

	/*
	@fn		�_�ƕ��ʂ̍ŒZ������Ԃ�
	@param	_point �C�ӂ̓_�̃|�W�V����
	@return �������ŒZ����(float�^)
	*/
	float SignedDistance(const Vector3& _point);

	//���ʂ̖@���x�N�g��
	Vector3 m_normal;
	//���ʂƌ��_�̕������ŒZ����
	float m_distance;
};

//��
struct Sphere
{
	/*
	@param	_center ���̂̒��S���W
	@param	_radius ���̂̔��a
	*/
	Sphere(const Vector3& _center, const float _radius);

	/*
	@fn		���̂ɓ_���܂܂�Ă��邩�ǂ���
	@param	_point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
	bool Contains(const Vector3& _point)const;

	//���̂̒��S���W
	Vector3 m_center;
	//���̂̔��a
	float m_radius;
};

//�����s�o�E���f�B���O�{�b�N�X(Axis-Aligned Bounding Box)
struct AABB
{
	/*
	@param	_min �ŏ���x,y,z�̒l�̃|�W�V����
	@param	_max �ő��x,y,z�̒l�̃|�W�V����
	*/
	AABB(const Vector3& _min, const Vector3& _max);

	/*
	@fn		�ŏ��l�ƍő�l���e�������ƂɍX�V����
	@param	_point �C�ӂ̓_�̃|�W�V����
	*/
	void UpdateMinMax(const Vector3& _point);

	/*
	@fn		�����蔻��{�b�N�X�̉�]
	@param	_quaternion ��]���Ɖ�]�\���l
	*/
	void Rotate(const Quaternion& _quaternion);

	/*
	@fn	�{�b�N�X�ɓ_���܂܂�Ă��邩�ǂ���
	@param	_point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
	bool Contains(const Vector3& _point)const;

	/*
	@fn		�_�ƃ{�b�N�X�̍ŒZ������Ԃ�
	@param	_point �C�ӂ̓_
	@return �ŒZ����
	*/
	float MinDistanceSquared(const Vector3& _point)const;

	/*
	@fn		�ŏ��l�ƍő�l��������
	@param	_point �C�ӂ̓_
	*/
	void InitMinMax(const Vector3& _point) { m_min = m_max = _point; };

	//�ŏ���x,y,z�̒l�̃|�W�V����
	Vector3 m_min;
	//�ő��x,y,z�̒l�̃|�W�V����
	Vector3 m_max;
};

//�L���o�E���f�B���O�{�b�N�X�iOriented Bounding Box�j
//������
struct OBB
{
	//���S�̍��W
	Vector3 m_center;
	//��]�N�H�[�^�j�I��
	Quaternion m_rotation;
	//�{�b�N�X�̍L����i���A�����A���s���j
	Vector3 m_extents;
};

//�J�v�Z��
struct Capsule
{
	/*
	@param	_start �n�_�ƂȂ�_�̍��W
	@param	_end �I�_�ƂȂ�_�̍��W
	@param	_radius �J�v�Z���̔��a
	*/
	Capsule(const Vector3& _start, const Vector3& _end, float _radius);

	/*
	@fn	�J�v�Z���̎n�_�ƏI�_�̐�����̓_��Ԃ�
	@param	_t ���͒l t�iL(t) = Start + (End - Start)t�j
	@return ������̓_�̃|�W�V����(Vector3�^)
	*/
	Vector3 PointOnSegment(float _t)const;

	/*
	@fn	�J�v�Z���ɓ_���܂܂�Ă��邩�ǂ���
	@param	_point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
	bool Contains(const Vector3& _point)const;

	//�J�v�Z�����\���������
	LineSegment m_segment;
	//�J�v�Z���̔��a
	float m_radius;
};

//�ʃ|���S��
struct ConvexPolygon
{
	/*
	@fn		�Q�����̃|���S���ɓ_���܂܂�Ă��邩�ǂ���
	@param	_point �C�ӂ̓_
	@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
	*/
	bool Contains(const Vector2& _point)const;

	//���_�̉ϒ��R���e�i
	std::vector<Vector2> m_vertices;
};

/*
@fn	���Ƌ��̓����蔻��
@param	_sphere1 ���̍\���̂P
@param	_sphere2 ���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const Sphere& _sphere1, const Sphere& _sphere2);

/*
@fn		�{�b�N�X�ƃ{�b�N�X�̓����蔻��
@param	_AABB1 �{�b�N�X�̍\���̂P
@param	_AABB2 �{�b�N�X�̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const AABB& _AABB1, const AABB& _AABB2);

/*
@fn		�J�v�Z���ƃJ�v�Z���̓����蔻��
@param	_capsule1 �J�v�Z���̍\���̂P
@param	_capsule2 �J�v�Z���̍\���̂Q
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const Capsule& _capsule1, const Capsule& _capsule2);

/*
@fn	���ƃ{�b�N�X�̓����蔻��
@param	_sphere ���̍\����
@param	_AABB �{�b�N�X�̍\����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const Sphere& _sphere, const AABB& _AABB);

/*
@fn	�����Ƌ��̓����蔻��
@param	_line �����̍\����
@param	_sphere ���̍\����
@param	_outT �����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const LineSegment& _line, const Sphere& _sphere, float& _outT);

/*
@fn	�����ƕ��ʂ̓����蔻��
@param	_line�@�����̍\����
@param	_plane�@���ʂ̍\����
@param	_outT�@�����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const LineSegment& _line, const Plane& _plane, float& _outT);

/*
@fn	�����ƃ{�b�N�X�̓����蔻��
@param	_line �����̍\����
@param	_AABB �{�b�N�X�̍\����
@param	_outT �����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@param	_outNorm �����̎n�_����ڐG�����ʂ̖@���x�N�g�����i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool Intersect(const LineSegment& _line, const AABB& _AABB, float& _outT,
	Vector3& _outNorm);

/*
@fn	���X�C�[�v�̓����蔻��
@param	_sphere1 �P�t���[���O�̋��P�̍\����
@param	_sphere2 ���݂̃t���[���̋��P�̍\����
@param	_sphere3 �P�t���[���O�̋��Q�̍\����
@param	_sphere4 ���݂̃t���[���̋��Q�̍\����
@param	_outT �����̎n�_����ڐG���Ă���_�܂ł̒lt���i�[����
@return true : �������Ă��� , false : �������Ă��Ȃ�(bool�^)
*/
bool SweptSphere(const Sphere& _sphere1, const Sphere& _sphere2,
	const Sphere& _sphere3, const Sphere& _sphere4, float& _outT);
