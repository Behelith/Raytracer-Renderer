#include "Camera.h"
#include "Sphere.h"
//#include <Brofiler.h>
//#include "Light.h"

Camera::Camera()
{
	m_target = float3(0, 0, 0);
	m_up = float3(0, 1, 0);
	m_fov = 60.f;
	isOrthogonal = false;


	m_location = float3(0, 0, 0);

	//direction - gdzie patrzy kamea
	m_w = m_location - m_target;

	m_w.unitise();

	m_u = float3::cross(m_up, m_w); // right vector
									//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 1;
	m_u = -m_u;
}

Camera::Camera(float3 location, float3 direction, float3 up, float fov)
{
	m_target = direction; m_up = up;
	m_fov = fov;
	isOrthogonal = false;

	m_location = location;

	//direction - gdzie patrzy kamea
	m_w = m_location - m_target;
	m_w.unitise();

	//m_u = float3::cross(m_w,-m_up); // right vector
	m_u = float3::cross(m_up, m_w); // right vector

	//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 1;

	m_u = -m_u;
}

Camera::Camera(float3 location, float3 direction, float3 up)
{
	m_target = direction; m_up = up;
	isOrthogonal = true;

	m_location = -location;

	//direction - gdzie patrzy kamea
	m_w = m_location - m_target;
	m_w.unitise();

	m_u = float3::cross(m_up, m_w); // right vector
									//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 1;
	//m_u = m_u;
}

Camera::~Camera()
{
}

void Camera::LookAt(float3 target)
{
	m_target = target;
	m_direction = m_location - m_target;

	m_w = m_direction;// prosto
	m_w.unitise();

	m_u = float3::cross(m_up, m_w); // right vector
									//m_u = float3::cross(m_w, m_up); // right vector
	m_v = float3::cross(m_w, m_u); //

	m_distance = 1;
	m_u = -m_u;

}

Color Camera::Sampling(float2 sCenter, float2 dimensions, vector<Primitive*> &objects, vector<Light*> &lights, float &zDepth, int level)
{
	//BROFILER_CATEGORY("sampling", Profiler::Color::Yellow)

		//	Light light(float3(1, 2, 0), Color::YELLOW);

		//	cout << level << endl;
	Color suma(0.0f, 0.0f, 0.0f);

	float zVerts[4] = { 0.f,0.f,0.f,0.f };
	float zSuma = 0.f;
	float hits = 0;

	//tablica z wierzcholkami piksela (lg,pg,pd,ld)
	float2 verts[4] = {
		float2(sCenter.GetX() - dimensions.GetX(), sCenter.GetY() - dimensions.GetY()),
		float2(sCenter.GetX() + dimensions.GetX(), sCenter.GetY() - dimensions.GetY()),
		float2(sCenter.GetX() + dimensions.GetX(), sCenter.GetY() + dimensions.GetY()),
		float2(sCenter.GetX() - dimensions.GetX(), sCenter.GetY() + dimensions.GetY())
	};

	// tablica na policzone kolory
	Color colors[4] = {
		Color(0,0,0),
		Color(0,0,0),
		Color(0,0,0),
		Color(0,0,0)
	};


	//dla kazdego wierzcholka policz i wyslij promien w scene (czyli minimum 4 promienie)
	for (int i = 0; i < 4; i++)
	{

		float3 pxRay = m_u * verts[i].GetX() + m_v * verts[i].GetY() + m_w * -m_distance;		//piksel w przestrzeni
		Ray r;// promien
		if (isOrthogonal) //orto
			r = Ray(pxRay, m_direction);
		else
		{
			pxRay.unitise();
			r = Ray(m_location, pxRay);
		}
		colors[i] = GetColor(r, 5, objects, lights, zDepth);
	}

	//czy kolory roznia sie od siebie (margines 0.01)
	bool colorDiff = true;
	for (int i = 1; i < 4; i++)
		if (!colors[i].IsSimilar(colors[i - 1], 0.00005f)) colorDiff = false;

	//maksymalny poziom rekurencji; jesli kolory sie nie roznia, albo osiagnieto max. rek. to zwroc usredniony kolor
	if (level >= 2 || colorDiff)
	{

		for (int i = 0; i < 4; i++)
		{
			suma += colors[i];

		}
		//	else zDepth = INFINITY;// 4.f;
		return suma / 4.0f;
	}
	// jesli kolory sie roznia:
	else
	{
		//tablica wierzcholkow przechowuje teraz srodki poszczegolnych fragmentow
		verts[0] = float2(sCenter.GetX() - dimensions.GetX() / 2, sCenter.GetY() - dimensions.GetY() / 2);
		verts[1] = float2(sCenter.GetX() + dimensions.GetX() / 2, sCenter.GetY() - dimensions.GetY() / 2);
		verts[2] = float2(sCenter.GetX() + dimensions.GetX() / 2, sCenter.GetY() + dimensions.GetY() / 2);
		verts[3] = float2(sCenter.GetX() - dimensions.GetX() / 2, sCenter.GetY() + dimensions.GetY() / 2);

		//ustal kolor kazdego fragmentu, (myyyk rekurencja xD)
		for (int i = 0; i < 4; i++)
		{
			colors[i] = Sampling(verts[i], dimensions * 0.5, objects, lights, zVerts[i], level + 1);
			suma += colors[i];
			zSuma += zVerts[i];
		}
		// zwroc usredniony kolor
		//if (zDepth == 0) cout << "\n fsfasf\n\n";
		return suma / 4.0f;

	}

}

Color Camera::GetColor(Ray ray, int lvl, vector<Primitive*>& objects, vector<Light*>& lights, float& zDepth)
{
	Color color = Color::BLACK;
	Color bg(0.0f, .0f, 0.0f);

	Color
		ia(0.1f, 0.05f, 0.0f),
		id(1.f, 1.f, 1.f),
		is(1.f, 1.f, 1.f)
		;


	Primitive *objectHit = NULL; //najblizszy obiekt
	HitInfo hit(float3(), float3(), Color::RED, INFINITY);// = objects[j]->Intersect(r, 50);//r.intersect(objects[j], 50);
	float lastDistance = INFINITY; //odleglosc do aktualnego, najblizszego

								   //Ray r(m_location, pxRay);
								   //	


	for (int j = 0; j < objects.size(); j++)
	{
		HitInfo	hi = objects[j]->Intersect(ray, 50);

		if (hi.getDistance() > 0 && hi.getDistance() < hit.getDistance())
		{
			lastDistance = hi.getDistance();
			objectHit = objects[j];
			hit = hi;
		}
	}

	//jesli znalazl cokolwiek to pobierz kolor obiektu
	if (hit.getDistance() < INFINITY && objectHit != nullptr)
	{
		//	Color pc = Color::BLACK;
		Color ambient = ia*objectHit->getMaterial().getA();	// ambient do phonga
		float brightness = 0;

		color += ambient;

		Color diffuseSum = Color::BLACK;
		Color specularSum = Color::BLACK;
		Color reflectedColor = Color::BLACK;
		Color transmittedColor = Color::BLACK;

		float isReflective = 0;
		float isTransmissive = 0;

		// jesli diffuse
		//swiatla~!!

		//* skladowa diffuse i specular << do rozdzielenia
		//if (objectHit->getMaterial().getD() > 0.0f)
		{
			for (int k = 0; k < lights.size(); k++) {
				Color diffuse = Color::BLACK;
				Color specular = Color::BLACK;

				if (lights[k]->getLightType() == 1) {																// uwaga, wartosci wpisane na sztywno!
					float d = float3::distance(lights[k]->getPosition(), hit.getPoint());
					//brightness = 1 / (0.02f + 0.05f * d + 0.05f * d * d);
					brightness = 1 / (lights[k]->getConstA() + lights[k]->getLinearA() * d + lights[k]->getQuadA() * d * d);
					//brightness = 1;
				}

				else brightness = 1;


				//shadow ray
				HitInfo hl;
				float3 srd = lights[k]->getPosition() - hit.getPoint(); // czemu nie odwrotnie
				srd.unitise(); //shadow ray direction

				Ray sr(hit.getPoint(), srd);

				for (int j = 0; j < objects.size(); j++)
				{
					hl = objects[j]->Intersect(sr, 50);//r.intersect(objects[j], 50);
					if (hl.getDistance() > eps5) break;
					hl = HitInfo(float3(), float3(), Color::RED, -1);
					//float3 p;
				}
				float vi = (hl.getDistance() < 0) ? 1.f : 0.f; // visibilisit
															   //float visible = (hl.getDistance() <= 0) ? 1.f : 0.f;

															   //shadow ray



				float3 L = lights[k]->getPosition() - hit.getPoint();
				L.unitise();

				//float LdotN = float3::dot(L, hit.getNormal());
				float LdotN = float3::dot(hit.getNormal(), L);

				if (LdotN < 0) LdotN = 0.f;

				float3 H = L - ray.getDirection();
				H.unitise();

				//	float3 R = hit.getNormal() * (2.0* (float3::dot(L, hit.getNormal()))) - L;

				//	float nh = pow(float3::dot(hit.getNormal(), H), 64);
				float nh = pow(float3::dot(hit.getNormal(), H), objectHit->getMaterial().getC());		// dla wspolczynnika rozblysku, potega 2

				diffuse = id*objectHit->getColor(hit.getPoint())*LdotN*lights[k]->getColor()*vi;				// DIFFUSE
				specular = is*nh*lights[k]->getColor()*vi;
				diffuseSum += diffuse*brightness*vi;
				specularSum += specular*brightness*vi;

				//pc += ia +
				//	hit.getColor() *LdotN*vi +
				//	is*nh*vi;
				//pc.cut();

				//		pc = objectHit->getColor();

			}
			//	color += diffuseSum*objectHit->getMaterial().getD() + specularSum*objectHit->getMaterial().getS();
				//	color.cut();
		}//*/
		// lustrzany
		if (lvl > 0)
		{
			
			if (objectHit->getMaterial().getReflectivity() > 0.0)
			{
				isReflective = 1.f;
				float NdotI = float3::dot(ray.getDirection(), hit.getNormal()); // cos kata padajacego
				float3 R = ray.getDirection() - hit.getNormal() * 2 * NdotI;
				R.unitise();
				float3 offset = R*eps3;

				Ray// rayR(hit.getPoint(), R);
					rayR(hit.getPoint() + offset, R);

				reflectedColor += GetColor(rayR, lvl - 1, objects, lights, zDepth) * objectHit->getMaterial().getKRefl();
				reflectedColor.cut();
			}
			

			// refrakcyjny
			//else 
			if (objectHit->getMaterial().getRefraction() > 0.0)
			{
			//	cout << "refr";
				
			//	isTransmissive = 1.0f;
				float rIndex = objectHit->getMaterial().getRefraction();	//index refrakcji
				float n = REFRACTION_AIR / rIndex; // stosunek indeksow refrakcji roznych oœrodków/
				float NdotI = float3::dot(ray.getDirection(), hit.getNormal()); // cos kata padajacego
				
				float3 N = hit.getNormal();// *hit.getIsInside();
				if (NdotI > 0) {
					N = N* -1;
					NdotI = float3::dot(ray.getDirection(), hit.getNormal()); // cos kata padajacego
				//	cout << "rev. N" << endl;
				}

				float sin2t = (n*n) * (1.f - NdotI*NdotI);

				if (sin2t < 1.f)
				{
					float3 T = ray.getDirection()*n - N * (n + sqrtf(1.0f - sin2t));
					T.unitise();
					float3 offset = T*eps3;

					Ray rayT(hit.getPoint() + offset, T);
					Color absorbance = objectHit->getMaterial().getColor() * 0.15f * hit.getDistance();
					Color transparency = Color(expf(absorbance.getR()), expf(absorbance.getG()), expf(absorbance.getB()), 1.0f);

					transmittedColor += transparency* GetColor(rayT, lvl - 1, objects, lights, zDepth) *objectHit->getMaterial().getKRefr();
					transmittedColor.cut();

				//	diffuseSum = transmittedColor;

				}

				//float3 N = hit.getNormal() // *hit.getResult();
			//	N.unitise();

				//!!todo -- trzymac 2 ostatnie object hity, i pobierac z nich iRefrekcji, jesli drugi hit == null, wtedy iR = 1 (powietrze)
			}


		}
		//else
		//	reflectedColor += Color::BLACK;

		color
			+= reflectedColor * isReflective *  objectHit->getMaterial().getReflectivity()
			+ transmittedColor //* isTransmissive
			+ diffuseSum * objectHit->getMaterial().getD() //* (1.0 - isTransmissive)
			+ specularSum*objectHit->getMaterial().getS();

		color.cut();
	}
	else
	{
		color = bg;// *(1 - pr);

	}


	return color;
}

void Camera::RenderImage(RenderContext& bitmap, vector<Primitive*> &objects, vector<Light*> &lights)
{
	//BROFILER_CATEGORY("RenderImage", Profiler::Color::Orchid)


	float zMin = 100.f, zMax = 0.f;
	float zDepth = 0;

	float aspectRatio = float(bitmap.getWidth()) / float(bitmap.getHeight());
	float pi180 = 3.14159265359f / 180.0f;
	float tanHFOV;
	float2 pxDimensions(1.f / (float)bitmap.getWidth(), 1.f / (float)bitmap.getHeight());

	if (isOrthogonal)
	{
		//orto
		tanHFOV = 1.f;
	}
	else
	{
		//perspective
		//tangens (fov /2)
		tanHFOV = float(tan((m_fov * pi180) / 2.0f));
	}

	for (int x = 0; x < bitmap.getWidth(); x++)
	{
		for (int y = 0; y < bitmap.getHeight(); y++)
		{

			float2 pCenter(x, y);

			if (aspectRatio <= 1.f)
			{
				pCenter.SetX((2.f * (x + 0.5f) * pxDimensions.GetX() - 1.f) * tanHFOV);
				//pCenter.SetY((2.f * (y + 0.5f) * pxDimensions.GetY() - 1.f) / aspectRatio * tanHFOV);
				pCenter.SetY((1.f - 2.f * (y + 0.5f) * pxDimensions.GetY()) / aspectRatio * tanHFOV);

			}
			else
			{
				pCenter.SetX((2.f * (x + 0.5f) * pxDimensions.GetX() - 1.f) * tanHFOV * aspectRatio);
				pCenter.SetY((1.f - 2.f * (y + 0.5f) * pxDimensions.GetY()) *  tanHFOV);
			}

			//color z antialiasingiem
			unsigned int tmp = Sampling(pCenter, pxDimensions*0.5f, objects, lights, zDepth).toHex();

			if (zDepth > zMax) zMax = zDepth;
			if (zDepth < zMin && zDepth) zMin = zDepth;
			bitmap.DrawPixel(x, y, tmp);
			if (zDepth < INFINITY) bitmap.m_zbuffer[x + y *bitmap.getWidth()] = zDepth;




			/*
						float3 pxRay = m_u * pxc + m_v * pyc + m_w * -m_distance;

						pxRay.unitise();
						Ray r(m_location, pxRay);
						for (int i = 0; i < 3; i++) {

							float isect = r.intersect(objects[i], 50);


							if (isect != -1 && isect < zBuffer[x + y *bitmap.getWidth()])
							{
								zBuffer[x + y *bitmap.getWidth()] = isect;
								if (isect > zMax) zMax = isect;
								if (isect < zMin) zMin = isect;

								pr = 0;
								Color tmpCol = objects[i].getColor();// *(1 - pr);
								bitmap.DrawPixel(x, y, tmpCol.toHex());
							}
						}*/
		}
	}





	//cout << "zMin: " << zMin << "\tzMax: " << zMax << endl;







	/*
		float d = zMax - zMin;
		for (int i = 0; i < bitmap.getHeight() * bitmap.getWidth(); i++)
		{
			if (bitmap.m_zbuffer[i] < INFINITY)
			{
				float pr = (bitmap.m_zbuffer[i]-zMin )/ d;
				//Color col = Color(1.f, 1.f, 1.f) * (1 - pr);
				Color col =
					Color(bitmap.getComponents()[i])
				//	Color (255,255,255)
				* (1 - pr);

			 bitmap.getComponents()[i] = col.toHex();

			}
			else bitmap.getComponents()[i] = Color(0.0f, 0.f, 0.f).toHex();
		}
	//*/

}
