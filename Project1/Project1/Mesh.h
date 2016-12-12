#pragma once
#include "Primitive.h"
#include "Triangle.h"

class Mesh :
	public Primitive
{
private:
	int tIndex;
	float3 m_uvw = float3 ();

public:
	Mesh();
	Mesh(string filename, Material &material);
	~Mesh();

	vector <float3> m_vertices;
	vector <float2> m_uvs;
	vector <Triangle> m_triangles;
	HitInfo Intersect(Ray &ray, float distance);

	Color getColor(float3 point);


	bool static importOBJ(string filename, vector<Mesh> &meshes);
	
	bool importOBJ(string filename);
	

	vector<Triangle> & getTriangles() { return m_triangles; }
	vector <float3> & getVertices() { return m_vertices; }
};

