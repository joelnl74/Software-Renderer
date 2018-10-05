#pragma once
#include "Math.h"
#include "SDL.h"

struct EdgeEquation {
	float a;
	float b;
	float c;
	bool tie;

	EdgeEquation(const EruptionMath::vec3 v0, const EruptionMath::vec3 &v1)
	{
		a = v0.y - v1.y;
		b = v1.x - v0.x;
		c = -(a * (v0.x + v1.x) + b * (v0.y + v1.y)) / 2;
		tie = a != 0 ? a > 0 : b > 0;
	}

	/// Evaluate the edge equation for the given point. 
	float evaluate(float x, float y)
	{
		return a * x + b * y + c;
	}

	/// Test if the given point is inside the edge. 
	bool test(float x, float y)
	{
		return test(evaluate(x, y));
	}

	/// Test for a given evaluated value. 
	bool test(float v)
	{
		return (v > 0 || v == 0 && tie);
	}
};

class Rasterizer
{
public:
	Rasterizer(SDL_Surface *_surface);
	~Rasterizer();
	Uint32 GetPixel(int x, int y);
	void PutPixel(int x, int y, Uint32 pixel);
	void DrawLine(EruptionMath::vec3 vt1, EruptionMath::vec3 vt2, Uint32 color);
	void DrawTriangle(EruptionMath::Triangle, unsigned int color);
private:
	SDL_Surface *surface;

};

