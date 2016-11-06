#include "Mesh.h"
#include "fstream"
#include "cstring"

Mesh::Mesh()
{


}

Mesh::Mesh(float a)
{
	//setColor(Color(0.f, 0.f, 0.5f));

	m_vertices.push_back(float3(-0.500000, -0.200000, 0.500000));
	m_vertices.push_back(float3(0.000000, 0.800000, 0.000000));
	m_vertices.push_back(float3(-0.500000, -0.200000, -0.500000));
	m_vertices.push_back(float3(0.500000, -0.200000, 0.500000));
	m_vertices.push_back(float3(0.500000, -0.200000, -0.500000));

	float3	v1(-.5, -.2, -.5);

	cout << "mesh" << endl;
	//	Triangle t(&m_vertices[1], &m_vertices[1], &m_vertices[1], Color(1,1,1));

	//Color
	//	c1(255, 0, 0),
	//	c2(0, 255, 0);

	m_triangles.push_back(Triangle(&m_vertices[1], &m_vertices[2], &m_vertices[0], C1));
	m_triangles.push_back(Triangle(&m_vertices[1], &m_vertices[4], &m_vertices[2], C2));
	m_triangles.push_back(Triangle(&m_vertices[1], &m_vertices[3], &m_vertices[4], C3));
	m_triangles.push_back(Triangle(&m_vertices[1], &m_vertices[0], &m_vertices[3], C4));
	m_triangles.push_back(Triangle(&m_vertices[2], &m_vertices[3], &m_vertices[0], C5));
	m_triangles.push_back(Triangle(&m_vertices[2], &m_vertices[4], &m_vertices[3], C6));

	//for (Triangle t : m_triangles)
	//cout << hex << t.getColor().toHex() << endl;


	//m_triangles.push_back(Triangle( float3(1,1,1), float3(1,1,1),float3(1,1,1) ));

}

Mesh::~Mesh()
{
	m_triangles.clear();
	m_vertices.clear();
}

float Mesh::Intersect(Ray& ray, float distance)
{
	

	for (int i = 0; i < m_triangles.size(); i++)
	//for (Triangle t : m_triangles)

	{
		float isect = m_triangles[i].Intersect(ray, distance);
		if (isect > 0)
		{
	//	setColor( m_triangles[i].getColor());
			c = i;
		//	cout << hex << t.getColor().toHex() << endl;
			//setColor(m_triangles[i].getColor());
			return isect;
			break;
		}
	}

	return -1;
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
			else if (tmp1[0] == "vt") isTextured = true;
			else if (isTextured && tmp1[0] == "f" )
			{
				vector <string> tmp2;
				float3 *a, *b, *c;

				split(tmp1[1], "/", tmp2);
				a = &m_vertices[stoi(tmp2[0]) - 1];
				tmp2.clear();

				split(tmp1[2], "/", tmp2);
				b = &m_vertices[stoi(tmp2[0]) - 1];
				tmp2.clear();

				split(tmp1[3], "/", tmp2);
				c = &m_vertices[stoi(tmp2[0]) - 1];
				tmp2.clear();

				if (i == 1) m_triangles.push_back(Triangle(a, b, c, C7));
				else m_triangles.push_back(Triangle(a, b, c, C8));
			}
			else if ( !isTextured && tmp1[0] == "f")
			{
				vector <string> tmp2;
				float3 *a,* b, *c;

				split(tmp1[1], "//", tmp2);
				a = &m_vertices[stoi(tmp2[0]) - 1];
				tmp2.clear();

				split(tmp1[2], "//", tmp2);
				b =& m_vertices[stoi(tmp2[0]) - 1];
				tmp2.clear();

				split(tmp1[3], "//", tmp2);
				c = &m_vertices[stoi(tmp2[0]) - 1];
				tmp2.clear();

				if (i == 1) m_triangles.push_back(Triangle(a, b, c, C7));
				else m_triangles.push_back(Triangle(a, b, c, C8));
			}
		//	line.
			i = (i + 1) % 2;
		}
		myfile.close();
	}

	cout << "vertexow: " << m_vertices.size() << endl;
	cout << "trojkatow: " << m_triangles.size() << endl;

	return true;
}
