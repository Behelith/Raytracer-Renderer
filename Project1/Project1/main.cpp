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
#include "Triangle.h"
#include "Mesh.h"


using namespace std;

//Material
Color
c1(255, 200, 15),
c2(255, 127, 40),
c3(1.f, 0.f, 0.f),
c4(.0f, 1.0f, 0.f),
c5(.0f, 0.0f, 1.f),
c6(1.0f, 0.0f, 1.f);

int main(int argc, char * argv[])
{
	auto start = get_time::now();
	int w = 500, h = 350;

	RenderContext bitmap(w, h);

	vector <Primitive*> sc;
//	sc.push_back(new Sphere(float3(0, 0, 0.4f), 0.4f, c1));

	//sc.push_back(new Sphere(float3(-.2f, 0.0, 0.0f), 0.4f, c2));
	//sc.push_back(new Sphere(float3(.6f, 0.0f, 0.0f), 0.4f, c3));

	//
	//sc.push_back(new Sphere(float3(0.1f, 0, 0.8f), 0.3f, c4));
	//sc.push_back(new Sphere(float3(0.3f, 0, 0.4f), 0.3f, c5));

	// wrazliwe na kolejnosc wertexow;
	float3
		v1(-0.500000, -0.200000, 0.500000),
		v2(0.000000, 0.800000, 0.000000),
		v3(-0.500000, -0.200000, -0.500000),
		v4(0.500000, -0.200000, 0.500000),
		v5(0.500000, -0.200000, -0.500000);
	 /*
	float3
		v1(-.5, -.2, -.5),
		v2(0, -.8, .0),
		v3(-.5, -.2, -.5),
		v4(0, .5, 0),
		v5(0, .5, 0);
*/

	Triangle
		t1(&v2, &v3, &v1, c1),
		t2(&v2, &v5, &v3, c2),
		t3(&v2, &v4, &v5, c3),
		t4(&v2, &v1, &v4, c4),
		t5(&v3, &v4, &v1, c5),
		t6(&v3, &v5, &v4, c6),

		dt(&v3, &v5, &v4, Color(255, 0, 0))
		;


	Mesh m (1);
	m.setColor(c2);
	m.importOBJ("obj/s3.obj");

	sc.push_back(&m);


	//cout <<hex << dt.getColor().toHex() << endl;

	//Ray r(float3 (0,0,-2), float3 (0,0,1) );

	//sc.push_back(&t1);
	//sc.push_back(&t2);
	//sc.push_back(&t3);
	//sc.push_back(&t4);
	//sc.push_back(&t5);
	//sc.push_back(&t6);
//	sc.push_back(&t2);
	//float i = t.Intersect(r, 50);
	//cout << i << endl;


	Camera cam(float3(-2.0f, -.8f, -2), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective
	//Camera cam	(float3 (0.0f, 0.0f, -2), float3(0,0,0), float3 (0,1,0)); // ortho
	cam.RenderImage(bitmap, sc);

	auto end = get_time::now();
	auto diff = end - start;
	//cout << "Elapsed time is :  " << chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ns " << endl;

	Display display("okno_1", bitmap);

	_getch();
	return 0;
}
