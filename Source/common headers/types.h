#pragma once

#ifdef _DEBUG
#define ASSERT(x) if(!(x)) __debugbreak();
#else
#define ASSERT(X)
#endif 

// Fundamental Data Types

typedef signed char        int8;
typedef short              int16;
typedef int                int32;
typedef long long          int64;
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef unsigned int       uint32;
typedef unsigned long long uint64;

typedef bool b8;
typedef int b32;		

typedef float f32;
typedef double f64;
//-----------------------


// Operations
namespace myops
{
	template <typename T>
	void swap(T &a, T &b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <typename T>
	T sqr(T& n)
	{
		return ((n) * (n));
	}
}


//-----------------------


// Math Data Types

template <typename t>
struct Vec2
{
	union
	{
		struct { t x, y; };
		t raw[2];
	};

	Vec2() :x(0), y(0) {}
	Vec2(t _x, t _y) : x(_x), y(_y) {}

	inline Vec2<t> operator + (Vec2<t>& n) { return Vec2<t>(x + n.x, y + n.y); };
	inline Vec2<t> operator - (Vec2<t>& n) { return Vec2<t>(x - n.x, y - n.y); };
	inline Vec2<t> operator * (f32 n) { return Vec2<t>(x * n, y * n); }


	inline t mag2() { return ((x * x) + (y * y)); };
};

template <typename t>
struct Vec3
{
	union
	{
		struct { t x, y, z; };
		t raw[3];
	};

	Vec3() :x(0), y(0), z(0) {}
	Vec3(t _x, t _y, t _z) : x(_x), y(_y), z(_z) {}

	inline Vec3<t> operator + (Vec3<t>& n) { return Vec2<t>(x + n.x, y + n.y, z + n.z); };
	inline Vec3<t> operator - (Vec3<t>& n) { return Vec2<t>(x - n.x, y - n.y); };
	inline Vec3<t> operator * (f32 n) { return Vec2<t>(x * n, y * n, z * n); };
	inline f32 operator * (Vec3<t>& n) { return (x * n.x) + (y * n.y) + (z * n.z); };

	inline f32 mag2() { return (x * x + y * y + z * z); };

};
//----------------------