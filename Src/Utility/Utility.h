#pragma once
#include <string>
#include <vector>
#include <DxLib.h>
#include "../Common/Vector2.h"

class Utility
{

public:

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
	static int SqrMagnitude(const Vector2& v);
	static double Distance(const Vector2& v1, const Vector2& v2);

	// �摜�ǂݍ��݁i�G���[�`�F�b�N�t���j
	static void LoadImg(int& handle, std::string path);
	// �摜�ǂݍ��݁i�G���[�`�F�b�N�t���j
	static int LoadImg(std::string path);
	// �X�v���C�g�摜�ǂݍ��݁i�G���[�`�F�b�N�t���j
	static void LoadArrayImg(std::string path, int AllNum, int XNum, int YNum, int XSize, int YSize, int* handleArray);
	static void LoadArrayImg(std::string path, int AllNum, int XNum, int YNum, int XSize, int YSize, std::vector<int>& handleArray);
};

