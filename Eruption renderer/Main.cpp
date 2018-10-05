#include <iostream>
#include <stdio.h>

#include "Window.h"
#include "Rasterizer.h"
#include "Mesh.h"

static float screenHeight = 600;
static float screenWidth = 800;

static bool g_Running = true;


static void
HandleKeyEvent(const SDL_Event &event)
{
	switch (event.key.keysym.sym) {
	default:
		break;
	case SDLK_ESCAPE:
		g_Running = false;
		break;
	}
}
static void
HandleEvent(const SDL_Event &event)
{
	switch (event.type) {
	default:
		break;
	case SDL_QUIT:
		g_Running = false;
		break;
	case SDL_KEYDOWN:
		HandleKeyEvent(event);
		break;
	}
}
int main(int argc, char* argv[])
{
	// Timing variables
	Uint32 old_time, current_time = 0;
	float ftime;

	//create window,draw surface and Rasterizer
	Window *window = new Window();
	SDL_Surface *screen = SDL_GetWindowSurface(window->window);
	Rasterizer *rasterizer = new Rasterizer(screen);

	

	//Create a projection matrix 
	EruptionMath::mat4 projectionMatirx = projectionMatirx.ProjectionMatirx(0.1f, 1000.0f, 90.0f, screenWidth, screenHeight);
	Mesh cube;
	//red pixel
	EruptionMath::Color color(255 ,255, 255, 255);
    int ourColor = color.toRGB();

	//
	EruptionMath::vec3 vertex1(0, 499, 0);
	EruptionMath::vec3 vertex2(screenWidth / 2, 0, 0);
	EruptionMath::vec3 vertex3(799, 499, 0);


	EruptionMath::Triangle tri(vertex1, vertex2, vertex3);
	while (g_Running)
	{
		old_time = current_time;
		current_time = SDL_GetTicks();
		ftime = (current_time - old_time) / 1000.0f;

		SDL_Event event;
		while (SDL_PollEvent(&event))
			HandleEvent(event);

			SDL_FillRect(screen, 0, 0);
			//render here
			//rasterizer->DrawTriangle(tri, ourColor);
			cube.Draw(*rasterizer, color, projectionMatirx,ftime);

			SDL_UpdateWindowSurface(window->window);
	}
	// Close and destroy the window
	SDL_DestroyWindow(window->window);

	// Clean up
	SDL_Quit();

	return 0;
}