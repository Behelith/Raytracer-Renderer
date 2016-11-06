#pragma once
#include "Primitive.h"
#include "Triangle.h"

class Mesh :
	public Primitive
{
private:
	vector <float3> m_vertices;
	vector <Triangle> m_triangles;
	int c;

public:
	Mesh();
	Mesh(float a);
	~Mesh();

	float Intersect(Ray &ray, float distance);
	
	Color getColor()
	{
		//return *m_color;
		return  m_triangles[c].getColor();
	}

	bool importOBJ(string filename);
	

	vector<Triangle> getTriangles() { return m_triangles; }
};

