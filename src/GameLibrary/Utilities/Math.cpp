
#include "Math.h"
#include <cmath>
#include <cstdlib>

namespace GameLibrary
{
	const double Math::PI = 3.1415926535897931;

	//Trig
	double Math::sin(double radians){ return std::sin(radians); }
	float Math::sin(float radians){ return std::sin(radians); }
	long double Math::sin(long double radians){ return std::sin(radians); }
	double Math::cos(double radians){ return std::cos(radians); }
	float Math::cos(float radians){ return std::cos(radians); }
	long double Math::cos(long double radians){ return std::cos(radians); }
	double Math::tan(double radians){ return std::tan(radians); }
	float Math::tan(float radians){ return std::tan(radians); }
	long double Math::tan(long double radians){ return std::tan(radians); }
	double Math::asin(double sin){ return std::asin(sin); }
	float Math::asin(float sin){ return std::asin(sin); }
	long double Math::asin(long double x){ return std::asin(x); }
	double Math::acos(double cos){ return std::acos(cos); }
	float Math::acos(float cos){ return std::acos(cos); }
	long double Math::acos(long double cos){ return std::acos(cos); }
	double Math::atan(double tan){ return std::atan(tan); }
	float Math::atan(float tan){ return std::atan(tan); }
	long double Math::atan(long double x){ return std::atan(x); }
	double Math::atan2(double x, double y){ return std::atan2(x, y); }
	float Math::atan2(float x, float y){ return std::atan2(x, y); }
	long double Math::atan2(long double x, long double y){ return std::atan2(x, y); }

	//Logarithmic
	double Math::log(double arg){ return std::log(arg); }
	float Math::log(float arg){ return std::log(arg); }
	long double Math::log(long double arg){ return std::log(arg); }
	double Math::log(double base, double arg){ return std::log(arg) / std::log(base); }
	float Math::log(float base, float arg){ return std::log(arg) / std::log(base); }
	long double Math::log(long double base, long double arg){ return std::log(arg) / std::log(base); }
	double Math::log10(double arg){ return std::log10(arg); }
	float Math::log10(float arg){ return std::log10(arg); }
	long double Math::log10(long double arg){ return std::log10(arg); }

	//Powers
	double Math::pow(double base, double exponent){ return std::pow(base, exponent); }
	float Math::pow(float base, float exponent){ return std::pow(base, exponent); }
	long double Math::pow(long double base, long double exponent){ return std::pow(base, exponent); }
	double Math::sqrt(double arg){ return std::sqrt(arg); }
	float Math::sqrt(float arg){ return std::sqrt(arg); }
	long double Math::sqrt(long double arg){ return std::sqrt(arg); }

	//Rounding and remainders
	double Math::ceil(double arg){ return std::ceil(arg); }
	float Math::ceil(float arg){ return std::ceil(arg); }
	long double Math::ceil(long double arg){ return std::ceil(arg); }
	double Math::floor(double arg){ return std::floor(arg); }
	float Math::floor(float arg){ return std::floor(arg); }
	long double Math::floor(long double arg){ return std::floor(arg); }
	double Math::round(double arg){ return std::round(arg); }
	float Math::round(float arg){ return std::round(arg); }
	long double Math::round(long double arg){ return std::round(arg); }

	//Absolute Value
	double Math::abs(double arg){ return std::abs(arg); }
	float Math::abs(float arg){ return std::abs(arg); }
	long double Math::abs(long double arg){ return std::abs(arg); }
	int Math::abs(int arg){ return std::abs(arg); }
	long Math::abs(long arg){ return std::abs(arg); }
	
	//Min and Max
	double Math::min(double a, double b) { return (a<b) ? a : b; }
	float Math::min(float a, float b) { return (a<b) ? a : b; }
	long double Math::min(long double a, long double b) { return (a<b) ? a : b; }
	int Math::min(int a, int b) { return (a<b) ? a : b; }
	long Math::min(long a, long b) { return (a<b) ? a : b; }
	double Math::max(double a, double b) { return (a>b) ? a : b; }
	float Math::max(float a, float b) { return (a>b) ? a : b; }
	long double Math::max(long double a, long double b) { return (a>b) ? a : b; }
	int Math::max(int a, int b) { return (a>b) ? a : b; }
	long Math::max(long a, long b) { return (a>b) ? a : b; }

	//Angle Conversions
	double Math::degtorad(double deg){ return deg * PI / 180; }
	float Math::degtorad(float deg){ return deg * ((float)PI) / 180; }
	long double Math::degtorad(long double deg){ return deg * ((long double)PI) / 180; }
	double Math::radtodeg(double rad){ return rad * 180 / PI; };
	float Math::radtodeg(float rad){ return rad * 180 / ((float)PI); };
	long double Math::radtodeg(long double rad){ return rad * 180 / ((long double)PI); };

	//Random
	double Math::random() { return ((double)std::rand())/((double)(RAND_MAX)); }
}

