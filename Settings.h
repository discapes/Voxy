#pragma once

struct Settings
{
	int width = 1024;
	int height = 768;
	bool fullscreen = true;

	double lookSpeed = 1;
	double moveSpeed= 3;
	int FOV = 110;
};

extern Settings G; // should be named settings but too verbose