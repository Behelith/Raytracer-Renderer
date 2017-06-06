#include "Mesh.h"
#include "fstream"
#include "cstring"

Mesh::Mesh()
{
}

Mesh::Mesh(string filename, Material &material)
{
	m_material = &material;
	importOBJ(filename);
}

Mesh::~Mesh()
{
	m_triangles.clear();
	m_vertices.clear();
	m_uvs.clear();
}

HitInfo Mesh::Intersect(Ray& ray, float distance)
{
	HitInfo objectHit(float3(), float3(), Color::GREEN, INFINITY);


	for (int i = 0; i < m_triangles.size(); i++)
		//for (Triangle t : m_triangles)
	{
		HitInfo nearestHit = m_triangles[i].Intersect(ray, distance, m_vertices[m_triangles[i].m_indecies[0]], m_vertices[m_triangles[i].m_indecies[1]], m_vertices[m_triangles[i].m_indecies[2]], &m_uvw);
		//float isectt =
		nearestHit.setTIndex(i);

		if (nearestHit.getDistance() > 0 && nearestHit.getDistance() < objectHit.getDistance())
		{
			//	tIndex = i;
			objectHit = nearestHit;
			//float3 p = ray.getOrigin() + ray.getDirection()*nearestHit.getDistance();
			//	return HitInfo(m_triangles[i].getNormal(), p, getColor(), hi.getDistance());
			//	break;
		}
	}

	if (objectHit.getDistance() < INFINITY)
	{
		//objectHit.setColor(getColor(float3()));
		objectHit.setColor(Color(0,0,0));
		return objectHit;
	}
	return HitInfo();

}

Color Mesh::getColor(HitInfo hitinfo)
{
	//return *m_color;
	if (m_material->getIsTextured())
	{
		tIndex = hitinfo.getTIndex();
		//m_triangles[c].
			// pole trojkata abc =  || (b - a) X (c-a) || /2;

			//float3 e1 = *m_verts[1] - *m_verts[0];
			//float3 e2 = *m_verts[2] - *m_verts[0];	
		float3 ab = m_vertices[m_triangles[tIndex].m_indecies[1]] - m_vertices[m_triangles[tIndex].m_indecies[0]];
		float3 ac = m_vertices[m_triangles[tIndex].m_indecies[2]] - m_vertices[m_triangles[tIndex].m_indecies[0]];
		float3 cb = m_vertices[m_triangles[tIndex].m_indecies[2]] - m_vertices[m_triangles[tIndex].m_indecies[1]];
		float3 ap = hitinfo.getPoint() - m_vertices[m_triangles[tIndex].m_indecies[0]];
		float3 bp = hitinfo.getPoint() - m_vertices[m_triangles[tIndex].m_indecies[1]];
		float3 cp = hitinfo.getPoint() - m_vertices[m_triangles[tIndex].m_indecies[2]];


		float abc =  float3::cross(ab, ac).length() * 0.5f;

		// u = cap/ abc
		//float cap = float3::cross(*m_verts[0] - *m_verts[2], point - *m_verts[2]).length()*0.5f;
		float cap = float3::cross(ac, cp).length()*0.5f;

		// v = abp / abc
		//float abp = float3::cross(*m_verts[1] - *m_verts[0], point - *m_verts[0]).length()*0.5f;
		float abp = float3::cross(ab, ap).length()*0.5f;
		//float bcp = float3::cross(cb, bp).length()*0.5f;


		//w
	//	float bcp = float3::cross(m_vertices[m_triangles[c].m_indecies[2]] - m_vertices[m_triangles[c].m_indecies[1]], point - m_vertices[m_triangles[c].m_indecies[1]]).length()*0.5f;

		float u = cap / abc;
		float v = abp / abc;
	//	float w = bcp / abc;
	//	*/
		//*
		if (u < 0) u = 0;
		else if (u > 1.0) u = 1;

		if (v < 0) v = 0;
		else if (v > 1.0) v = 1;

		//if (w < 0) w = 0;
		//else if (w > 1.0) w = 1;

		float w = 1.f - (u + v);
		//*/
		float2 uv = m_uvs[m_triangles[tIndex].m_indecies[0]] * u +
		/*float2 uv2 = */m_uvs[m_triangles[tIndex].m_indecies[1]] * v+
		/*float2 uv3 = */m_uvs[m_triangles[tIndex].m_indecies[2]] * w;

		
		//		float2 uv3 = m_uvs[m_triangles[c].m_indecies[2]] * uvw.z;
//		float2 uvw2 = uv1 + uv2 + uv3;

		int x = (uv.GetX()* m_material->getTexture().getWidth());
		int y = (uv.GetY()* m_material->getTexture().getHeight());

		//	return Color(m_material->getTexture().getComponents()[x + y*m_material->getTexture().getWidth()]);

		return Color(m_material->getTexture().getComponents()[x + y * m_material->getTexture().getWidth()]);
	}
	return m_material->getColor();
}

void split(std::string str, std::string splitBy, std::vector<std::string>& tokens)
{
	/* Store the original string in the array, so we can loop the rest
	* of the algorithm. */
	tokens.push_back(str);

	// Store the split index in a 'size_t' (unsigned integer) type.
	size_t splitAt;
	// Store the size of what we're splicing out.
	size_t splitLen = splitBy.size();
	// Create a string for temporarily storing the fragment we're processing.
	std::string frag;
	// Loop infinitely - break is internal.
	while (true)
	{
		/* Store the last string in the vector, which is the only logical
		* candidate for processing. */
		frag = tokens.back();
		/* The index where the split is. */
		splitAt = frag.find(splitBy);
		// If we didn't find a new split point...
		if (splitAt == string::npos)
		{
			// Break the loop and (implicitly) return.
			break;
		}
		/* Put everything from the left side of the split where the string
		* being processed used to be. */
		tokens.back() = frag.substr(0, splitAt);
		/* Push everything from the right side of the split to the next empty
		* index in the vector. */
		tokens.push_back(frag.substr(splitAt + splitLen, frag.size() - (splitAt + splitLen)));
	}
}

bool Mesh::importOBJ(string filename)
{
	string line;
	m_vertices.clear();
	m_triangles.clear();
	m_uvs.clear();
	int i = 0;
	//string s;
	//vector<float3> v;
	//vector<Triangle> t;
	bool isTextured = false;

	ifstream myfile(filename);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			vector <string> tmp1;
			split(line, " ", tmp1);
			if (tmp1[0] == "v")
			{
				m_vertices.push_back(float3(stof(tmp1[1]), stof(tmp1[2]), stof(tmp1[3])));
			}
			else if (tmp1[0] == "vt")
			{
				m_uvs.push_back(
					float2(
						stof(tmp1[1]),
						stof(tmp1[2])
					)
				);
				isTextured = true;

			}
			else if (/*isTextured && */tmp1[0] == "f")
			{
				vector <string> tmp2;
				//	float3 *a, *b, *c;

				vector <int> ind;
				split(tmp1[1], "/", tmp2);
				ind.push_back(stoi(tmp2[0]) - 1);
				tmp2.clear();

				split(tmp1[2], "/", tmp2);
				ind.push_back(stoi(tmp2[0]) - 1);
				tmp2.clear();

				split(tmp1[3], "/", tmp2);
				ind.push_back(stoi(tmp2[0]) - 1);
				tmp2.clear();

				//split(tmp1[1], "/", tmp2);
				//a = &m_vertices[stoi(tmp2[0]) - 1];
				//tmp2.clear();

				//split(tmp1[2], "/", tmp2);
				//b = &m_vertices[stoi(tmp2[0]) - 1];
				//tmp2.clear();

				//split(tmp1[3], "/", tmp2);
				//c = &m_vertices[stoi(tmp2[0]) - 1];
				//tmp2.clear();

				//	if (i == 1) m_triangles.push_back(Triangle(a, b, c, Color::DVIOLET));
				//	else
				Triangle tempT(ind, *m_material);


				m_triangles.push_back(tempT);

			}
			i = (i + 1) % 4;
		}
		myfile.close();
	}

	cout << "vertexow: " << m_vertices.size() << endl;
	cout << "trojkatow: " << m_triangles.size() << endl;

	return true;
}
