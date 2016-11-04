#include "RenderContext.h"
#include "structures.h"
#include <math.h>

class Stars3D
{
private:
	float m_spread,
		m_speed;
		int m_number;

	float *m_starX,
		*m_starY,
		*m_starZ;

	void InitStar(int index);
public:
	Stars3D(int number, float spread, float speed);

	void updateAndRender(RenderContext &bitmap, float delta, float fov);

	~Stars3D();
};

