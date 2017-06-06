#pragma once
#include <cmath>
#include <iostream>
#include "float4.h"
using namespace std;

class Matrix4
{

	float **m_m;

public:

	/** Default constructor */
	Matrix4()
	{
		//	m_m = initMatrix4();
		m_m = new float *[4];

		for (int i = 0; i < 4; i++)
			m_m[i] = new float[4];
	};
		
	/** Copy constructor */
	Matrix4(const Matrix4& other) 
	{
		m_m = new float *[4];

		for (int i = 0; i < 4; i++)
			m_m[i] = new float[4];

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_m[i][j] = other.get(i,j);
			}
		}
	}

	~Matrix4()
	{
		for (int i = 0; i < 4; ++i)
			delete[] m_m[i];

			delete[] m_m;
	}



	Matrix4& operator= (const Matrix4& other)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_m[i][j] = other.get(i, j);
			}
		}

		return *this;
	}



	float**  initMatrix4()
	{
		float **matrix = new float *[4];

		for (int i = 0; i < 4; ++i)
			matrix[i] = new float[4];

		return  matrix;
	}


	Matrix4 initIdentity()
	{
		//float **m_m;
		//Matrix4 res;



		m_m[0][0] = 1; m_m[0][1] = 0; m_m[0][2] = 0; m_m[0][3] = 0;
		m_m[1][0] = 0; m_m[1][1] = 1; m_m[1][2] = 0; m_m[1][3] = 0;
		m_m[2][0] = 0; m_m[2][1] = 0; m_m[2][2] = 1; m_m[2][3] = 0;
		m_m[3][0] = 0; m_m[3][1] = 0; m_m[3][2] = 0; m_m[3][3] = 1;
		//res.SetM(m_m);
	//	return res;
		return *this;

	}

	Matrix4 initD()
	{
	//	Matrix4 res;



		m_m[0][0] = 1; m_m[0][1] = 2; m_m[0][2] = 3; m_m[0][3] = 4;
		m_m[1][0] = 2; m_m[1][1] = 1; m_m[1][2] = 2; m_m[1][3] = 3;
		m_m[2][0] = 3; m_m[2][1] = 2; m_m[2][2] = 1; m_m[2][3] = 2;
		m_m[3][0] = 4; m_m[3][1] = 3; m_m[3][2] = 2; m_m[3][3] = 1;
	//	res.SetM(m_m);
		//return res;
		return *this;


	}

	Matrix4 InitScreenSpaceTransform(float halfWidth, float halfHeight)
	{
		//Matrix4 res;
		m_m[0][0] = halfWidth;	m_m[0][1] = 0;				m_m[0][2] = 0;		m_m[0][3] = halfWidth;
		m_m[1][0] = 0;			m_m[1][1] = -halfHeight;	m_m[1][2] = 0;		m_m[1][3] = halfHeight;
		m_m[2][0] = 0;			m_m[2][1] = 0;				m_m[2][2] = 1;		m_m[2][3] = 0;
		m_m[3][0] = 0;			m_m[3][1] = 0;				m_m[3][2] = 0;		m_m[3][3] = 1;
		//res.SetM(m_m);
		//return res;
		return *this;

	}

	Matrix4 InitTranslation(float x, float y, float z)
	{
		//Matrix4 res;
		m_m[0][0] = 1;	m_m[0][1] = 0;	m_m[0][2] = 0;	m_m[0][3] = x;
		m_m[1][0] = 0;	m_m[1][1] = 1;	m_m[1][2] = 0;	m_m[1][3] = y;
		m_m[2][0] = 0;	m_m[2][1] = 0;	m_m[2][2] = 1;	m_m[2][3] = z;
		m_m[3][0] = 0;	m_m[3][1] = 0;	m_m[3][2] = 0;	m_m[3][3] = 1;
		//res.SetM(m_m);
		//return res;
		//return this;
		return *this;

	}

	Matrix4 InitRotation(float x, float y, float z, float angle)
	{
		//Matrix4 res;

		float rsin = sin(angle);
		float rcos = cos(angle);

		m_m[0][0] = rcos + x*x*(1 - rcos);		m_m[0][1] = x*y*(1 - rcos) - z*rsin;	m_m[0][2] = x*z*(1 - rcos) + y*rsin;	m_m[0][3] = 0;
		m_m[1][0] = y*x*(1 - rcos) + z*rsin;	m_m[1][1] = rcos + y*y*(1 - rcos);		m_m[1][2] = y*z*(1 - rcos) - x*rsin;	m_m[1][3] = 0;
		m_m[2][0] = z*x*(1 - rcos) - y*rsin;	m_m[2][1] = z*y*(1 - rcos) + x*rsin;	m_m[2][2] = rcos + z*z*(1 - rcos);		m_m[2][3] = 0;
		m_m[3][0] = 0;							m_m[3][1] = 0;							m_m[3][2] = 0;							m_m[3][3] = 1;

		//res.SetM(m_m);
		//return res;
		return *this;

	}

	Matrix4 InitRotation(float x, float y, float z)
	{
		//	z = 0;
		Matrix4 rx;// = new Matrix4f();
		Matrix4 ry;// = new Matrix4f();
		Matrix4 rz;// = new Matrix4f();

	//	Matrix4 res = Matrix4().initIdentity();

		rz.m_m[0][0] = cos(z);				rz.m_m[0][1] = -sin(z);				rz.m_m[0][2] = 0;					rz.m_m[0][3] = 0;
		rz.m_m[1][0] = sin(z);				rz.m_m[1][1] = cos(z);				rz.m_m[1][2] = 0;					rz.m_m[1][3] = 0;
		rz.m_m[2][0] = 0;					rz.m_m[2][1] = 0;					rz.m_m[2][2] = 1;					rz.m_m[2][3] = 0;
		rz.m_m[3][0] = 0;					rz.m_m[3][1] = 0;					rz.m_m[3][2] = 0;					rz.m_m[3][3] = 1;

		rx.m_m[0][0] = 1;					rx.m_m[0][1] = 0;					rx.m_m[0][2] = 0;					rx.m_m[0][3] = 0;
		rx.m_m[1][0] = 0;					rx.m_m[1][1] = cos(x);				rx.m_m[1][2] = -sin(x);				rx.m_m[1][3] = 0;
		rx.m_m[2][0] = 0;					rx.m_m[2][1] = sin(x);				rx.m_m[2][2] = cos(x);				rx.m_m[2][3] = 0;
		rx.m_m[3][0] = 0;					rx.m_m[3][1] = 0;						rx.m_m[3][2] = 0;					rx.m_m[3][3] = 1;

		ry.m_m[0][0] = cos(y);				ry.m_m[0][1] = 0;					ry.m_m[0][2] = -sin(y);				ry.m_m[0][3] = 0;
		ry.m_m[1][0] = 0;					ry.m_m[1][1] = 1;					ry.m_m[1][2] = 0;					ry.m_m[1][3] = 0;
		ry.m_m[2][0] = sin(y);				ry.m_m[2][1] = 0;					ry.m_m[2][2] = cos(y);				ry.m_m[2][3] = 0;
		ry.m_m[3][0] = 0;					ry.m_m[3][1] = 0;					ry.m_m[3][2] = 0;					ry.m_m[3][3] = 1;


		//m_m = ;
		//res.SetM(m_m);
		//res = (rz * (ry * rx));
		return (rz.mul(ry.mul(rx)));// .GetM()res;
	}

	Matrix4 InitScale(float x, float y, float z)
	{
		//Matrix4 res;

		//float **m = initMatrix4();

		//res.GetM()[0][0] = x;	res.GetM()[0][1] = 0;	res.GetM()[0][2] = 0;	res.GetM()[0][3] = 0;
		//res.GetM()[1][0] = 0;	res.GetM()[1][1] = y;	res.GetM()[1][2] = 0;	res.GetM()[1][3] = 0;
		//res.GetM()[2][0] = 0;	res.GetM()[2][1] = 0;	res.GetM()[2][2] = z;	res.GetM()[2][3] = 0;
		//res.GetM()[3][0] = 0;	res.GetM()[3][1] = 0;	res.GetM()[3][2] = 0;	res.GetM()[3][3] = 1;

		//res.GetM() = m;
		//	return res;

		m_m[0][0] = x;	m_m[0][1] = 0;	m_m[0][2] = 0;	m_m[0][3] = 0;
		m_m[1][0] = 0;	m_m[1][1] = y;	m_m[1][2] = 0;	m_m[1][3] = 0;
		m_m[2][0] = 0;	m_m[2][1] = 0;	m_m[2][2] = z;	m_m[2][3] = 0;
		m_m[3][0] = 0;	m_m[3][1] = 0;	m_m[3][2] = 0;	m_m[3][3] = 1;
		//res.SetM(m_m);
	//	return res;

	}

	Matrix4 InitPerspective(float fov, float aspectRatio, float zNear, float zFar)
	{
		//Matrix4 res;

		float tanHalfFOV = tan(fov / 2);
		float zRange = zNear - zFar;

		m_m[0][0] = 1.0f / (tanHalfFOV * aspectRatio);	m_m[0][1] = 0;					m_m[0][2] = 0;							m_m[0][3] = 0;
		m_m[1][0] = 0;									m_m[1][1] = 1.0f / tanHalfFOV;	m_m[1][2] = 0;							m_m[1][3] = 0;
		m_m[2][0] = 0;									m_m[2][1] = 0;					m_m[2][2] = (-zNear - zFar) / zRange;	m_m[2][3] = 2 * zFar * zNear / zRange;
		m_m[3][0] = 0;									m_m[3][1] = 0;					m_m[3][2] = 1;							m_m[3][3] = 0;


		//res.GetM()[0][0] = 1.0f / (tanHalfFOV * aspectRatio);	res.GetM()[0][1] = 0;					res.GetM()[0][2] = 0;							res.GetM()[0][3] = 0;
		//res.GetM()[1][0] = 0;									res.GetM()[1][1] = 1.0f / tanHalfFOV;	res.GetM()[1][2] = 0;							res.GetM()[1][3] = 0;
		//res.GetM()[2][0] = 0;									res.GetM()[2][1] = 0;					res.GetM()[2][2] = (-zNear - zFar) / zRange;	res.GetM()[2][3] = 2 * zFar * zNear / zRange;
		//res.GetM()[3][0] = 0;									res.GetM()[3][1] = 0;					res.GetM()[3][2] = 1;							res.GetM()[3][3] = 0;

	//	res.SetM(m_m);
	//	return res;

		return *this;

	}

	Matrix4 InitOrthographic(float left, float right, float bottom, float top, float near, float far)
	{
		float width = right - left;
		float height = top - bottom;
		float depth = far - near;
		//Matrix4 res;

		m_m[0][0] = 2 / width;	m_m[0][1] = 0;			m_m[0][2] = 0;				m_m[0][3] = -(right + left) / width;
		m_m[1][0] = 0;			m_m[1][1] = 2 / height; m_m[1][2] = 0;				m_m[1][3] = -(top + bottom) / height;
		m_m[2][0] = 0;			m_m[2][1] = 0;			m_m[2][2] = -2 / depth;		m_m[2][3] = -(far + near) / depth;
		m_m[3][0] = 0;			m_m[3][1] = 0;			m_m[3][2] = 0;				m_m[3][3] = 1;

		//res.GetM()[0][0] = 2 / width;	res.GetM()[0][1] = 0;			res.GetM()[0][2] = 0;				res.GetM()[0][3] = -(right + left) / width;
		//res.GetM()[1][0] = 0;			res.GetM()[1][1] = 2 / height; res.GetM()[1][2] = 0;				res.GetM()[1][3] = -(top + bottom) / height;
		//res.GetM()[2][0] = 0;			res.GetM()[2][1] = 0;			res.GetM()[2][2] = -2 / depth;		res.GetM()[2][3] = -(far + near) / depth;
		//res.GetM()[3][0] = 0;			res.GetM()[3][1] = 0;			res.GetM()[3][2] = 0;				res.GetM()[3][3] = 1;
		//res.SetM(m_m);
		//return res;

		return *this;
	}

	Matrix4 InitRotation(float4 forward, float4 up)
	{
		float4 f = forward.Normalized();

		float4 r = up.Normalized();
		r = r.cross(f);

		float4 u = f.cross(r);

		return InitRotation(f, u, r);
	}
	Matrix4 InitRotation(float4 forward, float4 up, float4 right)
	{
		float4 f = forward;
		float4 r = right;
		float4 u = up;
	//	Matrix4 res;

		m_m[0][0] = r.GetX();	m_m[0][1] = r.GetY();	m_m[0][2] = r.GetZ();	m_m[0][3] = 0;
		m_m[1][0] = u.GetX();	m_m[1][1] = u.GetY();	m_m[1][2] = u.GetZ();	m_m[1][3] = 0;
		m_m[2][0] = f.GetX();	m_m[2][1] = f.GetY();	m_m[2][2] = f.GetZ();	m_m[2][3] = 0;
		m_m[3][0] = 0;			m_m[3][1] = 0;			m_m[3][2] = 0;			m_m[3][3] = 1;

		//res.GetM()[0][0] = r.GetX();	res.GetM()[0][1] = r.GetY();	res.GetM()[0][2] = r.GetZ();	res.GetM()[0][3] = 0;
		//res.GetM()[1][0] = u.GetX();	res.GetM()[1][1] = u.GetY();	res.GetM()[1][2] = u.GetZ();	res.GetM()[1][3] = 0;
		//res.GetM()[2][0] = f.GetX();	res.GetM()[2][1] = f.GetY();	res.GetM()[2][2] = f.GetZ();	res.GetM()[2][3] = 0;
		//res.GetM()[3][0] = 0;			res.GetM()[3][1] = 0;			res.GetM()[3][2] = 0;			res.GetM()[3][3] = 1;

	//	return res;

		return *this;
	}

	float4 Transform(float4 r) const
	{

		return float4(m_m[0][0] * r.GetX() + m_m[0][1] * r.GetY() + m_m[0][2] * r.GetZ() + m_m[0][3] * r.GetW(),
			m_m[1][0] * r.GetX() + m_m[1][1] * r.GetY() + m_m[1][2] * r.GetZ() + m_m[1][3] * r.GetW(),
			m_m[2][0] * r.GetX() + m_m[2][1] * r.GetY() + m_m[2][2] * r.GetZ() + m_m[2][3] * r.GetW(),
			m_m[3][0] * r.GetX() + m_m[3][1] * r.GetY() + m_m[3][2] * r.GetZ() + m_m[3][3] * r.GetW());

	}


	Matrix4 mul(const Matrix4 &r)
	{
		Matrix4 res;
		//r.showMatrix();

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res.set(i, j, m_m[i][0] * r.get(0, j) +
					m_m[i][1] * r.get(1, j) +
					m_m[i][2] * r.get(2, j) +
					m_m[i][3] * r.get(3, j));
			}
		}
		//res.showMatrix();

		//return Matrix4().initD();
		return res;

	}

	float** GetM()
	{
		return m_m;
	}

	void SetM(float* matrix[])
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				//result.set(i, j,
				m_m[i][j] = matrix[i][j];
			}
		}
	}


	float get(int x, int y) const
	{
		return  m_m[x][y];
	}

	void set(int x, int y, float value)
	{
		m_m[x][y] = value;
	}


	void showMatrix()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				std::cout << get(i, j) << "\t";
			}
			std::cout << "\n";
		}
	}

};

