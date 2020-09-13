#pragma once
#include "includes.h"

struct Light
{
	vec3 pos, color;
	Light(vec3 pos, vec3 color, float pwr)
		: pos(pos), color(color * pwr) {}
};