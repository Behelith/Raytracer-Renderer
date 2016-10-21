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



	/*
	float
		i1 = R1.intersect(S, 50),
		i2 = R2.intersect(S, 50),
		i3 = R3.intersect(S, 50),
		i4 = R2.intersect(p, 50);
		;
	

	/*
	if (i1 == -1)
	else
	{
		float3 ip = R1.getOrigin() + R1.getDirection()*R1.intersect(S, 50);
		cout << "przeciecie w punkcie: " << ip << endl;
	}

	*/
	//*

//	p.intersect(R2, 300);

	//S.intersect(R1, 50);
	/*
	//definicje
//	Sphere S(float3(0, 0, 0), 10);
	cout << "Sfera S o srodku w punkcie (" << S.getCenter() << ") oraz promieniu = " << S.getRadius();
	//Ray R1(float3(0, 0, -20), float3(0, 0, 1));
//	cout << "\n\nPromien R1 o zrodle (" << R1.getOrigin() << ") oraz kierunku (" << R1.getDirection() << ")";
	S.intersect(R1, 50);
	//Ray R2(float3(0, 0, -20), float3(0, 1, 0)); // RAY(zrodlo,kierunek)
	//cout << "\n\nPromien R2 o zrodle (" << R2.getOrigin() << ") oraz kierunku (" << R2.getDirection() << ")";
	S.intersect(R2, 50);
//	cout << "\n\nPromien R3 o zrodle (" << R3.getOrigin() << ") oraz kierunku (" << R3.getDirection() << ")";
	S.intersect(R3, 50);
	//*/



}



//Material

int main(int argc, char * argv[])
{

	//----------------
	float3 p = float3(1, 2, 3);


	float3 a(3, 1, 1);
	float3 b(2, 2, 2);
	float3 d(3, 1, 1, 1);
	//float3 c = a;float3::cross(a, b);

	a.unitise();


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
	int w = 600, h = 600;

	RenderContext bitmap(w, h);

	//Color ca(1,0.5,1);

	//cout << black.isBlack() << endl;
	//cout << hex << ca.toHex() << endl;
	
	float pw = 2.0f / w,
		ph = 2.0f / h;
		float pxc, pyc;
	Sphere S(float3(0, 00, 1), .85f);
	float dist = float3::distance(S.getCenter(), float3(0,0,0)) + S.getRadius();
	

//*	pxc = -1.0f + ()
	for (int x = 0; x < w; x++)

		{
			for (int y = 0; y < h; y++)
			{

				pxc = -1.0f + (x + 0.5f) * pw;
				pyc = 1.0f - (y + 0.5f) * ph;

				float3 pxRay(pxc, pyc, 0);
				//Ray r(float3(0, 0, 10.000000476838), pxRay);
				//Ray r(float3(0, 0, 1), pxRay);
				Ray r(pxRay, float3(0,0, 1));

				

				float isect = r.intersect(S, 50);
				if (isect == -1) bitmap.DrawPixel(x, y, 0x00);
				
				else
				{
					float3 p2(r.getOrigin() + r.getDirection() * isect);
					float d2 = float3::distance(r.getOrigin(), p2) - dist;
					float pr = d2 / S.getRadius();
					Color tmpCol(1.0f - 1.0f * pr, 1.0f - 1.0f * pr, 1.0f - 1.0f * pr);
					bitmap.DrawPixel(x, y, tmpCol.toHex());
				}
			}

		}
//*/



	//zadanie1();
	//bitmap.Clear(0x0000cd00);



	Display display("okno_1", bitmap );

	_getch();
	return 0;
}
