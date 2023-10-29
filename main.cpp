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

	//Cone(double radius, double angle, Eigen::Vector3d centerBase, Eigen::Vector3d vertex, Eigen::Vector3d kAmbient, Eigen::Vector3d kDif, Eigen::Vector3d kEsp, int specularIndex);

	double angle = 0.4;
	Eigen::Vector3d centerBase(0, -75, -1100);
	Eigen::Vector3d vertex(0, 75, -1100);
	Eigen::Vector3d coneKAmbient(0.2, 0.5, 0.25);
	Eigen::Vector3d coneKDif(0.2, 0.5, 0.25);
	Eigen::Vector3d coneKEsp(0, 0, 0);
	int coneSpecularIndex = 0;
	Object* cone = new Cone(angle, centerBase, vertex, coneKAmbient, coneKDif, coneKEsp, coneSpecularIndex);

	double woodRadius = 20;
	Eigen::Vector3d woodCenterBase(0, -200, -1100);
	Eigen::Vector3d woodCenterTop(0, -75, -1100);
	Eigen::Vector3d woodKAmbient(0.62, 0.33, 0.07);
	Eigen::Vector3d woodKDif(0.62, 0.33, 0.07);
	Eigen::Vector3d woodKEsp(0, 0, 0);
	Object* wood = new Cilinder(woodRadius, woodCenterBase, woodCenterTop, woodKAmbient, woodKDif, woodKEsp, 0);

	Eigen::Vector3d floorNormal(0, 1, 0);
	Eigen::Vector3d floorCenter(0, -200, 0);
	Eigen::Vector3d floorKAmbient(0.2, 0.7, 0.2);
	Eigen::Vector3d floorKDif(0.2, 0.7, 0.2);
	Eigen::Vector3d floorKEsp(0, 0, 0);
	int floorSpecularIndex = 0;
	Object* floor = new Plane(floorNormal, floorCenter, floorKAmbient, floorKDif, floorKEsp, floorSpecularIndex);

	Eigen::Vector3d wallNormal(0, 0, 1);
	Eigen::Vector3d wallCenter(0, 0, -2000);
	Eigen::Vector3d wallKAmbient(0, 0.5, 0.8);
	Eigen::Vector3d wallKDif(0, 0.5, 0.8);
	Eigen::Vector3d wallKEsp(0, 0, 0);
	int wallSpecularIndex = 0;
	Object* wall = new Plane(wallNormal, wallCenter, wallKAmbient, wallKDif, wallKEsp, wallSpecularIndex);

	scene.addObject(cone);
	scene.addObject(wood);
	scene.addObject(floor);
	scene.addObject(wall);

	Eigen::Vector3d pontualIntensity(0.7, 0.7, 0.7);
	Eigen::Vector3d pontualOrigin(-500, 500, 0);
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