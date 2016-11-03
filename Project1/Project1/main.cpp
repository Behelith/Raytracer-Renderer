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
#include "Camera.h"

using namespace std;


/*TODO klasa abstrakcyjna dla obiektu (material / kolor, intersect)
*/


//Material
Color c1(255, 200, 15),
c2(255, 127, 40),
c3(1.f, 0.f, 0.f),
c4(.0f, 1.0f, 0.f),
c5(.0f, 0.0f, 1.f);

int main(int argc, char * argv[])
{	
	auto start = get_time::now();
	int w = 500, h = 350;

	RenderContext bitmap(w, h);

	Sphere S2(float3(0, 0, 0.0f), .15f);
	Sphere S(float3(0.3f, 0.0, 8.f), .15f);

	Sphere scene[3] = {
		Sphere(float3(0, 0, 0.4f), 0.4f),
		Sphere(float3(-.2f, 0.0, 0.0f), 0.4f),
		Sphere(float3(.6f, 0.0f, 0.0f), 0.4f)

	};

	scene[2].setColor(c3);
	scene[1].setColor(c4);
	scene[0].setColor(c5);


	Camera cam(float3(0.0f, 0.0f, -2), float3(0, 0, 0), float3(0, 1, 0), 60.f);
	//Camera cam	(float3 (0.0f, 0.0f, -2), float3(0,0,0), float3 (0,1,0));
	cam.RenderImage(bitmap, scene);
	
	auto end = get_time::now();
	auto diff = end - start;
	cout << "Elapsed time is :  " << chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ns " << endl;

	Display display("okno_1", bitmap );

	//_getch();
	return 0;
}
