#include <iostream>
#include <stdio.h>

#include "Window.h"
#include "Rasterizer.h"
#include "Mesh.h"
#include "BasicShader.h"

#define screenHeight 600;
#define screenWidth 800;

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

	rasterizer->mode = RasterizerMode::Line_And_Fill;
	//Create a projection matrix 
	EruptionMath::mat4 projectionMatirx = projectionMatirx.ProjectionMatirx(0.1f, 1000.0f, 90.0f, 800, 600);
	Mesh cube(EruptionMath::vec3(400.0f, 300.0f, 0.0f), "Resources/OBJ/Star.obj" );
	//Mesh cube1(EruptionMath::vec3(200.0f, 150.0f, 0.0f),"Resources/OBJ/Cube.obj"  );

	BasicShader *basic = new BasicShader(projectionMatirx);

	EruptionMath::Color color(255 ,255, 255);
	//red pixel
	EruptionMath::Color color2(0, 0, 255);

	while (g_Running)
	{
		old_time = current_time;
		current_time = SDL_GetTicks();

		ftime = (current_time - old_time) / 1000.0f;
		printf("%f", ftime);
		SDL_Event event;
		while (SDL_PollEvent(&event))
			HandleEvent(event);

			SDL_FillRect(screen, 0, 0);
			//render here
		     cube.Draw(*rasterizer, color, projectionMatirx,ftime, basic);
			 //cube1.Draw(*rasterizer, color, projectionMatirx, ftime, basic);

			SDL_UpdateWindowSurface(window->window);
	}
	// Close and destroy the window
	SDL_DestroyWindow(window->window);

	// Clean up
	SDL_Quit();

	return 0;
}