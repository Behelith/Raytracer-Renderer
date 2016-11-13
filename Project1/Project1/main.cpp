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
#include "Brofiler.h"


using namespace std;

//Material


int main(int argc, char * argv[])
{

	auto start = get_time::now();
	int w = 700, h = 700;

	RenderContext bitmap(w, h);
	vector <Mesh> meshes;

	vector <Primitive*> sc;


	sc.push_back(new Sphere(float3(4.2f, 0, 0.0f), 1.f, Material::RED_D));
	sc.push_back(new Sphere(float3(-4.2f, 0, 0.0f), 1.f, Material::DBLUE_D));

	//Mesh::importOBJ("obj/s2.obj", meshes);

	//for (int i = 0; i < meshes.size(); i++)
	//	sc.push_back(&meshes[i]);
//	sc.push_back(new Mesh("obj/s2.obj"));
	//sc.push_back(new Mesh("obj/d2.obj"));

	//cout << " models: " << sc.size() << endl;
	
	Camera cam(float3(0.0f, 0.f, -15.f), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective
	//Camera cam	(float3 (0.0f, 0.0f, -2), float3(0,0,0), float3 (0,1,0)); // ortho
	//while (true)
	{
		BROFILER_FRAME("rendering")
			cout << "start.." << endl;

		cam.RenderImage(bitmap, sc);
		cout << ".. done " << endl;

	}
	auto end = get_time::now();
	auto diff = end - start;
	cout << "Elapsed time is :  " << chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ns " << endl;

	Display display("okno_1", bitmap);

//	_getch();

	for (auto &p : sc)
		delete p;

	return 0;
}
