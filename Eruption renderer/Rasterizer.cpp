#include "Rasterizer.h"

Rasterizer::Rasterizer(SDL_Surface *_surface)
{
	surface = _surface;
}


Rasterizer::~Rasterizer()
{
}

Uint32 Rasterizer::GetPixel(int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}
void Rasterizer::PutPixel(int x, int y, Uint32 pixel)
{
	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to set */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}


void Rasterizer::DrawLine(EruptionMath::vec3 vt1, EruptionMath::vec3 vt2, Uint32 color)
{
	float xdiff = (vt2.x - vt1.x);
	float ydiff = (vt2.y - vt1.y);

	if (xdiff == 0.0f && ydiff == 0.0f) {
		PutPixel(vt1.x, vt1.y, color);
		return;
	}

	if (fabs(xdiff) > fabs(ydiff)) {
		float xmin, xmax;

		// set xmin to the lower x value given
		// and xmax to the higher value
		if (vt1.x < vt2.x) {
			xmin = vt1.x;
			xmax = vt2.x;
		}
		else {
			xmin = vt2.x;
			xmax = vt1.x;
		}

		// draw line in terms of y slope
		float slope = ydiff / xdiff;
		for (float x = xmin; x <= xmax; x += 1.0f) {
			float y = vt1.y + ((x - vt1.x) * slope);
			PutPixel(x, y, color);
		}
	}
	else {
		float ymin, ymax;

		// set ymin to the lower y value given
		// and ymax to the higher value
		if (vt1.y < vt2.y) {
			ymin = vt1.y;
			ymax = vt2.y;
		}
		else {
			ymin = vt2.y;
			ymax = vt1.y;
		}

		// draw line in terms of x slope
		float slope = xdiff / ydiff;
		for (float y = ymin; y <= ymax; y += 1.0f) {
			float x = vt1.x + ((y - vt1.y) * slope);
			PutPixel(x, y, color);
		}
	}
}
void Rasterizer::DrawTriangle(EruptionMath::Triangle tri, unsigned int color)
{
	DrawLine(tri.p[0], tri.p[1], color);
	DrawLine(tri.p[1], tri.p[2], color);
	DrawLine(tri.p[2], tri.p[0], color);
}