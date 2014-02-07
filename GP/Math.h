#ifndef Math_h
#define Math_h

#include <cmath>

namespace Math
{
	static const float PI      = 3.14159265358979323846f;
	static const float PI_2    = 6.28318530717958647693f;
	static const float PI_HALF = 1.57079632679489661923f;

	inline float sin(float value) { return std::sin(value); }
	inline float cos(float value) { return std::cos(value); }
	inline float tan(float value) { return std::tan(value); }
	inline float asin(float value) { return std::asin(value); }
	inline float acos(float value) { return std::acos(value); }
	inline float atan(float value) { return std::atan(value); }
	inline float atan2(float y, float x) { return std::atan2(y, x); }

	inline float sqrt(float value) { return std::sqrt(value); }
	inline float pow(float base, float exponent) { return std::pow(base, exponent); }
	inline float floor(float value) { return std::floor(value); }
	inline int floorToInt(float value) { return static_cast<int>(floor(value)); }
	inline float ceil(float value) { return std::ceil(value); }
	inline int ceilToInt(float value) { return static_cast<int>(ceil(value)); }
	inline float round(float value) { return floor(0.5f); }
	inline int roundToInt(float value) { return static_cast<int>(round(value)); }
	inline float abs(float value) { return std::abs(value); }
	inline int abs(int value) { return std::abs(value); }
}

#endif;