#include <iostream>
#include <Eigen>  // Lib para álgebra linear
#include <SDL.h>  // Lib gráfica
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
	// Checando a inicialização do SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("Não foi possível inicializar o SDL");
		return 1;
	}

	// Posição da câmera
	Eigen::Vector3d origin(0, 0, 0);

	// Parâmetros da janela e canvas
	int windowDistance = 1000;
	int windowWidth = 500;
	int windowHeight = 500;
	int numColumns = 500;
	int numLines = 500;

	// Criação da janela
	SDL_Window* window = SDL_CreateWindow
	(
		"Esfera",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
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

	// (Eigen::Vector3d normal, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, double specularIndex)

	Object* wall = new Plane(Eigen::Vector3d(0, 0, 1), Eigen::Vector3d(0, 0, -1600), Eigen::Vector3d(1, 0.8, 0.2),
		Eigen::Vector3d(1, 0.8, 0.2), Eigen::Vector3d(0.2, 0.2, 0.2), 9);

	Object* leftWall = new Plane(Eigen::Vector3d(1, 0, 0.16), Eigen::Vector3d(-500, 0, 0), Eigen::Vector3d(1, 0.8, 0.2),
		Eigen::Vector3d(1, 0.8, 0.2), Eigen::Vector3d(0, 0, 0), 0);

	Object* rightWall = new Plane(Eigen::Vector3d(-1, 0, 0.16), Eigen::Vector3d(500, 0, 0), Eigen::Vector3d(1, 0.8, 0.2),
		Eigen::Vector3d(1, 0.8, 0.2), Eigen::Vector3d(0, 0, 0), 0);

	Object* ceiling = new Plane(Eigen::Vector3d(0, -1, 0), Eigen::Vector3d(0, 200, 0), Eigen::Vector3d(0.2, 0.2, 0.2),
		Eigen::Vector3d(0.2, 0.2, 0.2), Eigen::Vector3d(0, 0, 0), 0);

	Object* floor = new Plane(Eigen::Vector3d(0, 1, 0), Eigen::Vector3d(0, -200, 0), Eigen::Vector3d(0.2, 0.2, 0.2),
		Eigen::Vector3d(0.2, 0.2, 0.2), Eigen::Vector3d(0, 0, 0), 0);

	// (double radius, Eigen::Vector3d center, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)

	Object* sphere = new Sphere(80, Eigen::Vector3d(-30, -120, -1100), Eigen::Vector3d(0.7, 0.2, 0.2), Eigen::Vector3d(0.7, 0.2, 0.2),
		Eigen::Vector3d(0.2, 0.2, 0.2), 9);

	// (double radius, Eigen::Vector3d centerBase, Eigen::Vector3d centerTop, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)

	Object* cilinder = new Cilinder(60, Eigen::Vector3d(120, -200, -1450), Eigen::Vector3d(120, 100, -1450), Eigen::Vector3d(0.2, 0.5, 1), Eigen::Vector3d(0.2, 0.5, 1),
		Eigen::Vector3d(0.2, 0.2, 0.2), 9);

	// (double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex)

	Object* cone = new Cone(0.2, Eigen::Vector3d(-175, -200, -1500), Eigen::Vector3d(-175, 100, -1500), Eigen::Vector3d(0.3, 1, 0.4), Eigen::Vector3d(0.3, 1, 0.4),
		Eigen::Vector3d(0.2, 0.2, 0.2), 9);

	///*
	scene.addObject(wall);
	scene.addObject(floor);
	scene.addObject(leftWall);
	scene.addObject(rightWall);
	scene.addObject(ceiling);
	//*/
	scene.addObject(sphere);
	scene.addObject(cilinder);
	scene.addObject(cone);

	Eigen::Vector3d pontualIntensity(0.7, 0.7, 0.7);
	Eigen::Vector3d pontualOrigin(0, 0, -800);
	LightSource* pontual = new PontualSource(pontualOrigin, pontualIntensity);

	Eigen::Vector3d ambientIntensity(0.3, 0.3, 0.3);
	LightSource* ambient = new AmbientSource(ambientIntensity);

	scene.addSource(pontual);
	scene.addSource(ambient);

	// Display
	std::cout << "oi\n";
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