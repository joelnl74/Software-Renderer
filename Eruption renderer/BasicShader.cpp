#include "BasicShader.h"


BasicShader::BasicShader(EruptionMath::mat4 projectionMatrixx)
{
	projectionMatirx = projectionMatrixx;
}


BasicShader::~BasicShader()
{
}
EruptionMath::vec3 BasicShader::VertexShader(EruptionMath::vec3 vec3)
{
	EruptionMath::vec3 RotateX, RotateZ, Translated, Projected;

	z = z.RotateZ(time); x = x.RotateX(time);

	//Rotate in Z-Axis
	z.MulitiplyMatrixVector(vec3, RotateZ, z);
	// Rotate in X-Axis
	x.MulitiplyMatrixVector(RotateZ, RotateX, x);

	Translated = RotateX;
	Translated.z += 5.0f;

	projectionMatirx.MulitiplyMatrixVector(Translated, Projected, projectionMatirx);
	
	Projected.x += 1; Projected.y += 1;
	
	Projected.x *= pos.x;
	Projected.y *= pos.y;

	return Projected;
}
EruptionMath::Color BasicShader::FragmentShader(EruptionMath::Color color)
{
	////creating normals
	//EruptionMath::vec3 normal, line1, line2;
	//line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
	//line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
	//line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

	//line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
	//line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
	//line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

	//normal.x = line1.y * line2.z - line1.z * line2.y;
	//normal.y = line1.z * line2.x - line1.x * line2.z;
	//normal.z = line1.x * line2.y - line1.y * line2.x;

	//// It's normally normal to normalise the normal
	//float l = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
	//normal.x /= l; normal.y /= l; normal.z /= l;

	//light_direction.normalize();

	//float dot = normal.x * light_direction.x + normal.y * light_direction.y + normal.z * light_direction.z;
	//color.R = 255;

	//triTranslated.color = color;
	return color;
}

