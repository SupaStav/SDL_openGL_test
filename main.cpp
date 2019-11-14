#include <iostream>
//predefines SDL and openGl before program starts
#define SDL_MAIN_HANDLED
//SDL
#include <sdl/SDL.h>
//openGL
#include <glad/glad.h>

int main()
{
	//creates window
	SDL_Window* window = SDL_CreateWindow("okgoogle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	//creates context for openGL
	SDL_GLContext context = SDL_GL_CreateContext(window);
	
	//enables context on window
	SDL_GL_MakeCurrent(window, context);
	//loads openGL from graphics driver and outputs into terminal
	std::cout << gladLoadGLLoader(SDL_GL_GetProcAddress) << std::endl;
	
	while (true)
	{
		//SDL_Event variable is set to e
		SDL_Event e;
		//tests for events, e, in the window
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				exit(0);
			}
		}


		//sets the color of the window
		glClearColor(1, 1, 0, 1);
		//clears screen to ^^ color
		glClear(GL_COLOR_BUFFER_BIT);

		//switches back buffer to front. you write to back then switch to front.
		SDL_GL_SwapWindow(window);
	}
	//closes the program
	return 0;
}
