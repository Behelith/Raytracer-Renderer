#pragma once
#include "float4.h"
#include "Matrix4.h"


class vertex
{
private:
	

public:
	float4 m_pos;// = float4();
	vertex(float x, float y)
	{
		m_pos = float4(x, y, 1, 1);
	}

	vertex(float4 pos)
	{
		m_pos = pos;;
	}

	vertex Transform(const Matrix4 &transform) const
	{
		return transform.Transform(m_pos);
	}

	vertex PerspectiveDivide()
	{
		return vertex(float4(m_pos.GetX() / m_pos.GetW(), m_pos.GetY() / m_pos.GetW(),
			m_pos.GetZ() / m_pos.GetW(), m_pos.GetW()));
	}

	float TriangleArea(vertex c, vertex b)
	{
		float x1 = c.GetX() - m_pos.GetX();
		float y1 = c.GetY() - m_pos.GetY();
		float x2 = b.GetX() - m_pos.GetX();
		float y2 = b.GetY() - m_pos.GetY();

		return (x1 * y2 - x2 * y1)*0.5;
	}
	float GetX() { return m_pos.GetX(); }

	float GetY() { return m_pos.GetY(); }
	~vertex();
};

