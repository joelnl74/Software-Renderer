#pragma once
#include <cmath>

namespace EruptionMath
{
	struct vec3
	{
		float x;
		float y;
		float z;

		vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f) : x(x), y(y), z(z) {}
		//add
		vec3 operator +(const vec3 &rhs)
		{
			return vec3(x + rhs.x, y + rhs.y, z + rhs.z);
		};
		//subtract
		vec3 operator -(const vec3 &rhs)
		{
			return vec3(x - rhs.x, y - rhs.y, z - rhs.z);
		}
		//?
		vec3 operator /(const vec3 &rhs)
		{
			return vec3(x / rhs.x, y / rhs.y, z / rhs.z);
		}
		//get Magnitude of the vector
		float GetMagnitude()
		{
			return sqrtf(x * x + y * y + z * z);
		}
		//multiply by a scaler value
		vec3 operator*(float num) const
		{
			return vec3(x * num, y * num, z * num);
		}
		//normalize vector
		void normalize()
		{
			float magnitude = sqrtf(x * x + y * y + z * z);
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
		//calculate and return dot product
		float DotProduct(const vec3 &vec, const vec3 &vec1) const
		{
			return (vec.x * vec1.x) + (vec.y * vec1.y) + (vec.z * vec1.z);
		}
		//calculate and return cross product
		vec3 CrossProduct(const vec3 &vec) const
		{
			return vec3(y * vec.z - z * vec.y,
				z * vec.x - x * vec.z,
				x * vec.y - y * vec.x);
		}
	};
	struct vec2
	{
		float x;
		float y;

		vec2(float x, float y) : x(x), y(y) {}

		//add
		vec2 operator +(const vec3 &rhs)
		{
			return vec2(x + rhs.x, y + rhs.y);
		};
		//subtract
		vec2 operator -(const vec3 &rhs)
		{
			return vec2(x - rhs.x, y - rhs.y);
		}
		//multiply by a scaler value
		vec2 operator*(float num) const
		{
			return vec2(x * num, y * num);
		}
		//normalize
		void normalize()
		{
			float magnitude = sqrtf(x * x + y * y);
			x /= magnitude;
			y /= magnitude;
		}
	};
	struct  Triangle
	{
		vec3 p[3];
		Triangle(vec3 vt1, vec3 vt2, vec3 vt3) 
		{
			p[0] = vt1;
			p[1] = vt2;
			p[2] = vt3;
		}

	};
	struct Color
	{
		float R, G, B, A;

		Color(float r = 255, float g = 255, float b = 255, float a = 255) { R = r; G = g, B = b, A = a; }

		Color operator + (const Color &c) const 
		{
			return (R + c.R, G + c.G, B + c.B, A + c.A);
		}
		Color operator - (const Color &c) const 
		{
			return (R - c.R, G - c.G, B - c.B, A - c.A);
		}
		Color operator * (float f) const 
		{
			return (R * f, G * f, B * f, A * f);
		}
		int toRGB()
		{
			unsigned int r = R;
			unsigned int g = G;
			unsigned int b = B;
			unsigned int a = A;

			return  a << 24 | r << 16 | g << 8 | b << 0;  // 16742927
		}
	};
	struct mat4
	{
		float m4[4][4] = { 0 };
		//Create a projection matrix
		mat4 ProjectionMatirx(float fNearr, float fFarr, float fFovv, float width, float height)
		{
			mat4 projection;

			float fNear = fNearr;
			float fFar = fFarr;
			float fFov = fFovv;
			float fAspectRatio = (float)width / (float)height;
			float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * 3.14159f);

			projection.m4[0][0] = fAspectRatio * fFovRad;
			projection.m4[1][1] = fFovRad;
			projection.m4[2][2] = fFar / (fFar - fNear);
			projection.m4[3][2] = (-fFar * fNear) / (fFar - fNear);
			projection.m4[2][3] = 1.0f;
			projection.m4[3][3] = 0.0f;

			return projection;
		};
		mat4 RotateZ(float time)
		{
			mat4 matRotZ;
			// Rotation Z
			matRotZ.m4[0][0] = cosf(time);
			matRotZ.m4[0][1] = sinf(time);
			matRotZ.m4[1][0] = -sinf(time);
			matRotZ.m4[1][1] = cosf(time);
			matRotZ.m4[2][2] = 1;
			matRotZ.m4[3][3] = 1;
			return matRotZ;
		}
		mat4 RotateX(float time)
		{
			mat4 matRotX;
			// Rotation X
			matRotX.m4[0][0] = 1;
			matRotX.m4[1][1] = cosf(time * 0.5f);
			matRotX.m4[1][2] = sinf(time * 0.5f);
			matRotX.m4[2][1] = -sinf(time * 0.5f);
			matRotX.m4[2][2] = cosf(time * 0.5f);
			matRotX.m4[3][3] = 1;

			return matRotX;
		}
		//Multiply a vector by a matrix
		void MulitiplyMatrixVector(vec3 &i, vec3 &o, mat4 &m)
		{
			o.x = i.x * m.m4[0][0] + i.y * m.m4[1][0] + i.z * m.m4[2][0] + m.m4[3][0];
			o.y = i.x * m.m4[0][1] + i.y * m.m4[1][1] + i.z * m.m4[2][1] + m.m4[3][1];
			o.z = i.x * m.m4[0][2] + i.y * m.m4[1][2] + i.z * m.m4[2][2] + m.m4[3][2];
			float w = i.x * m.m4[0][3] + i.y * m.m4[1][3] + i.z * m.m4[2][3] + m.m4[3][3];

			if (w != 0.0f)
			{
				o.x /= w; o.y /= w; o.z /= w;
			}
		};
		//matrix multiplication
		mat4 operator *(const mat4 &rhs)
		{
				this->m4[0][0] = m4[0][0] * rhs.m4[0][0] + m4[1][0] * rhs.m4[0][1] + m4[2][0] * rhs.m4[0][2] + m4[3][0] * rhs.m4[0][3];
				this->m4[1][0] = m4[0][0] * rhs.m4[1][0] + m4[1][0] * rhs.m4[1][1] + m4[2][0] * rhs.m4[1][2] + m4[3][0] * rhs.m4[1][3];
				this->m4[2][0] = m4[0][0] * rhs.m4[2][0] + m4[1][0] * rhs.m4[2][1] + m4[2][0] * rhs.m4[2][2] + m4[3][0] * rhs.m4[2][3];
				this->m4[3][0] = m4[0][0] * rhs.m4[3][0] + m4[1][0] * rhs.m4[3][1] + m4[2][0] * rhs.m4[3][2] + m4[3][0] * rhs.m4[3][3];

				this->m4[0][1] = m4[0][1] * rhs.m4[0][0] + m4[1][1] * rhs.m4[0][1] + m4[2][1] * rhs.m4[0][2] + m4[3][1] * rhs.m4[0][3];
				this->m4[1][1] = m4[0][1] * rhs.m4[1][0] + m4[1][1] * rhs.m4[1][1] + m4[2][1] * rhs.m4[1][2] + m4[3][1] * rhs.m4[1][3];
				this->m4[2][1] = m4[0][1] * rhs.m4[2][0] + m4[1][1] * rhs.m4[2][1] + m4[2][1] * rhs.m4[2][2] + m4[3][1] * rhs.m4[2][3];
				this->m4[3][1] = m4[0][1] * rhs.m4[3][0] + m4[1][1] * rhs.m4[3][1] + m4[2][1] * rhs.m4[3][2] + m4[3][1] * rhs.m4[3][3];

				this->m4[0][2] = m4[0][2] * rhs.m4[0][0] + m4[1][2] * rhs.m4[0][1] + m4[2][2] * rhs.m4[0][2] + m4[3][2] * rhs.m4[0][3];
				this->m4[1][2] = m4[0][2] * rhs.m4[1][0] + m4[1][2] * rhs.m4[1][1] + m4[2][2] * rhs.m4[1][2] + m4[3][2] * rhs.m4[1][3];
				this->m4[2][2] = m4[0][2] * rhs.m4[2][0] + m4[1][2] * rhs.m4[2][1] + m4[2][2] * rhs.m4[2][2] + m4[3][2] * rhs.m4[2][3];
				this->m4[3][2] = m4[0][2] * rhs.m4[3][0] + m4[1][2] * rhs.m4[3][1] + m4[2][2] * rhs.m4[3][2] + m4[3][2] * rhs.m4[3][3];

				this->m4[0][3] = m4[0][3] * rhs.m4[0][0] + m4[1][3] * rhs.m4[0][1] + m4[2][3] * rhs.m4[0][2] + m4[3][3] * rhs.m4[0][3];
				this->m4[1][3] = m4[0][3] * rhs.m4[1][0] + m4[1][3] * rhs.m4[1][1] + m4[2][3] * rhs.m4[1][2] + m4[3][3] * rhs.m4[1][3];
				this->m4[2][3] = m4[0][3] * rhs.m4[2][0] + m4[1][3] * rhs.m4[2][1] + m4[2][3] * rhs.m4[2][2] + m4[3][3] * rhs.m4[2][3];
				this->m4[3][3] = m4[0][3] * rhs.m4[3][0] + m4[1][3] * rhs.m4[3][1] + m4[2][3] * rhs.m4[3][2] + m4[3][3] * rhs.m4[3][3];

				return *this;
		}
	};

}



