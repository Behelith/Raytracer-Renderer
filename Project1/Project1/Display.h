#pragma once
#include "RenderContext.h"
#include <SDL.h>
#include "structures.h"
#include "Stars3D.h"


class Display
{
private:
	//RenderContext* displayImage;
	int SCR_W;// = 720;
	int SCR_H;// = 480;
	const char * windowTitle;
	//void drawBitmap(Bitmap& bitmap);
	void drawBitmap(RenderContext& bitmap);


	/*
	time_t lastTime,
	currentTime;
	long currentTime = 0;
	*/

	SDL_Window* window = NULL;
	SDL_Surface* screen = NULL;

public:
	~Display();

	bool initialize();
	void close();
	//void updateView


	Display( char * title, RenderContext &renderContext);

	void putpixels(int x, int y, unsigned int color);

};
