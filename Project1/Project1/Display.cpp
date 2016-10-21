#include "Display.h"




Display::Display(char * title, RenderContext &displayImage) : windowTitle(title)
{
	/*if (!initialize()) {
	cout << "nie ma okna :<";
	//return -1;
	}*/
	SCR_W = displayImage.getWidth();
	SCR_H = displayImage.getHeight();



	bool exit = false;

	SDL_Event e;
	//Uint32 bgColor = SDL_MapRGB(screen->format, 20, 50, 20);
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCR_W, SCR_H, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture * texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCR_W, SCR_H);
	//Uint32 * pixels = new Uint32[SCR_W * SCR_H];

	//    memset(displayImage.m_components, 255, SCR_W * SCR_H * sizeof(Uint32));

	unsigned int ax = 0, ay = 20;

	//displayImage = &renderContext;//new RenderContext(SCR_W, SCR_H);
	//displayImage->Clear(0x0a320aff);
	//displayImage.Clear(0x00);

	Stars3D starfield(3000, 64.0f, 20.0f);
	//Triangles starfield(6, 64.0f, 20.0f);

	previousTime = getTime;
	while (!exit)
	{
		SDL_UpdateTexture(texture, NULL, displayImage.getComponents(), SCR_W* sizeof(unsigned int));

		//	cout << delta << endl;
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				exit = true;

			if (e.key.keysym.sym == SDLK_d)
			{
				displayImage.Clear(0xcc0000);
				//Bitmap::SaveTGA(bmap, "tst2.tga")
			}
			else if (e.key.keysym.sym == SDLK_p)
			{
				//displayImage->Clear(0xff00ff00);
				//Bitmap::SaveTGA(bmap, "tst2.tga")
				displayImage.SaveAsTGA("tst4.tga");
			}
			else if (e.key.keysym.sym == SDLK_q)
			{
				if (FOV < 179) FOV += 0.5f;

				cout << "FOV: \t\t" << FOV << endl;
			}
			else if (e.key.keysym.sym == SDLK_w)
			{
				if (FOV > 1) FOV -= 0.5f;

				cout << "FOV: \t\t" << FOV << endl;

			}
		}


		//displayImage->Clear(0xff00ff00);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		currentTime = getTime;
		float delta = getDelay() / 1000000000.0f; // czy musze podstawiac? 

		//starfield.updateAndRender(displayImage, delta, FOV);
		previousTime = currentTime;
//		displayImage->Clear(0x00ff0000);

		/*------------------ fill shape
		for (int j = 0; j < 100; j++)
		{
			displayImage->DrawScanBuffer(j, 100 - j, 100 + j);
		}

		displayImage->fillShape(0, 100);
		*/


		float2 a = float2(400, 100), b = float2(100, 200), c = float2(80, 300);
		
		//displayImage->FillTriangle(a, c, b);



/*
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)

				displayImage->DrawPixel(j, i, 0xff000000);

		}

		
		

		SDL_UpdateWindowSurface(window);
		*/

		//drawBitmap(displayImage);
	}


	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}


void Display::putpixels(int x, int y, unsigned int color)
{
	unsigned int *ptr = (unsigned int*)screen->pixels;

	int lineoffset = y * (screen->pitch / 4);
	ptr[lineoffset + x] = color;

}

void Display::close()
{
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

bool Display::initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "jeblo sie\n";
		return false;
	}

	//windowTitle = "ssd";
	window = SDL_CreateWindow(windowTitle,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCR_W, SCR_H, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		cout << "okienko sie zjebalo";
		return false;

	}
	screen = SDL_GetWindowSurface(window);
	return true;
}


void Display::drawBitmap(RenderContext& bitmap)
{

	for (int x = 0; x < bitmap.getWidth(); x++) {
		for (int y = 0; y < bitmap.getHeight(); y++)
		{
			putpixels(x, bitmap.getHeight() - 1 - y, (bitmap.getComponents()[x + y*bitmap.getWidth()] >> 8));
		}
	}
}

Display::~Display()
{
	//delete displayImage;
}

