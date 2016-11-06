#include "Camera.h"
#include "Sphere.h"

Camera::Camera()
{
	m_target = float3(0,0,0); 
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

Color Camera::Sampling(float2 sCenter, float2 dimensions, vector<Primitive*> &objects, int level)
{
	//	cout << level << endl;
	Color bg(0.0f, .0f, 0.0f);
	Color suma(0.0f, 0.0f, 0.0f);

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
		Primitive *objectHit; //najblizszy obiekt
		float lastDistance = INFINITY; //odleglosc do aktualnego, najblizszego
		float3 pxRay = m_u * verts[i].GetX() + m_v * verts[i].GetY() + m_w * -m_distance;		//piksel w przestrzeni
		Ray r;// promien


		//Ray r(m_location, pxRay);
		//	
		if (isOrthogonal) //orto
		{
		//	m_direction = m_w;	//perspective
			r = Ray(pxRay, m_direction);
		}
		else
		{
			pxRay.unitise();
			 r = Ray(m_location, pxRay);

			/* TO JEST MAGIA xD... jak wysylam promien z piksela to wychodzi to wieeeeeeeeelkie; 
			m_direction = pxRay - m_location;
			m_direction = -m_direction;
			m_direction.unitise();
			*/
		}

		//ile obiektow w scenie... !!!!szukanie koloru: (( jak dzialal ten FOREACH !?))
		for (uint8_t j = 0; j < objects.size(); j++)
		{
			float isect = objects[j]->Intersect(r, 50);//r.intersect(objects[j], 50);

			if (isect != -1 && isect < lastDistance)
			{
				lastDistance = isect;
				//	cout << isect << endl;

				objectHit = objects[j];
				//cout << hex << objectHit->getColor().toHex()<<endl;
				//objectHit = new Sphere(float3(0, 0, 0.4f), 0.4f);
			}
		}
		//jesli znalazl cokolwiek to pobierz kolor obiektu
		if (lastDistance < INFINITY)	colors[i] += objectHit->getColor();// *(1 - pr);
		else colors[i] += bg;// *(1 - pr);
	}

	//czy kolory roznia sie od siebie (margines 0.01)
	bool colorDiff = true;
	for (int i = 1; i < 4; i++)
		if (!colors[i].IsSimilar(colors[i - 1], 0.00005f)) colorDiff = false;

	//maksymalny poziom rekurencji; jesli kolory sie nie roznia, albo osiagnieto max. rek. to zwroc usredniony kolor
	if (level >=2 || colorDiff)
	{
		for (int i = 0; i < 4; i++)
		{
			suma += colors[i];
		}
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
			colors[i] = Sampling(verts[i], dimensions * 0.5, objects, level + 1);
			suma += colors[i];

		}
		// zwroc usredniony kolor
		return suma / 4.0f;

	}

}


void Camera::RenderImage(RenderContext& bitmap, vector<Primitive*> &objects)
{
	//Ray r(float3(0, 0, 0), float3(0, 0, 1));
	//for (int i = 0; i < objects.size();i++)		cout << hex << objects[i]->Intersect(r, 40) << endl;


//	float *zBuffer = new float[bitmap.getWidth() * bitmap.getHeight()];
//	fill(zBuffer, zBuffer + (bitmap.getWidth() * bitmap.getHeight()), INFINITY);
	float zMin = INFINITY, zMax = 0.f;
	float aspectRatio = float(bitmap.getWidth()) / float(bitmap.getHeight());
	float pi180 = 3.14159265359f / 180.0f;
	float tanHFOV;
	float2 pxDimensions(1.f /  (float)bitmap.getWidth(), 1.f / (float)bitmap.getHeight());
		
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
				pCenter.SetY((2.f * (y + 0.5f) * pxDimensions.GetY() - 1.f) / aspectRatio * tanHFOV);
			}
			else
			{
				pCenter.SetX((2.f * (x + 0.5f) * pxDimensions.GetX() - 1.f) * tanHFOV * aspectRatio);
				pCenter.SetY((1.f -2.f * (y + 0.5f) * pxDimensions.GetY() ) *  tanHFOV);
			}

			//color z antialiasingiem
			unsigned int tmp = Sampling(pCenter, pxDimensions*0.5f, objects).toHex();

			bitmap.DrawPixel(x, y, tmp);

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

	/*
		float d = zMax - zMin;
		for (int i = 0; i < bitmap.getHeight() * bitmap.getWidth(); i++)
		{
			if (zBuffer[i] < INFINITY)
			{
				float pr = (zBuffer[i]-zMin )/ d;
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
