#pragma once
#include <string>
#include <vector>
#include <DxLib.h>
#include "../Common/Vector2.h"

class Utility
{

public:
	enum class STRING_PLACE	//������𑵂���ʒu
	{
		LEFT,		//������
		CENTER,		//��������
		RIGHT,		//�E����
	};

	static constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };

	// ��]��
	static constexpr VECTOR AXIS_X = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR AXIS_Y = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR AXIS_Z = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR AXIS_XZ = { 1.0f, 0.0f, 1.0f };
	static constexpr VECTOR AXIS_XY = { 1.0f, 1.0f, 1.0f };
	static constexpr VECTOR AXIS_YZ = { 0.0f, 1.0f, 1.0f };
	static constexpr VECTOR AXIS_XYZ = { 1.0f, 1.0f, 1.0f };

	// ����
	static constexpr VECTOR DIR_F = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR DIR_B = { 0.0f, 0.0f, -1.0f };
	static constexpr VECTOR DIR_R = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR DIR_L = { -1.0f, 0.0f, 0.0f };
	static constexpr VECTOR DIR_U = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR DIR_D = { 0.0f, -1.0f, 0.0f };

	//�J���[�R�[�h
	static constexpr int BLACK = 0x000000;	//��
	static constexpr int RED = 0xFF0000;	//��
	static constexpr int BLUE = 0x0000FF;	//��
	static constexpr int YELLOW = 0xFFFF00;	//���F
	static constexpr int GREEN = 0x008000;	//��
	static constexpr int CYAN = 0x00FFFF;	//���F
	static constexpr int PINK = 0xFFC0CB;	//���F
	static constexpr int ORANGE = 0xFFA500;	//�I�����W
	static constexpr int LIME = 0xADFF2F;	//����
	static constexpr int PURPLE = 0x800080;	//��
	static constexpr int WHITE = 0xFFFFFF;	//��
	static constexpr int GRAY = 0xBBBBBB;	//�D�F
	static constexpr int BROWN = 0x8B4513;	//���F

	// ���W�A��(rad)�E�x(deg)�ϊ��p
	static constexpr float RAD2DEG = (180.0f / DX_PI_F);
	static constexpr float DEG2RAD = (DX_PI_F / 180.0f);

	static constexpr float kEpsilonNormalSqrt = 1e-15F;

	// �l�̌ܓ�
	static int Round(float v);

	// ������̕���
	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ���W�A��(rad)����x(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// �x(deg)���烉�W�A��(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

	// 0�`360�x�͈̔͂Ɏ��߂�
	static double DegIn360(double deg);

	// 0(0)�`2��(360�x)�͈̔͂Ɏ��߂�
	static double RadIn2PI(double rad);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundRad(float from, float to);

	// ��]�����Ȃ����̉�]�������擾����(���v���:1�A�����v���:-1)
	static int DirNearAroundDeg(float from, float to);

	// ���`���
	static int Lerp(int start, int end, float t);
	static float Lerp(float start, float end, float t);
	static double Lerp(double start, double end, double t);
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float t);

	// �p�x�̐��`���
	static double LerpDeg(double start, double end, double t);

	// �x�W�F�Ȑ�
	static Vector2 Bezier(const Vector2& p1, const Vector2& p2, const Vector2& p3, float t);

	// �x�N�g���̒���
	static double Magnitude(const Vector2& v);
	static double Magnitude(const VECTOR& v);
	static float MagnitudeF(const VECTOR& v);
	static int SqrMagnitude(const Vector2& v);
	static float SqrMagnitudeF(const VECTOR& v);
	static double SqrMagnitude(const VECTOR& v);
	static double SqrMagnitude(const VECTOR& v1, const VECTOR& v2);
	static double Distance(const Vector2& v1, const Vector2& v2);
	static double Distance(const VECTOR& v1, const VECTOR& v2);

	// �摜�ǂݍ��݁i�G���[�`�F�b�N�t���j
	static void LoadImg(int& handle, std::string path);
	// �摜�ǂݍ��݁i�G���[�`�F�b�N�t���j
	static int LoadImg(std::string path);
	// �X�v���C�g�摜�ǂݍ��݁i�G���[�`�F�b�N�t���j
	static void LoadArrayImg(std::string path, int AllNum, int XNum, int YNum, int XSize, int YSize, int* handleArray);
	static void LoadArrayImg(std::string path, int AllNum, int XNum, int YNum, int XSize, int YSize, std::vector<int>& handleArray);

	// ���K��
	static VECTOR Normalize(const Vector2& v);
	static VECTOR VNormalize(const VECTOR& v);

	// ��r
	static bool Equals(const VECTOR& v1, const VECTOR& v2);
	static bool EqualsVZero(const VECTOR& v1);


	// 2�̃x�N�g���̊Ԃ̊p�x
	static double AngleDeg(const VECTOR& from, const VECTOR& to);
};

