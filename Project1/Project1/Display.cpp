#include "Display.h"




Display::Display(char * title, RenderContext &displayImage) : windowTitle(title)
{
	SCR_W = displayImage.getWidth();
	SCR_H = displayImage.getHeight();



	bool exit = false;

	SDL_Event e;
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCR_W, SCR_H, 0);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_Texture * texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCR_W, SCR_H);

	unsigned int ax = 0, ay = 20;

	//Stars3D starfield(3, 64.0f, 20.0f,1);
	Stars3D starfield(3000, 64.0f, 20.0f);

	//verts
	//float2  a = float2(400, 100), 
	//		b = float2(100, 200), 
	//		c = float2(80, 300);

	vertex a = vertex(100, 100),
		b = vertex(150, 200),
		c = vertex(80, 300);

	//vertex a = vertex(-1, -1),
	//	b = vertex(0, 1),
	//	c = vertex(1, -1);

	Matrix4 projection = Matrix4().InitPerspective((70.0f*PI180), displayImage.getWidth() / displayImage.getHeight(), 0.1f, 1000.0f);
	
	float rotCounter = 0.0f;
		
	previousTime = getTime;
	while (!exit)
	{
		SDL_UpdateTexture(texture, NULL, displayImage.getComponents(), SCR_W * sizeof(unsigned int));

		//	cout << delta << endl;
		while (SDL_PollEvent(&e) != 0)
		{

			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			if (e.key.keysym.sym == SDLK_d)
			{
				FreeImage_Initialise();
				//int tw = w, th = h;
				FIBITMAP *bm = FreeImage_Allocate(displayImage.getWidth(), displayImage.getHeight(), 24, 0xff0000, 0x00ff00, 0x0000ff);
				RGBQUAD color;

				for (int j = 0; j < displayImage.getHeight(); j++)
				{
					for (int i = 0; i < displayImage.getWidth(); i++)
					{
						unsigned int tmpColor = displayImage.getColorAt(i, displayImage.getHeight() - j);
						color.rgbRed = (double)Color::rToInt(tmpColor);
						color.rgbGreen = (double)Color::gToInt(tmpColor);
						color.rgbBlue = (double)Color::bToInt(tmpColor);
						//color.rgbRed = 0.0;
						//color.rgbGreen = 0.0;
						//color.rgbBlue = 255.0;

						FreeImage_SetPixelColor(bm, i, j, &color);
					}
				}
				if (FreeImage_Save(FIF_PNG, bm, "render1.png", 0)) { cout << " bitmap successfully saved! " << endl; }


				FreeImage_DeInitialise();
				//FreeImage_Save()
			}

			else if (e.key.keysym.sym == SDLK_p)
			{



				//displayImage.SaveAsTGA("tst4.tga");
			}
			else if (e.key.keysym.sym == SDLK_q)
			{
				if (FOV < 175) FOV += 5.0f;
				cout << "FOV: \t\t" << FOV << endl;
			}
			else if (e.key.keysym.sym == SDLK_w)
			{
				if (FOV > 1) FOV -= 5.0f;
				cout << "FOV: \t\t" << FOV << endl;
			}
		}


		//displayImage->Clear(0xff00ff00);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		currentTime = getTime;
		float delta = getDelay() / 1000000000.0f; // czy musze podstawiac? 
		previousTime = currentTime;
		//starfield.updateAndRender(displayImage, delta, FOV);
		/*rotCounter += delta;
		//*
		Matrix4 translation = Matrix4().InitTranslation(0.0f, 0.0f, 3.0f);

		Matrix4 rotation = Matrix4().InitRotation(0.0f, rotCounter, 0.0f);
		Matrix4 transform = projection.mul(translation.mul(rotation));
		
		//*/
		
		//transform.showMatrix();

		//displayImage.Clear(0x00000000);

		//for ( int j = 100; j < 200; j++)
		//{
		//	displayImage.DrawScanBuffer(j, 300 - j, 300 + j);
		//}

		//displayImage.ScanConvertTriangle(a, b, c, 0);
		//displayImage.FillShape(100,300);

		//displayImage.FillTriangle(a, b, c);

		//displayImage.FillTriangle(a.Transform(transform),b.Transform(transform), c.Transform(transform));
		//projection.showMatrix();

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

