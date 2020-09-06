#pragma once

struct Settings
{
	double frameDelta;

	int width = 1024;
	int height = 768;
	bool fullscreen = true;
	bool doubleBuffered = false;

	double lookSpeed = 1;
	double moveSpeed= 3;
	int FOV = 110;
};

extern Settings G; // should be named settings but too verbose