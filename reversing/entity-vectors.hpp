#include <corecrt_math_defines.h>
#include "../stdafx/stdafx.hpp"
#include "../driver/m_driver.hpp"

class FRotator
{
public:
	FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f)
	{

	}

	FRotator(double _Pitch, double _Yaw, double _Roll) : Pitch(_Pitch), Yaw(_Yaw), Roll(_Roll)
	{

	}
	~FRotator()
	{

	}

	double Pitch;
	double Yaw;
	double Roll;

};

struct FVector {
	FVector() : x(), y(), z() {}
	FVector(double x, double y, double z) : x(x), y(y), z(z) {}

	FVector operator+ (const FVector& other) const { return { this->x + other.x, this->y + other.y, this->z + other.z }; }
	FVector operator- (const FVector& other) const { return { this->x - other.x, this->y - other.y, this->z - other.z }; }
	FVector operator* (double offset) const { return { this->x * offset, this->y * offset, this->z * offset }; }
	FVector operator/ (double offset) const { return { this->x / offset, this->y / offset, this->z / offset }; }

	FVector& operator*= (const double other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
	FVector& operator/= (const double other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

	FVector& operator= (const FVector& other) { this->x = other.x; this->y = other.y; this->z = other.z; return *this; }
	FVector& operator+= (const FVector& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
	FVector& operator-= (const FVector& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
	FVector& operator*= (const FVector& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
	FVector& operator/= (const FVector& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }

	operator bool() {
		return bool(this->x || this->y || this->z);
	}
	friend bool operator== (const FVector& a, const FVector& b) { return a.x == b.x && a.y == b.y && a.z == b.z; }
	friend bool operator!= (const FVector& a, const FVector& b) { return !(a == b); }

	double dot(const FVector& vector) {
		return x * vector.x + y * vector.y + z * vector.z;
	}
	double distance(FVector v) {
		return double(sqrt(pow(v.x - x, 2.0) + pow(v.y - y, 2.0) + pow(v.z - z, 2.0)));
	}
	bool IsValidAddress() const
	{
		return !(x == 0.f && y == 0.f && z == 0.f) || (x == -1.f && y == -1.f && z == -1.f);
	}

	double x, y, z;
};

struct FVector2D {
	FVector2D() : x(0), y(0) {}
	FVector2D(float x, float y) : x(x), y(y) {}

	FVector2D operator+ (const FVector2D& other) const { return { this->x + other.x, this->y + other.y }; }
	FVector2D operator- (const FVector2D& other) const { return { this->x - other.x, this->y - other.y }; }
	FVector2D operator* (float offset) const { return { this->x * offset, this->y * offset }; }
	FVector2D operator/ (float offset) const { return { this->x / offset, this->y / offset }; }

	FVector2D& operator*= (const float other) { this->x *= other; this->y *= other; return *this; }
	FVector2D& operator/= (const float other) { this->x /= other; this->y /= other; return *this; }

	FVector2D& operator= (const FVector2D& other) { this->x = other.x; this->y = other.y; return *this; }
	FVector2D& operator+= (const FVector2D& other) { this->x += other.x; this->y += other.y; return *this; }
	FVector2D& operator-= (const FVector2D& other) { this->x -= other.x; this->y -= other.y; return *this; }
	FVector2D& operator*= (const FVector2D& other) { this->x *= other.x; this->y *= other.y; return *this; }
	FVector2D& operator/= (const FVector2D& other) { this->x /= other.x; this->y /= other.y; return *this; }

	operator bool() { return bool(this->x || this->y); }
	friend bool operator== (const FVector2D& a, const FVector2D& b) { return a.x == b.x && a.y == b.y; }
	friend bool operator!= (const FVector2D& a, const FVector2D& b) { return !(a == b); }

	float distance(FVector2D v) {
		return float(sqrt(pow(v.x - x, 2.0) + pow(v.y - y, 2.0)));
	}
	bool IsValidAddress() const
	{
		return !(x == 0.f && y == 0.f) || (x == -1.f && y == -1.f);
	}

	float x, y;
};

inline double degree_to_radian(double degree) {
	return degree * (M_PI / 180);
}
inline FRotator GetRotation(const FVector& angles)
{
	FRotator forward;
	float sp, sy, cp, cy;

	sy = sin(degree_to_radian(angles.y));
	cy = cos(degree_to_radian(angles.y));

	sp = sin(degree_to_radian(angles.x));
	cp = cos(degree_to_radian(angles.x));

	forward.Yaw = cp * sy;
	forward.Pitch = cp * cy;
	forward.Roll = -sp;

	return forward;
}

struct TArray
{
	std::uintptr_t Array;
	std::uint32_t Count;
	std::uint32_t MaxCount;

	std::uintptr_t Get(std::uint32_t Index)
	{
		return pmem64->read<std::uintptr_t>(Array + (Index * 0x8));
	}
};

struct FPlane : public FVector
{
	double W;
};

struct FMatrix {
	FPlane XPlane, YPlane, ZPlane, WPlane;

	FMatrix MatrixMultiplication(FMatrix Other) {
		FMatrix Copy = {};

		Copy.WPlane.x = this->WPlane.x * Other.XPlane.x + this->WPlane.y * Other.YPlane.x + this->WPlane.z * Other.ZPlane.x + this->WPlane.W * Other.WPlane.x;
		Copy.WPlane.y = this->WPlane.x * Other.XPlane.y + this->WPlane.y * Other.YPlane.y + this->WPlane.z * Other.ZPlane.y + this->WPlane.W * Other.WPlane.y;
		Copy.WPlane.z = this->WPlane.x * Other.XPlane.z + this->WPlane.y * Other.YPlane.z + this->WPlane.z * Other.ZPlane.z + this->WPlane.W * Other.WPlane.z;
		Copy.WPlane.W = this->WPlane.x * Other.XPlane.W + this->WPlane.y * Other.YPlane.W + this->WPlane.z * Other.ZPlane.W + this->WPlane.W * Other.WPlane.W;

		return Copy;
	}

	static FMatrix RotatorToMatrix(FVector Rotation) {
		auto ReturnValue = FMatrix();

		auto Pitch = (Rotation.x * 3.14159265358979323846 / 180);
		auto Yaw = (Rotation.y * 3.14159265358979323846 / 180);
		auto Roll = (Rotation.z * 3.14159265358979323846 / 180);

		auto sp = sin(Pitch);
		auto cp = cos(Pitch);
		auto sy = sin(Yaw);
		auto cy = cos(Yaw);
		auto sr = sin(Roll);
		auto cr = cos(Roll);

		ReturnValue.XPlane.x = cp * cy;
		ReturnValue.XPlane.y = cp * sy;
		ReturnValue.XPlane.z = sp;

		ReturnValue.YPlane.x = sr * sp * cy - cr * sy;
		ReturnValue.YPlane.y = sr * sp * sy + cr * cy;
		ReturnValue.YPlane.z = -sr * cp;

		ReturnValue.ZPlane.x = -(cr * sp * cy + sr * sy);
		ReturnValue.ZPlane.y = cy * sr - cr * sp * sy;
		ReturnValue.ZPlane.z = cr * cp;

		ReturnValue.WPlane.W = 0x1;

		return ReturnValue;
	}
};

struct FTransform
{
	FPlane Rotation;
	FVector Translation;
	char pad_0[8];
	FVector Scale3D;
	char pad_1[4];

	FMatrix ToMatrix() {
		auto ReturnValue = FMatrix();

		auto x2 = this->Rotation.x * 2;
		auto y2 = this->Rotation.y * 2;
		auto z2 = this->Rotation.z * 2;

		auto xx2 = this->Rotation.x * x2;
		auto yy2 = this->Rotation.y * y2;
		auto zz2 = this->Rotation.z * z2;

		auto yz2 = this->Rotation.y * z2;
		auto wx2 = this->Rotation.W * x2;

		auto xy2 = this->Rotation.x * y2;
		auto wz2 = this->Rotation.W * z2;

		auto xz2 = this->Rotation.x * z2;
		auto wy2 = this->Rotation.W * y2;

		ReturnValue.XPlane.x = (1.0 - (yy2 + zz2)) * this->Scale3D.x;
		ReturnValue.XPlane.y = (xy2 + wz2) * this->Scale3D.x;
		ReturnValue.XPlane.z = (xz2 - wy2) * this->Scale3D.x;

		ReturnValue.YPlane.x = (xy2 - wz2) * this->Scale3D.y;
		ReturnValue.YPlane.y = (1.0 - (xx2 + zz2)) * this->Scale3D.y;
		ReturnValue.YPlane.z = (yz2 + wx2) * this->Scale3D.y;

		ReturnValue.ZPlane.x = (xz2 + wy2) * this->Scale3D.z;
		ReturnValue.ZPlane.y = (yz2 - wx2) * this->Scale3D.z;
		ReturnValue.ZPlane.z = (1.0 - (xx2 + yy2)) * this->Scale3D.z;

		ReturnValue.WPlane.x = this->Translation.x;
		ReturnValue.WPlane.y = this->Translation.y;
		ReturnValue.WPlane.z = this->Translation.z;

		ReturnValue.WPlane.W = 1.0;

		return ReturnValue;
	}
};

namespace customs {
	inline auto in_rect(double x, double y, double radius, double coord_x, double coord_y) -> bool {
		return coord_x >= x - radius && coord_x <= x + radius &&
			coord_y >= y - radius && coord_y <= y + radius;
	}

	inline auto in_circle(double x, double y, double radius, double coord_x, double coord_y) -> bool {
		if (in_rect(x, coord_y, radius, x, coord_y)) {
			double dx = x - coord_x;
			double dy = y - coord_y;
			dx *= dx;
			dy *= dy;
			double distance_squared = dx + dy;
			double radius_squared = radius * radius;

			return distance_squared <= radius_squared;
		}

		return false;
	}

	inline float degree_to_radian(float degree) {
		return degree * (M_PI / 180);
	}

	inline bool is_in_screen(FVector2D head_pos_dol, int width, int height) {
		if (((head_pos_dol.x <= 0 || head_pos_dol.x > width) && (head_pos_dol.y <= 0 || head_pos_dol.y > height)) || ((head_pos_dol.x <= 0 || head_pos_dol.x > width) || (head_pos_dol.y <= 0 || head_pos_dol.y > height))) {
			return false;
		}
		else {
			return true;
		}
	}
}