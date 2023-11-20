#include <iostream>
#include <Eigen>  // Lib para �lgebra linear
#include <SDL.h>  // Lib gr�fica
#include <ctime>

// Estrutura de dados
#include "AmbientSource.h"
#include "Canvas.h"
#include "Cilinder.h"
#include "Cone.h"
#include "LightSource.h"
#include "Object.h"
#include "Plane.h"
#include "PontualSource.h"
#include "Ray.h"
#include "Sphere.h"
#include "Tensor.h"

int main(int argc, char* argv[])
{
	time_t startTime = time(NULL);
	// Checando a inicializa��o do SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("N�o foi poss�vel inicializar o SDL");
		return 1;
	}

	// Posi��o da c�mera
	Eigen::Vector3d origin(0, 0, 0);

	// Par�metros da janela e canvas
	double windowDistance = 30;
	double windowWidth = 60;
	double windowHeight = 60;
	double numColumns = 500;
	double numLines = 500;

	// Cria��o da janela
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
		SDL_Log("N�o foi poss�vel criar a janela");
		SDL_Quit();
		return 1;
	}

	// Cria��o do objeto renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		SDL_Log("N�o foi poss�vel criar o renderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Canvas e cena
	Canvas canvas(windowDistance, windowWidth, windowHeight, numLines, numColumns);
	Scene scene;

	Object* sky = new Plane
	(
		Eigen::Vector3d(0, 0, 1), 
		Eigen::Vector3d(0, 0, -1000), 
		Eigen::Vector3d(0, 0.3, 0.8),
		Eigen::Vector3d(0, 0.3, 0.8),
		Eigen::Vector3d(0, 0, 0), 
		1
	);

	Object* grass = new Plane
	(
		Eigen::Vector3d(0, 1, 0), 
		Eigen::Vector3d(0, -70, 0), 
		Eigen::Vector3d(0, 0.8, 0.3),
		Eigen::Vector3d(0, 0.8, 0.3),
		Eigen::Vector3d(0, 0, 0), 
		1
	);

	Object* body = new Sphere
	(
		40, 
		Eigen::Vector3d(0, -30, -100), 
		Eigen::Vector3d(1, 1, 1), 
		Eigen::Vector3d(1, 1, 1),
		Eigen::Vector3d(0, 0, 0), 
		1
	);

	body->translate(30, 60, 0);

	Object* head = new Sphere
	(
		30,
		Eigen::Vector3d(0, 30, -100),
		Eigen::Vector3d(1, 1, 1),
		Eigen::Vector3d(1, 1, 1),
		Eigen::Vector3d(0, 0, 0),
		1
	);

	Object* cone = new Cone
	(
		30,
		100,
		Eigen::Vector3d(0, -70, -130),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(0.8, 0.2, 0),
		Eigen::Vector3d(0.8, 0.2, 0),
		Eigen::Vector3d(0.2, 0.2, 0.2),
		3
	);

	Object* cilinder = new Cilinder
	(
		30,
		50,
		Eigen::Vector3d(0, -70, -130),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(0.8, 0.2, 0),
		Eigen::Vector3d(0.8, 0.2, 0),
		Eigen::Vector3d(0.2, 0.2, 0.2),
		3
	);

	cone->translate(-30, 140, 0);

	scene.addObject(cone);

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