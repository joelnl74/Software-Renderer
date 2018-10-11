#pragma once
#include <vector>

#include "ObjParser.h"
#include "BasicShader.h"
#include "Rasterizer.h"
class Mesh
{
public:
	Mesh(EruptionMath::vec3 position, std::string filename);
	~Mesh();
	void Draw(Rasterizer &raterizer, EruptionMath::Color color, EruptionMath::mat4 projectionMatrix, float time , BasicShader *shader);
	void CalculateVertexStage(EruptionMath::vec3, BasicShader *shader, EruptionMath::vec3 *result);
	std::vector<EruptionMath::Triangle> verticies;
	EruptionMath::vec3 position;
private:
	float fTheta;

	
};

