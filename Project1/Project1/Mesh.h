#pragma once
#include "Primitive.h"
#include "Triangle.h"

class Mesh :
	public Primitive
{
private:
	int c;

public:
	Mesh();
	Mesh(string filename);
	~Mesh();

	vector <float3> m_vertices;
	vector <Triangle> m_triangles;
	float Intersect(Ray &ray, float distance);
	
	//Color getColor()
	//{
	//	//return *m_color;
	//	return  m_triangles[c].getColor();
	//}


	bool static importOBJ(string filename, vector<Mesh> &meshes);
	
	bool importOBJ(string filename);
	

	vector<Triangle> & getTriangles() { return m_triangles; }
	vector <float3> & getVertices() { return m_vertices; }
};

