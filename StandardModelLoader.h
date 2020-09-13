#pragma once
#include "StandardModel.h"

namespace StandardModelLoader
{
	StandardModel loadObjAndDDS(const char* objName, const char* textureDDS);
	StandardModel loadCubeAndDDS(const char* textureDDS);
}