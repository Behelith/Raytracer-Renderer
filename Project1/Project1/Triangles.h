#include "RenderContext.h"
#include "structures.h"
#include "Triangle.h"
#include <math.h>

class Triangles
{
private:
	float m_spread,
		m_speed,
		m_number;

	float *m_starX,
		*m_starY,
		*m_starZ;
	Triangle *m_triangles;


	float3 InitStar(int index);
public:
	Triangles(int number, float spread, float speed);

	void updateAndRender(RenderContext *bitmap, float delta, float fov);

	~Triangles();
};

