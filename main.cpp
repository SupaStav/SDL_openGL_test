#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <glad/glad.h>	

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
int w, h;
GLuint LoadImage(const char* file)
{
	int width, height, bpp;
	//opengl likes images upside down, so tell stbi to load them upside down
	stbi_set_flip_vertically_on_load(true);
	//load the image into the variable image, while retrieving width, height, and color channel count
	stbi_uc* image = stbi_load(file, &width, &height, &bpp, 3);
	// &width is a pointer to width, and passing a pointer so that stb image can write to the int
	//print out the variables to make sure you dont literally get a negative number for size.
	std::cout << bpp << " " << width << " " << height << std::endl;
	//create the texture in opengl
	GLuint texture;
	glGenTextures(1, &texture);
	//bind the texture to opengl, to tell it that all the functions while its bound are for this texture
	glBindTexture(GL_TEXTURE_2D, texture);
	//make is so that when the image scales up and down its pixely instead of blurry which would be GL_LINEAR instead of GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//load the actual image data and size into OpenGl
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	//unbind the texture so that you dont acidentally draw this texture after you call the function, when you thought nothing was bound. dont be a turd, dont leave your textures bound if you wanna get hired anywhere
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//put width and height into global variables so you can access them and resize the window in the other function.
	//bad practice to send this type of information over a global variable rather than a pointer, dont use if you wanna get hired.
	w = width;
	h = height;
	return texture;
}


int main()
{
	//creates window
	SDL_Window* window = SDL_CreateWindow("okgoogle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 720, 720, SDL_WINDOW_OPENGL);
	
	//creates context for openGL
	SDL_GLContext context = SDL_GL_CreateContext(window);

	//enables context on window
	SDL_GL_MakeCurrent(window, context);
	//loads openGL from graphics driver and outputs into terminal
	std::cout << gladLoadGLLoader(SDL_GL_GetProcAddress) << std::endl;


	//load an image
	string fileName;
	cin >> fileName;
	GLuint texture = LoadImage(fileName.c_str());
	glBindTexture(GL_TEXTURE_2D, texture);
	
	//set window to fullscreen
	SDL_SetWindowFullscreen(window, 1);
	//change window size to image size
	SDL_SetWindowSize(window, w, h);
	//tell opengl the new window size
	// 0, 0 is to say the top left corner is at 0 pixels
	glViewport(0, 0, w, h);


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


		glEnable(GL_TEXTURE_2D);
		//clears screen to ^^ color
		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_QUADS); //start drawing a rectangle
		glTexCoord2f(0, 0);
		glVertex2f(-1, -1);
		glTexCoord2f(1, 0);
		glVertex2f(1, -1);
		glTexCoord2f(1, 1);
		glVertex2f(1, 1);
		glTexCoord2f(0, 1);
		glVertex2f(-1, 1);
		glEnd();

		//switches back buffer to front. you write to back then switch to front.
		SDL_GL_SwapWindow(window);
	}
	//closes the program
	return 0;
}
