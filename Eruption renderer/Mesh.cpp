#include "Mesh.h"
#include <algorithm>

Mesh::Mesh(EruptionMath::vec3 vposition, std::string filename)
{
	position = vposition;
	shader = new BasicShader();
	ObjParser parser;
	verticies = parser.LoadObj(filename);
}
Mesh::~Mesh()
{
}
void Mesh::Draw(Rasterizer &raterizer, EruptionMath::Color color, float time)
{
	fTheta += 1.0f * time;

	EruptionMath::vec3 light_direction(0.0f, 0.0f, -1.0f);

	std::vector<EruptionMath::Triangle> toDraw;
	for (auto tri : verticies)
	{
		
		EruptionMath::Triangle vertexShader(EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0));
		
		if (shader != 0)
		{
			shader->SetTime(fTheta);
			shader->SetPosition(position);
		}
		vertexShader.p[0] = shader->VertexShader(tri.p[0]);
		vertexShader.p[1] = shader->VertexShader(tri.p[1]);
		vertexShader.p[2] = shader->VertexShader(tri.p[2]);

		vertexShader.color = shader->FragmentShader(color);

		toDraw.push_back(vertexShader);

		//Painters algorithm what should be drawn last, so you see those pixels
		std::sort(toDraw.begin(), toDraw.end(), [](EruptionMath::Triangle & tri1, EruptionMath::Triangle &tri2)
		{
			float z1 = (tri1.p[0].z + tri1.p[1].z + tri1.p[2].z) / 3.0f;
			float z2 = (tri2.p[0].z + tri2.p[1].z + tri2.p[2].z) / 3.0f;
			return z1 > z2;
		});
		for (auto x : toDraw)
		{
			raterizer.DrawTriangle(x, x.color.toRGB());
		}
	}
}

