#include "Sphere.h"




Sphere::Sphere()
{
	delete m_material;;
}

Sphere::Sphere(float3 center, float radius, Color &color) : center(center), radius(radius)
{
	m_material = &Material::RED_D;// new Color(1.0f, 0.0f, 0.0f);
	setColor(color);

}

float3 Sphere::getNormal(float3& position) {
	float3 ret = position - center;
	ret.normalize();
	return ret;
}


float Sphere::Intersect(Ray &ray, float distance)
{
	float3
		v = ray.getOrigin() - getCenter();

	// float a = 2*float3::dot(getDirection(), getDirection()); przyjmuje sie, ze ==1
	float b = -float3::dot(ray.getDirection(), v);					// b = -(v dot d) -> b = -((o - c) dot d)
																	// b odwrocone do liczenia pierwiastkow
																	//float c = float3::dot(v, v) - (sphere.getRadius()*sphere.getRadius()); 
	float d = (b * b) - (float3::dot(v, v) - (getRadius()*getRadius()));// WYZNACZNIK - b2 - 2ac		!2a, bo wczesniej 'a' mnoze przez 2 

																		/*
																		instrukcji upraszcza sie skladowa a,
																		pierwiastek z rownania kwadratowego wychodzi wtedy cos takiego
																		v = ray.origin -sphere.center
																		a = ray.dir瓶ay.dir			// iloczyn skalarny == 1. dzieje sie to w momencie kiedy dlugosc wektora kierunku == 1;
																		b = 2 * ray.dir夫

																		i = [-b +- sqrt(delta)]/2a =	// a == 1, wiec zostaje tylko dwojka
																		[-b +- sqrt( b^2 - 4*c) ]/2 =
																		[- 2*dir夫  +- sqrt( (2*ray.dir夫)^2 - 4*c ]/2 =
																		[- 2*dir夫  +- sqrt( (4*(ray.dir夫)^2 - 4*c ]/2 =
																		[- 2*dir夫  +- 2(sqrt( (ray.dir夫)^2 - c ]/2 =				po wyciagnieciu 4 przed nawias w pierwiastku i potem przed pierwiastek. mozna podzelic calosc przez 2
																		i = -ray.dir夫 += sqrt( (ray.dir夫)^2 -c)			//odwracajac wartosc b nie zmienaimy wyniku podnoszenia do kwadratu:
																		= b +- sqrt ( b^2 -c )				i STAD WZIELY SIE TE WZORY
																		*/


	float tmp = -1;
	//if (d < 0) return -1;
	if (d < 0) tmp = -1;	// delta ujemna == brak pierwiastkow

	d = sqrtf(d);
	float i1 = (b - d),		// miejsca zerowe. zakladajac, ze pierwiastki zawsze sa nieujemne (dla naszych potrzeb) to ten zawsze bedzie mniejszy niz ten drugi (bo tu sie delte odejmuje a nizej dodaje XD)
		i2 = (b + d);
	//cout << "i1: " << i1 << ", i2: " << i2 << endl;

	if (i1 < distance) tmp = i1;	// wiec zwracamy mniejszy pierwiastek
	if (i1 <0 && i2 < distance) tmp = i2;	// jesli pierwszy jest jednak ujemny (punkt lezy w srodku sfery) to zwracamy drugi. 
											//if (i1 < distance) return i1;
											//if (i2 < distance) return i2;

											/*ogolnie rzecz biorac szukamy pierwiastkow nieujemnych. jak bedzie, pierwiastek jest == 0 to wtedy jest styczny i w poczatku ukladu tak mi sie zdaje,
											w przeviwnym wypadku pierwiastki sa  > 0. wlasciwie to interesuje nas pierwsze przeciecie z napotkanym obiektem i to wyznacza nam to mniejsze miejsce zerowe
											*/

											//cout << tmp << endl;
	if (tmp == -1 || tmp <= 0)
	{
		//	cout << "brak przeciecia" << endl;
		return tmp;
	}

	if (i1 == i2 && distance > 0) { // jesli pierwiastki sa takie same (w momencie gdy delta == 0) to promien jest styczny do sfery
		float3 p(ray.getOrigin() + ray.getDirection() * tmp);
		//	cout << "punkt styczny: " << p << endl;
		return tmp;
	}
	else
	{
		float3 p(ray.getOrigin() + ray.getDirection() * tmp);
		float3 p2(ray.getOrigin() + ray.getDirection() * i2);


		//	cout << "punkt przeciecia w zadanym kierunku: " << p << endl;
		//	if (i1 > 0 && i2 > i1) cout << "punkt przeciecia w zadanym kierunku: " << p2 << endl;

		return tmp;

	}

}
