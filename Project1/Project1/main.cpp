#include <iostream>
#include <SDL.h>
#include <conio.h>
#include <stdio.h>
#include "structures.h"
#include "Display.h"
#include "Color.h"
#include "Sphere.h"
#include "Camera.h"
#include "vector"


using namespace std;

//Material
Color
c1(255, 200, 15),
c2(255, 127, 40),
c3(1.f, 0.f, 0.f),
c4(.0f, 1.0f, 0.f),
c5(.0f, 0.0f, 1.f);

int main(int argc, char * argv[])
{
	auto start = get_time::now();
	int w = 500, h = 350;

	RenderContext bitmap(w, h);

	vector <Primitive*> sc;
	sc.push_back(new Sphere(float3(0, 0, 0.4f), 0.4f, c1));

	sc.push_back(new Sphere(float3(-.2f, 0.0, 0.0f), 0.4f, c2));
	sc.push_back(new Sphere(float3(.6f, 0.0f, 0.0f), 0.4f, c3));

	//
	//sc.push_back(new Sphere(float3(0.1f, 0, 0.8f), 0.3f, c4));
	//sc.push_back(new Sphere(float3(0.3f, 0, 0.4f), 0.3f, c5));




	Camera cam(float3(0.0f, 0.0f, -2), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective
	//Camera cam	(float3 (0.0f, 0.0f, -2), float3(0,0,0), float3 (0,1,0)); // ortho
	cam.RenderImage(bitmap, sc);

	auto end = get_time::now();
	auto diff = end - start;
	cout << "Elapsed time is :  " << chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ns " << endl;

	Display display("okno_1", bitmap);

	//_getch();
	return 0;
}
