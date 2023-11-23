#include <iostream>
#include <Eigen>  // Lib para álgebra linear
#include <SDL.h>  // Lib gráfica
#include <ctime>

// Estrutura de dados
#include "AmbientSource.h"
#include "Canvas.h"
#include "Cilinder.h"
#include "Cone.h"
#include "Cube.h"
#include "LightSource.h"
#include "Object.h"
#include "Plane.h"
#include "PontualSource.h"
#include "Ray.h"
#include "Sphere.h"
#include "Tensor.h"
#include "TriangularFace.h"

int main(int argc, char* argv[])
{
	time_t startTime = time(NULL);
	// Checando a inicialização do SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("Não foi possível inicializar o SDL");
		return 1;
	}

	// Posição da câmera
	Eigen::Vector3d origin(0, 0, 0);

	// Parâmetros da janela e canvas
	double windowDistance = 30;
	double windowWidth = 60;
	double windowHeight = 60;
	double numColumns = 300;
	double numLines = 300;

	// Criação da janela
	SDL_Window* window = SDL_CreateWindow
	(
		"Cena",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		(int) numColumns,
		(int) numLines,
		SDL_WINDOW_SHOWN
	);

	if (!window)
	{
		SDL_Log("Não foi possível criar a janela");
		SDL_Quit();
		return 1;
	}

	// Criação do objeto renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("Não foi possível criar o renderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Canvas e cena
	Canvas canvas(windowDistance, windowWidth, windowHeight, numLines, numColumns);
	Scene scene;

	Object* cube = new Cube
	(
		Eigen::Vector3d(-30, -100, -180),
		60,
		60,
		60,
		Eigen::Vector3d(255, 30, 30),
		Eigen::Vector3d(255, 30, 30),
		Eigen::Vector3d(0.3, 0.3, 0.3),
		10
	);

	HitBox* cubeHitBox = new HitBox
	(
		45,
		Eigen::Vector3d(0, -100, -210),
		Eigen::Vector3d(0, -40, -210)
	);

	cube->rotateX(0.78);
	cubeHitBox->addObject(cube);
	scene.addHitBox(cubeHitBox);

	Eigen::Vector3d pontualIntensity(0.7, 0.7, 0.7);
	Eigen::Vector3d pontualOrigin(-30, 60, 0);
	LightSource* pontual = new PontualSource(pontualOrigin, pontualIntensity);

	Eigen::Vector3d ambientIntensity(0.3, 0.3, 0.3);
	LightSource* ambient = new AmbientSource(ambientIntensity);

	scene.addSource(pontual);
	scene.addSource(ambient);

	// Display
	Tensor display = canvas.raycast(origin, scene);
	time_t renderTime = time(NULL);
	std::cout << "Tempo para renderizar objetos: " << renderTime - startTime << std::endl;
	display.normalize();

	// Loop principal
	bool isRunning = true;
	SDL_Event event;

	while (isRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isRunning = false;
			}
		}

		SDL_RenderClear(renderer);

		for (int i = 0; i < numLines; i++)
		{
			for (int j = 0; j < numColumns; j++)
			{
				SDL_SetRenderDrawColor(renderer, (int)display.red(i, j), (int)display.green(i, j), (int)display.blue(i, j), 255);
				SDL_RenderDrawPoint(renderer, j, i);
			}
		}

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}