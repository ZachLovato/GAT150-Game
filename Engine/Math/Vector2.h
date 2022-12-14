#pragma once
#include <cmath>
#include <sstream>
#include <string>

namespace wrap
{
	struct Vector2
	{
		float x, y;

		Vector2() : x{ 0 }, y{ 0 } {}
		Vector2(float x, float y) : x{ x }, y{ y } {}
		Vector2(float v) : x{ v }, y{ v } {}
		Vector2(int x, int y) : x{ (float)x }, y{ (float)y }{}

		void set(float x, float y) { this->x = x; this->y = y; }

		float operator [] (size_t index) const { return (&x)[index]; }
		float& operator [] (size_t index) { return (&x)[index]; }

		//arithmetic operator
		// Vector2 = Vector2 + Vector2
		Vector2 operator + (const Vector2& v) const { return Vector2{ this->x + v.x, this->y + v.y }; }
		Vector2 operator - (const Vector2& v) const { return Vector2{ this->x - v.x, this->y - v.y }; }
		Vector2 operator * (const Vector2& v) const { return Vector2{ this->x * v.x, this->y * v.y }; }
		Vector2 operator / (const Vector2& v) const { return Vector2{ this->x / v.x, this->y / v.y }; }

		//Vector2 = Vector 2 + float 
		Vector2 operator + (float s) { return Vector2{ this->x + s, this->y + s }; }
		Vector2 operator - (float s) { return Vector2{ this->x - s, this->y - s }; }
		Vector2 operator * (float s) { return Vector2{ this->x * s, this->y * s }; }
		Vector2 operator / (float s) { return Vector2{ this->x / s, this->y / s }; }

		//assignment operators
		Vector2& operator += (const Vector2& v) { this->x += v.x; this->y += v.y; return *this; }
		Vector2& operator -= (const Vector2& v) { this->x -= v.x; this->y -= v.y; return *this; }
		Vector2& operator *= (const Vector2& v) { this->x *= v.x; this->y *= v.y; return *this; }
		Vector2& operator /= (const Vector2& v) { this->x /= v.x; this->y /= v.y; return *this; }

		Vector2& operator += (float s) { this->x += s; this->y += s; return *this; }
		Vector2& operator -= (float s) { this->x -= s; this->y -= s; return *this; }
		Vector2& operator *= (float s) { this->x *= s; this->y *= s; return *this; }
		Vector2& operator /= (float s) { this->x /= s; this->y /= s; return *this; }

		//unary
		// Vector2 = -Vector2
		Vector2 operator - () { return Vector2{-x, -y}; }

		//conparision
		//Vector2 == Vectoer2 
		bool operator == (const Vector2& v) const { return (this->x == v.x && this->y == v.y); }
		bool operator != (const Vector2& v) const { return (this->x != v.x && this->y != v.y); }

		float LengthSqr();
		float Length();

		float DistanceSqr(const Vector2& v);
		float Distance(const Vector2& v);

		float Dot(const Vector2& v);
		float GetAngleBetween(const Vector2& v);
		float GetSignedAngleBetween(const Vector2& v);

		Vector2 Normalized();
		void Norm();
		float GetAngle();

		static Vector2 Rotate(const Vector2& v, float angle);

		static const Vector2 one;
		static const Vector2 zero;
		static const Vector2 up;
		static const Vector2 down;
		static const Vector2 left;
		static const Vector2 right;

	};

	std::istream& operator >> (std::istream& stream, Vector2& v);
	std::ostream& operator << (std::ostream& stream, const Vector2& v);


		// functions
		inline float Vector2::LengthSqr() { return x * x + y * y; }

		inline float Vector2::Length() { return std::sqrt(x * x + y * y); }

		inline float Vector2::DistanceSqr(const Vector2& v)
		{
			return ((*this) - v).LengthSqr();
		}

		inline float Vector2::Distance(const Vector2& v)
		{
			return ((*this) - v).Length();
		}

		inline float Vector2::Dot(const Vector2& v)
		{
			return x * v.x + y * v.y;
		}

		inline float Vector2::GetAngleBetween(const Vector2& v)
		{
			return std::acos(Dot(v));
		}

		inline float Vector2::GetSignedAngleBetween(const Vector2& v)
		{
			float y = x * v.y - y * v.x; // perpendicular dot product
			float x = x * v.x + y * v.y; // dor product
			return std::atan2(y, x);

		}

		inline Vector2 Vector2::Normalized()
		{
			float length = Length();
			return (length == 0) ? Vector2{ 0 ,0 } : Vector2{x / length, y / length};
		}
		
		inline void Vector2::Norm()
		{
			(*this) /= Length();
		}

		inline float Vector2::GetAngle()
		{
			return std::atan2(y, x);
		}

		inline Vector2 Vector2::Rotate(const Vector2& v, float angle)
		{
			float x = v.x * std::cos(angle) - v.y * std::sin(angle);
			float y = v.x * std::sin(angle) + v.y * std::cos(angle);

			return Vector2{ x,y };
		}



}