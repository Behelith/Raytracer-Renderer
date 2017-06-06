#include "RenderContext.h"
#include "structures.h"
#include <math.h>
#include "vertex.h"

class Stars3D
{
private:
	float m_spread,
		m_speed;
	int m_number;
	float4 *m_stars;

	float *m_starX,
		*m_starY,
		*m_starZ;
	int renderMode = 0;

	void InitStar(int index);
public:
	Stars3D(int number, float spread, float speed, int mode=0);

	void updateAndRender(RenderContext &bitmap, float delta, float fov);

	~Stars3D();
};

