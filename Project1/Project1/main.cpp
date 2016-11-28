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
//#include "Brofiler.h"
#include "Light.h"
#include "PointLight.h"


using namespace std;

//Material


int main(int argc, char * argv[])
{

	auto start = get_time::now();
	int w = 600, h = 400;

	RenderContext bitmap(w, h);

	//swiatla siatki
	vector <Mesh> meshes;

	//swiatla
	vector <Light*> lights;
	//lights.push_back(new Light(float3(0.f, 2.f, -1.f), Color::WHITE));
	
	//kamera
	Camera cam(float3(0.0f, 2.f, -2.f), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective
//	Camera cam(float3(0.0f, 2.f, -2.f), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective
	
	//scena
	vector <Primitive*> sc;
	//sc.push_back(new Sphere(float3(0.f, 0.f, 0.0f), 0.5f, Material::ORANGE));


	//Mesh::importOBJ("obj/s2.obj", meshes);

	//for (int i = 0; i < meshes.size(); i++)


	lights.push_back(new PointLight(float3(-2.f, 1.5f, 0.3f), Color::RED, 0.02f, 0.05f, 0.05f));
	lights.push_back(new PointLight(float3(0.f, 1.5f, 0.3f), Color::GREEN, 0.02f, 0.05f, 0.05f));
	lights.push_back(new PointLight(float3(2.f, 1.5f, 0.3f), Color::BLUE, 0.02f, 0.05f, 0.05f));

	sc.push_back(new Sphere(float3(-0.6f, 0.4f, 0.f), 0.3f, Material::GREEN));
	sc.push_back(new Sphere(float3(0.f, 0.4f, 0.f), 0.3f, Material::DBLUE_D));
	sc.push_back(new Sphere(float3(0.6f, 0.4f, 0.f), 0.3f, Material::RED_D));
	//sc.push_back(new Mesh("obj/st.obj", Material::GRAY));
	sc.push_back(new Mesh("obj/p2.obj", Material::WHITE_S));


	/*
	lights.push_back(new PointLight(float3(-4.f, 2.5f, 1.f), Color::WHITE, 0.02f, 0.05f, 0.05f));
	sc.push_back(new Sphere(float3(-0.5f, 0.0f, 0.5f), 0.3f, Material::ORANGE));
	sc.push_back(new Mesh("obj/st.obj", Material::RED_D));
	sc.push_back(new Mesh("obj/p2.obj", Material::GRAY));
	*/

	/*/ ATTENUATION TEST
	lights.push_back(new PointLight(float3(0.f, 1.5f, 0.f), Color::WHITE));
	sc.push_back(new Sphere(float3(3.f, 0.f, 0.75f), 0.5f, Material::RED_D));
	sc.push_back(new Sphere(float3(3.f, 0.f, -0.75f), 0.5f, Material::DBLUE_D));
	sc.push_back(new Sphere(float3(4.f, -1.f, 0.f), 0.5f, Material::RED_D));
	sc.push_back(new Sphere(float3(7.f, 1.f, 0.f), 0.5f, Material::RED_D));
	Camera cam(float3(.0f, 0.1f, .0f), float3(1, 0, 0), float3(0, 1, 0), 40.f);
	*/

	//cout << " models: " << sc.size() << endl;

	//while (true)
	{
//		BROFILER_FRAME("rendering")
			cout << "start.." << endl;

		cam.RenderImage(bitmap, sc, lights);
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
