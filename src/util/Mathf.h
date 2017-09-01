#pragma once

#include <math.h>

// Defines math constants and helper functions that are not included in <math.h>.
namespace math
{
	using default_float_t = float;

	// Constant return value functions

	// Returns (PI).
	template<typename T = default_float_t>
	constexpr T pi()
	{
		return static_cast<T>(3.1415926535897932384626433832795);
	}

	// Returns (PI / 2).
	template<typename T = default_float_t>
	constexpr T pid2()
	{
		return static_cast<T>(1.5707963267948966192313216916398);
	}

	// Returns (PI * 2).
	template<typename T = default_float_t>
	constexpr T pim2()
	{
		return static_cast<T>(6.283185307179586476925286766559);
	}

	// Returns (PI / 4).
	template<typename T = default_float_t>
	constexpr T pid4()
	{
		return static_cast<T>(0.78539816339744830961566084581988);
	}

	// Returns (sqrt(2)).
	template<typename T = default_float_t>
	constexpr T sqrt2()
	{
		return static_cast<T>(1.4142135623730950488016887242097);
	}

	// Returns (sqrt(2) / 2).
	template<typename T = default_float_t>
	constexpr T sqrt2d2()
	{
		return static_cast<T>(0.70710678118654752440084436210485);
	}

	// Returns (PI / 180).
	template<typename T = default_float_t>
	constexpr T deg2Rad()
	{
		return static_cast<T>(0.01745329251994329576923690768489);
	}

	// Returns (180 / PI).
	template<typename T = default_float_t>
	constexpr T rad2Deg()
	{
		return static_cast<T>(57.295779513082320876798154814105);
	}

	// Helper functions

	// Returns the value of degrees in radians.
	template<typename T>
	inline T radians(T degrees)
	{
		return degrees * deg2Rad<T>();
	}

	// Returns the value of radians in degrees.
	template<typename T>
	inline T degrees(T radians)
	{
		return radians * rad2Deg<T>();
	}
}