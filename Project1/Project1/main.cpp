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
#include "FreeImage.h"
#include "Texture.h"


using namespace std;

//Material


int main(int argc, char * argv[])
{

	auto start = get_time::now();
	int w =
		400, h = 400;
	int isRendering = 0;
	//RenderContext bitmap(w, h);

	//siatki
	vector <Mesh> meshes;
	//swiatla
	vector <Light*> lights;
	//scena
	vector <Primitive*> sc;
	//lights.push_back(new Light(float3(0.f, 2.f, -1.f), Color::WHITE));

	//kamera
	//Camera cam(float3(0.0f, 2.f, -2.f), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective
//	Camera cam(float3(0.0f, 2.f, -2.f), float3(0, 0, 0), float3(0, 1, 0), 60.f); //perspective


	//sc.push_back(new Sphere(float3(0.f, 0.f, 0.0f), 0.5f, Material::ORANGE));


	//Mesh::importOBJ("obj/s2.obj", meshes);

	//for (int i = 0; i < meshes.size(); i++)


	/* CORNELL BOX */
	Camera cam(float3(0.0f, 2.5f, -3.5f), float3(0, .7f, 0), float3(0, 1, 0), 40.f); //perspective

	//sc.push_back(new Sphere(float3(-0.2f, 0.375f, 0.1f), 0.45f, Material::MIRROR));
	//sc.push_back(new Sphere(float3(0.3f, 0.237f, -0.45f), 0.3f, Material::GLASS));
	sc.push_back(new Mesh("obj/p2.obj", Material::GREEN));
	sc.push_back(new Mesh("obj/c1.obj", Material::RED_D));
	sc.push_back(new Mesh("obj/c2.obj", Material::WHITE_S));
	sc.push_back(new Mesh("obj/c3.obj", Material::DBLUE_D));

	lights.push_back(new PointLight(float3(0.0f, 2.5f, 0.05f), Color::GRAY, 0.05f, 0.05f, 0.05f));

	isRendering = 1;


	if (isRendering == 0)
	{
	
		Ray r(float3(0, 0, 2),float3(0, 0, 1) );
		HitInfo hi = sc[0]->Intersect(r, 10);
		float3 N(0, 1, 0);



	float3 v1(-1.f, 0.f, 1.f);
		v1.unitise();
	//for (float i = 1; i > -1.0; i -= 0.1f)
		{
			float3 v2(-0.9f, 0.f, 1.f);
			v2.unitise();
			//float cosI = float3::dot(hi.getNormal(), r.getDirection());
			//float cosI = float3::dot(r.getDirection(), hi.getNormal());
			//cout << "\t\thi: normal \t" << hi.getNormal() << endl;

			cout << "\t\thi: cos v1v2\t" << float3::dot(v1, v2) << endl;
			v2 = -v2;
			cout << "\t\thi: cos v1v2\t" << float3::dot(v1, v2) << endl;
		}
	}
	//*/


	//cout << " models: " << sc.size() << endl;
	Texture t("az.png");
	Texture t2("za.png");

	//Material::GRAY.setTexture(t);
	Material::GREEN.setTexture(t2);
	RenderContext bitmap(t2.getWidth(), t2.getHeight());
	//bitmap.draw(Material::GRAY.getTexture());
	//while (true)
	if (isRendering == 1)
	{
		//		BROFILER_FRAME("rendering")
		cout << "start" << endl;
		cam.RenderImage(bitmap, sc, lights);
		cout << "done " << endl;

	}
	auto end = get_time::now();
	auto diff = end - start;
	cout << "Elapsed time is :  " << chrono::duration_cast<std::chrono::milliseconds>(diff).count() << " ns " << endl;

	if (isRendering == 1)
		Display display("okno_1", bitmap);

	if (isRendering == 0)
		_getch();

	for (auto &p : sc)
		delete p;

	return 0;
}
