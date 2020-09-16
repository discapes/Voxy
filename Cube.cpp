#include "Cube.h"

namespace Cube
{
	vec2 uvs[24]
	{
		/* 0 */
		{ 0, 1.f/3 },
		{ 1, 1.f/3 },
		{ 1, 1.f/3 },
		/* 1 */
		{ 0, 2.f/3 },
		{ 1, 2.f/3 },
		{ 1, 2.f/3 },
		/* 2 */
		{ 1, 2.f/3 },
		{ 0, 2.f/3 },
		{ 0, 2.f/3 },
		/* 3 */
		{ 1, 1.f/3 },
		{ 0, 1.f/3 },
		{ 0, 1.f/3 },
		/* 4 */
		{ 1, 1.f/3 },
		{ 1, 0 },
		{ 0, 1.f/3 },
		/* 5 */
		{ 1, 2.f/3 },
		{ 1, 1 },
		{ 0, 2.f/3 },
		/* 6 */
		{ 0, 2.f/3 },
		{ 0, 1 },
		{ 1, 2.f/3 },
		/* 7 */
		{ 0, 1.f/3 },
		{ 0, 0 },
		{ 1, 1.f/3 },
	};

#define x { 1, 0, 0 }
#define y { 0, 1, 0 }
#define z { 0, 0, 1 }
#define _x { -1, 0, 0 }
#define _y { 0, -1, 0 }
#define _z { 0, 0, -1 }

	vec3 normals[24]
	{
		 x, _y,  z,
		 x,  y,  z,
		_x,  y,  z,
		_x, _y,  z,
		 x, _y, _z,
		 x,  y, _z, 
		_x,  y, _z,
		_x, _y, _z
	};

#undef x 
#undef y
#undef z
#undef _x
#undef _y
#undef _z


	/*
	Wieku: You treat z=0 as being closer to the camera, if you treat z=0 as being farther from it (which you should, camera looks at negative z)
		then you can notice that triangle {0 7 4} is CW
		Flip z coordinate in box vertices and it should work
	*/

	vec3 vertices[24]
	{
		/* 0 */
		{ 0.5, -0.5, 0.5 },
		{ 0.5, -0.5, 0.5 },
		{ 0.5, -0.5, 0.5 },
		/* 1 */
		{ 0.5, 0.5, 0.5 },
		{ 0.5, 0.5, 0.5 },
		{ 0.5, 0.5, 0.5 },
		/* 2 */
		{ -0.5, 0.5, 0.5 },
		{ -0.5, 0.5, 0.5 },
		{ -0.5, 0.5, 0.5 },
		/* 3 */
		{ -0.5, -0.5, 0.5 },
		{ -0.5, -0.5, 0.5 },
		{ -0.5, -0.5, 0.5 },
		/* 4 */
		{ 0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 },
		{ 0.5, -0.5, -0.5 },
		/* 5 */
		{ 0.5, 0.5, -0.5 },
		{ 0.5, 0.5, -0.5 },
		{ 0.5, 0.5, -0.5 },
		/* 6 */
		{ -0.5, 0.5, -0.5 },
		{ -0.5, 0.5, -0.5 },
		{ -0.5, 0.5, -0.5 },
		/* 7 */
		{ -0.5, -0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },
		{ -0.5, -0.5, -0.5 },
	};

#define x *3+0
#define y *3+1
#define z *3+2
	unsigned short indices[36]
	{
		0 z, 1 z, 2 z,
		2 z, 3 z, 0 z,

		3 x, 2 x, 6 x,
		6 x, 7 x, 3 x,

		1 y, 5 y, 6 y,
		6 y, 2 y, 1 y,

		4 z, 7 z, 6 z,
		6 z, 5 z, 4 z,

		0 x, 4 x, 5 x,
		5 x, 1 x, 0 x,

		0 y, 3 y, 7 y,
		7 y, 4 y, 0 y
	};
#undef x
#undef y
#undef z

}