#pragma once
#include <string>
#include <SDL.h>
#include <iostream>

#include <cmath>
#include <chrono>
#include <cstdlib>
#include <vector>
#include "Color.h"


//#include "Stars3D.h"


using namespace std;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;
static float FOV = 100.0f;
#define getTime get_time::now();

static auto currentTime = get_time::now();
static auto previousTime = get_time::now();

static float getFOV() { return FOV; }
inline static int64_t getDelay()
{
	auto diff = currentTime - previousTime;
	int64_t tmp = chrono::duration_cast<ns>(diff).count();
	//cout << "Elapsed time is :  " << tmp << " ns " << endl;
	return tmp;
}

const float eps3 = 0.001f;
const float eps5 = 0.00001f;
const float UNDEFINED = INFINITY;
const float PI = 3.14159265f;
const float PIx2 = 6.28318530f;

// to radians: degrees * pi / 180
const float PI180 = PI / 180;

//indeksy refrakcji
const float REFRACTION_VACUUM = 1.0000f;
const float REFRACTION_AIR = 1.0003f;
const float REFRACTION_ICE = 1.3100f;
const float REFRACTION_WATER = 1.3330f;
const float REFRACTION_GASOLINE = 1.3980f;
const float REFRACTION_GLASS = 1.5500f;
const float REFRACTION_SAPPHIRE = 1.7700f;
const float REFRACTION_DIAMOND = 2.4190f;

typedef unsigned int nat;

inline float uRand();