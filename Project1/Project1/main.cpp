#include <iostream>
#include <SDL.h>
#include <conio.h>
#include <stdio.h>
#include "structures.h"
#include "Display.h"
#include "Color.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "CameraPerspective.h"
#include "CameraOrtho.h"
//#include "Image.h"



using namespace std;



void zadanie1() {
	// ------- ZADANIE 1 -----------
	cout << "-------------------------- ZADANIE 1 -------------------------\n";

	Sphere S(float3(0, 0, 0), 10);

	Plane p(float3(.5f, .5f, .707f), 0);
	Plane p1(float3(0, 0, 1), 5);
	
	Ray R1(float3(0, 0, -20), float3(0, 0, 1));
	Ray R2(float3(0, 0, -20), float3(0, 1, 0)); // RAY(zrodlo,kierunek)
	Ray R3(float3(0, 10, -20), float3(0, 0, 1));

	Sphere S2(float3(-10, 0, 10), 10);
	Ray R4(float3(0, 0, 0), float3(0,0,-1));

	float f = R4.intersect(S2, 50);
}

void raytrace(RenderContext &bitmap)
{


	float *zBuffer = new float[bitmap.getWidth() * bitmap.getHeight()];
	fill(zBuffer, zBuffer + (bitmap.getWidth() * bitmap.getHeight()), INFINITY);

	//cout << zBuffer[34];


	float pw = 2.0f / bitmap.getWidth(),
		ph = 2.0f / bitmap.getHeight();
	float pxc, pyc;
	Sphere S(float3(0, 00, 1), .85f);
	Sphere S2(float3(0, 0.4, .7f), .5f);
	float dist = float3::distance(S.getCenter(), float3(0, 0, 0)) + S.getRadius();


	//*	pxc = -1.0f + ()
	for (int x = 0; x < bitmap.getWidth(); x++)

	{
		for (int y = 0; y < bitmap.getHeight(); y++)
		{

			pxc = -1.0f + (x + 0.5f) * pw;
			pyc = 1.0f - (y + 0.5f) * ph;

			float3 pxRay(pxc, pyc, 0);
			//Ray r(float3(0, 0, 10.000000476838), pxRay);
			//Ray r(float3(0, 0, 1), pxRay);
			Ray r(pxRay, float3(0, 0, 1));



			float isect = r.intersect(S, 50);
			
			//if (isect == -1) continue; //.DrawPixel(x, y, 0x00);
			//if (isect != -1 M//
			if (isect != -1 && isect < zBuffer[x + y *bitmap.getWidth()])
			{	
				zBuffer[x + y *bitmap.getWidth()] = isect;
				float3 p2(r.getOrigin() + r.getDirection() * isect);
				float d2 = float3::distance(r.getOrigin(), p2) - dist;
				float pr = d2 / S.getRadius();
				Color tmpCol(1.0f - 1.0f * pr, 1.0f - 1.0f * pr, 1.0f - 1.0f * pr);
				//Color tmpCol(0.0f,0.3f,1.0f);
				bitmap.DrawPixel(x, y, tmpCol.toHex());
			}
		}

	}


	for (int x = 0; x < bitmap.getWidth(); x++)

	{
		for (int y = 0; y < bitmap.getHeight(); y++)
		{

			pxc = -1.0f + (x + 0.5f) * pw;
			pyc = 1.0f - (y + 0.5f) * ph;

			float3 pxRay(pxc, pyc, 0);
			//Ray r(float3(0, 0, 10.000000476838), pxRay);
			//Ray r(float3(0, 0, 1), pxRay);
			Ray r(pxRay, float3(0, 0, 1));



			float isect = r.intersect(S2, 50);
			if (isect != -1 && isect < zBuffer[x + y *bitmap.getWidth()])
			{
				zBuffer[x + y *bitmap.getWidth()] = isect;
				float3 p2(r.getOrigin() + r.getDirection() * isect);
				float d2 = float3::distance(r.getOrigin(), p2) - dist;
				float pr = d2 / S.getRadius();
				Color tmpCol(1.0f - 1.0f * pr, 1.0f - 1.0f * pr, 1.0f - 1.0f * pr);
				//Color tmpCol(0.5f, 1.0f, 0.0f);
				bitmap.DrawPixel(x, y, tmpCol.toHex());
			}
		}

	}
	//*/
}



/*TODO klasa abstrakcyjna dla obiektu (material / kolor, intersect)
*/


//Material
Color c1(255,200,15),
c2(255, 127, 40),
c3(255, 0, 0);

int main(int argc, char * argv[])
{
	int w = 600, h = 400;

	RenderContext bitmap(w, h);
	//raytrace(bitmap);
	Sphere S2(float3(0, 0, 0.0f), .15f);
	Sphere S(float3(0.3f, 0.0, 8.f), .15f);

	Sphere scene[3] = {
		Sphere(float3(0, 0, 0.0f), 0.4f),
		Sphere(float3(1.6f, 0.0f, 0.2f), 0.4f),
		Sphere(float3(-1.6f, 0.0, 0.1f), 0.4f)

	};

	scene[2].setColor(c3);
	scene[1].setColor(c1);
	scene[0].setColor(c2);

	CameraPerspective cam	(float3 (0.0f, 0.0f, -2), float3(0,0,0), float3 (0,1,0), 60.f);
//	CameraOrtho cam(float3(0.0f, 0.0f, -3.0f), float3(0, 0, 0), float3(0, 1, 0));
	//cam.LookAt(float3(0, 0, 0));
	//cam.RenderImage(bitmap, scene);

//
//	auto start = get_time::now();
	/*cout << a << endl;
	cout << a.length() << endl;
	cout << d << endl;
	cout << d.length() << endl;*/
	//cout << float3::dot(b, b) << endl;
	//cout << float3::dot(c, c) << endl;
	//auto end = get_time::now();
	//auto diff = end - start;
//	cout << "Elapsed time is :  " << chrono::duration_cast<ns>(diff).count() << " ns " << endl;


	//Color ca(1,0.5,1);

	//cout << black.isBlack() << endl;
	//cout << hex << ca.toHex() << endl;
	



	//zadanie1();
	//bitmap.Clear(0x0000cd00);



	Display display("okno_1", bitmap );

	//_getch();
	return 0;
}
