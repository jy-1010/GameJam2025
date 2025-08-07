#pragma once
#include <string>
#include <vector>
#include <DxLib.h>
#include "../Common/Vector2.h"

class Utility
{

public:
	enum class STRING_PLACE	//文字列を揃える位置
	{
		LEFT,		//左揃え
		CENTER,		//中央揃え
		RIGHT,		//右揃え
	};

	static constexpr VECTOR VECTOR_ZERO = { 0.0f, 0.0f, 0.0f };
	static constexpr VECTOR VECTOR_ONE = { 1.0f, 1.0f, 1.0f };

	// 回転軸
	static constexpr VECTOR AXIS_X = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR AXIS_Y = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR AXIS_Z = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR AXIS_XZ = { 1.0f, 0.0f, 1.0f };
	static constexpr VECTOR AXIS_XY = { 1.0f, 1.0f, 1.0f };
	static constexpr VECTOR AXIS_YZ = { 0.0f, 1.0f, 1.0f };
	static constexpr VECTOR AXIS_XYZ = { 1.0f, 1.0f, 1.0f };

	// 方向
	static constexpr VECTOR DIR_F = { 0.0f, 0.0f, 1.0f };
	static constexpr VECTOR DIR_B = { 0.0f, 0.0f, -1.0f };
	static constexpr VECTOR DIR_R = { 1.0f, 0.0f, 0.0f };
	static constexpr VECTOR DIR_L = { -1.0f, 0.0f, 0.0f };
	static constexpr VECTOR DIR_U = { 0.0f, 1.0f, 0.0f };
	static constexpr VECTOR DIR_D = { 0.0f, -1.0f, 0.0f };

	//カラーコード
	static constexpr int BLACK = 0x000000;	//黒
	static constexpr int RED = 0xFF0000;	//赤
	static constexpr int BLUE = 0x0000FF;	//青
	static constexpr int YELLOW = 0xFFFF00;	//黄色
	static constexpr int GREEN = 0x008000;	//緑
	static constexpr int CYAN = 0x00FFFF;	//水色
	static constexpr int PINK = 0xFFC0CB;	//桃色
	static constexpr int ORANGE = 0xFFA500;	//オレンジ
	static constexpr int LIME = 0xADFF2F;	//黄緑
	static constexpr int PURPLE = 0x800080;	//紫
	static constexpr int WHITE = 0xFFFFFF;	//白
	static constexpr int GRAY = 0xBBBBBB;	//灰色
	static constexpr int BROWN = 0x8B4513;	//茶色

	// ラジアン(rad)・度(deg)変換用
	static constexpr float RAD2DEG = (180.0f / DX_PI_F);
	static constexpr float DEG2RAD = (DX_PI_F / 180.0f);

	static constexpr float kEpsilonNormalSqrt = 1e-15F;

	// 四捨五入
	static int Round(float v);

	// 文字列の分割
	static std::vector <std::string> Split(std::string& line, char delimiter);

	// ラジアン(rad)から度(deg)
	static double Rad2DegD(double rad);
	static float Rad2DegF(float rad);
	static int Rad2DegI(int rad);

	// 度(deg)からラジアン(rad)
	static double Deg2RadD(double deg);
	static float Deg2RadF(float deg);
	static int Deg2RadI(int deg);

	// 0～360度の範囲に収める
	static double DegIn360(double deg);

	// 0(0)～2π(360度)の範囲に収める
	static double RadIn2PI(double rad);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundRad(float from, float to);

	// 回転が少ない方の回転向きを取得する(時計回り:1、反時計回り:-1)
	static int DirNearAroundDeg(float from, float to);

	// 線形補間
	static int Lerp(int start, int end, float t);
	static float Lerp(float start, float end, float t);
	static double Lerp(double start, double end, double t);
	static Vector2 Lerp(const Vector2& start, const Vector2& end, float t);

	// 角度の線形補間
	static double LerpDeg(double start, double end, double t);

	// ベジェ曲線
	static Vector2 Bezier(const Vector2& p1, const Vector2& p2, const Vector2& p3, float t);

	// ベクトルの長さ
	static double Magnitude(const Vector2& v);
	static double Magnitude(const VECTOR& v);
	static float MagnitudeF(const VECTOR& v);
	static int SqrMagnitude(const Vector2& v);
	static float SqrMagnitudeF(const VECTOR& v);
	static double SqrMagnitude(const VECTOR& v);
	static double SqrMagnitude(const VECTOR& v1, const VECTOR& v2);
	static double Distance(const Vector2& v1, const Vector2& v2);
	static double Distance(const VECTOR& v1, const VECTOR& v2);

	// 画像読み込み（エラーチェック付き）
	static void LoadImg(int& handle, std::string path);
	// 画像読み込み（エラーチェック付き）
	static int LoadImg(std::string path);
	// スプライト画像読み込み（エラーチェック付き）
	static void LoadArrayImg(std::string path, int AllNum, int XNum, int YNum, int XSize, int YSize, int* handleArray);
	static void LoadArrayImg(std::string path, int AllNum, int XNum, int YNum, int XSize, int YSize, std::vector<int>& handleArray);

	// 正規化
	static VECTOR Normalize(const Vector2& v);
	static VECTOR VNormalize(const VECTOR& v);

	// 比較
	static bool Equals(const VECTOR& v1, const VECTOR& v2);
	static bool EqualsVZero(const VECTOR& v1);


	// 2つのベクトルの間の角度
	static double AngleDeg(const VECTOR& from, const VECTOR& to);
};

