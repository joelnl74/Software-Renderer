#include "Mesh.h"



Mesh::Mesh()
{
	//south
	EruptionMath::Triangle tri1(EruptionMath::vec3(0.0f, 0.0f, 0.0f), EruptionMath::vec3(0.0f, 1.0f, 0.0f), EruptionMath::vec3(1.0f, 1.0f, 0.0f));
	EruptionMath::Triangle tri2(EruptionMath::vec3(0.0f, 0.0f, 0.0f), EruptionMath::vec3(1.0f, 1.0f, 0.0f), EruptionMath::vec3(1.0f, 0.0f, 0.0f));

	//east
	EruptionMath::Triangle tri3(EruptionMath::vec3(1.0f, 0.0f, 0.0f), EruptionMath::vec3(1.0f, 1.0f, 0.0f), EruptionMath::vec3(1.0f, 1.0f, 1.0f));
	EruptionMath::Triangle tri4(EruptionMath::vec3(1.0f, 0.0f, 0.0f), EruptionMath::vec3(1.0f, 1.0f, 1.0f), EruptionMath::vec3(1.0f, 0.0f, 1.0f));

	//north
	EruptionMath::Triangle tri5(EruptionMath::vec3(1.0f, 0.0f, 1.0f), EruptionMath::vec3(1.0f, 1.0f, 1.0f), EruptionMath::vec3(0.0f, 1.0f, 1.0f));
	EruptionMath::Triangle tri6(EruptionMath::vec3(1.0f, 0.0f, 1.0f), EruptionMath::vec3(0.0f, 1.0f, 1.0f), EruptionMath::vec3(0.0f, 0.0f, 1.0f));

	//west
	EruptionMath::Triangle tri7(EruptionMath::vec3(0.0f, 0.0f, 1.0f), EruptionMath::vec3(0.0f, 1.0f, 1.0f), EruptionMath::vec3(0.0f, 1.0f, 0.0f));
	EruptionMath::Triangle tri8(EruptionMath::vec3(0.0f, 0.0f, 1.0f), EruptionMath::vec3(0.0f, 1.0f, 0.0f), EruptionMath::vec3(0.0f, 0.0f, 0.0f));
	
	//top
	EruptionMath::Triangle tri9(EruptionMath::vec3(0.0f, 1.0f, 0.0f), EruptionMath::vec3(0.0f, 1.0f, 1.0f), EruptionMath::vec3(1.0f, 1.0f, 1.0f));
	EruptionMath::Triangle tri10(EruptionMath::vec3(0.0f, 1.0f, 0.0f), EruptionMath::vec3(1.0f, 1.0f, 1.0f), EruptionMath::vec3(1.0f, 1.0f, 0.0f));

	//bottem
	EruptionMath::Triangle tri11(EruptionMath::vec3(1.0f, 0.0f, 1.0f), EruptionMath::vec3(0.0f, 0.0f, 1.0f), EruptionMath::vec3(0.0f, 0.0f, 0.0f));
	EruptionMath::Triangle tri12(EruptionMath::vec3(1.0f, 0.0f, 1.0f), EruptionMath::vec3(0.0f, 0.0f, 0.0f), EruptionMath::vec3(1.0f, 0.0f, 0.0f));

	verticies.push_back(tri1);
	verticies.push_back(tri2);
	verticies.push_back(tri3);
	verticies.push_back(tri4);
	verticies.push_back(tri5);
	verticies.push_back(tri6);
	verticies.push_back(tri7);
	verticies.push_back(tri8);
	verticies.push_back(tri9);
	verticies.push_back(tri10);
	verticies.push_back(tri11);
	verticies.push_back(tri12);

}

void Mesh::Draw(Rasterizer &raterizer, EruptionMath::Color color, EruptionMath::mat4 projectionMatrix, float time)
{
	EruptionMath::Color _color(255, 255, 255, 255);
	int col = _color.toRGB();
	fTheta += 1.0f * time;

	EruptionMath::mat4 z,x;
	for (auto tri : verticies)
	{
		EruptionMath::Triangle RotateX(EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0));
		EruptionMath::Triangle RotateZ(EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0));
		EruptionMath::Triangle triTranslated(EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0));
		EruptionMath::Triangle triProjected(EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0), EruptionMath::vec3(0, 0, 0));
		
		z = z.RotateZ(fTheta);

		z.MulitiplyMatrixVector(tri.p[0], RotateZ.p[0], z);
		z.MulitiplyMatrixVector(tri.p[1], RotateZ.p[1], z);
		z.MulitiplyMatrixVector(tri.p[2], RotateZ.p[2], z);

		x = x.RotateX(fTheta);

		// Rotate in X-Axis
		x.MulitiplyMatrixVector(RotateZ.p[0], RotateX.p[0], x);
		x.MulitiplyMatrixVector(RotateZ.p[1], RotateX.p[1], x);
		x.MulitiplyMatrixVector(RotateZ.p[2], RotateX.p[2], x);

		triTranslated = RotateX;

		triTranslated.p[0].z = triTranslated.p[0].z + 3;
		triTranslated.p[1].z = triTranslated.p[1].z + 3;
		triTranslated.p[2].z = triTranslated.p[2].z + 3;

		projectionMatrix.MulitiplyMatrixVector(triTranslated.p[0], triProjected.p[0], projectionMatrix);
		projectionMatrix.MulitiplyMatrixVector(triTranslated.p[1], triProjected.p[1], projectionMatrix);
		projectionMatrix.MulitiplyMatrixVector(triTranslated.p[2], triProjected.p[2], projectionMatrix);

		triProjected.p[0].x += 1; triProjected.p[0].y += 1;
		triProjected.p[1].x += 1; triProjected.p[1].y += 1;
		triProjected.p[2].x += 1; triProjected.p[2].y += 1;

		triProjected.p[0].x *= 0.5f * 800.0f; triProjected.p[0].y *= 0.5f * 600.0f;
		triProjected.p[1].x *= 0.5f * 800.0f; triProjected.p[1].y *= 0.5f * 600.0f;
		triProjected.p[2].x *= 0.5f * 800.0f; triProjected.p[2].y *= 0.5f * 600.0f;


		raterizer.DrawTriangle(triProjected, col);
	}
}

Mesh::~Mesh()
{
}
