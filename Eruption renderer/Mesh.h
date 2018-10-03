#pragma once
#include <vector>

#include "Math.h"
#include "Rasterizer.h"
class Mesh
{
public:
	Mesh();
	~Mesh();
	void Draw(Rasterizer &raterizer, EruptionMath::Color color, EruptionMath::mat4 projectionMatrix, float time = 0);
	std::vector<EruptionMath::Triangle> verticies;
private:
	float fTheta;
};

