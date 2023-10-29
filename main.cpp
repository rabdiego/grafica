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

	double angle = 0.4;
	Eigen::Vector3d centerBase(-200, -75, -1100);
	Eigen::Vector3d vertex(-200, 75, -1100);
	Eigen::Vector3d coneKAmbient(0.2, 0.5, 0.25);
	Eigen::Vector3d coneKDif(0.2, 0.5, 0.25);
	Eigen::Vector3d coneKEsp(0, 0, 0);
	int coneSpecularIndex = 0;
	Object* cone = new Cone(angle, centerBase, vertex, coneKAmbient, coneKDif, coneKEsp, coneSpecularIndex);

	double woodRadius = 20;
	Eigen::Vector3d woodCenterBase(-200, -200, -1100);
	Eigen::Vector3d woodCenterTop(-200, -75, -1100);
	Eigen::Vector3d woodKAmbient(0.62, 0.33, 0.07);
	Eigen::Vector3d woodKDif(0.62, 0.33, 0.07);
	Eigen::Vector3d woodKEsp(0, 0, 0);
	Object* wood = new Cilinder(woodRadius, woodCenterBase, woodCenterTop, woodKAmbient, woodKDif, woodKEsp, 0);

	double angle2 = 0.4;
	Eigen::Vector3d centerBase2(200, -35, -1200);
	Eigen::Vector3d vertex2(200, 150, -1200);
	Eigen::Vector3d coneKAmbient2(0.2, 0.5, 0.25);
	Eigen::Vector3d coneKDif2(0.2, 0.5, 0.25);
	Eigen::Vector3d coneKEsp2(0, 0, 0);
	int coneSpecularIndex2 = 0;
	Object* cone2 = new Cone(angle2, centerBase2, vertex2, coneKAmbient2, coneKDif2, coneKEsp2, coneSpecularIndex2);

	double woodRadius2 = 30;
	Eigen::Vector3d woodCenterBase2(200, -200, -1200);
	Eigen::Vector3d woodCenterTop2(200, -35, -1200);
	Eigen::Vector3d woodKAmbient2(0.62, 0.33, 0.07);
	Eigen::Vector3d woodKDif2(0.62, 0.33, 0.07);
	Eigen::Vector3d woodKEsp2(0, 0, 0);
	Object* wood2 = new Cilinder(woodRadius2, woodCenterBase2, woodCenterTop2, woodKAmbient2, woodKDif2, woodKEsp2, 0);

	double bodyRadius = 83.3;
	Eigen::Vector3d bodyCenter(0, -116.7, -1100);
	Eigen::Vector3d bodyKAmbient(1, 1, 1);
	Eigen::Vector3d bodyKDif(1, 1, 1);
	Eigen::Vector3d bodyKEsp(0, 0, 0);
	Object* body = new Sphere(bodyRadius, bodyCenter, bodyKAmbient, bodyKDif, bodyKEsp, 0);

	double headRadius = 62.5;
	Eigen::Vector3d headCenter(0, -4.23, -1100);
	Eigen::Vector3d headKAmbient(1, 1, 1);
	Eigen::Vector3d headKDif(1, 1, 1);
	Eigen::Vector3d headKEsp(0, 0, 0);
	Object* head = new Sphere(headRadius, headCenter, headKAmbient, headKDif, headKEsp, 0);

	double leftEyeRadius = 16.7;
	Eigen::Vector3d leftEyeCenter(-29.17, 12.4, -1045);
	Eigen::Vector3d leftEyeKAmbient(0, 0.4, 1);
	Eigen::Vector3d leftEyeKDif(0, 0.4, 1);
	Eigen::Vector3d leftEyeKEsp(0.3, 0.3, 0.3);
	Object* leftEye = new Sphere(leftEyeRadius, leftEyeCenter, leftEyeKAmbient, leftEyeKDif, leftEyeKEsp, 4);

	double rightEyeRadius = 16.7;
	Eigen::Vector3d rightEyeCenter(29.17, 12.4, -1045);
	Eigen::Vector3d rightEyeKAmbient(0, 0.4, 1);
	Eigen::Vector3d rightEyeKDif(0, 0.4, 1);
	Eigen::Vector3d rightEyeKEsp(0.3, 0.3, 0.3);
	Object* rightEye = new Sphere(rightEyeRadius, rightEyeCenter, rightEyeKAmbient, rightEyeKDif, rightEyeKEsp, 4);

	double upperRightMouthRadius = 8.3;
	Eigen::Vector3d upperRightMouthCenter(-26.7, -20.9, -1005);
	Eigen::Vector3d upperRightMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d upperRightMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d upperRightMouthKEsp(0, 0, 0);
	Object* upperRightMouth = new Sphere(upperRightMouthRadius, upperRightMouthCenter, upperRightMouthKAmbient, upperRightMouthKDif, upperRightMouthKEsp, 0);

	double rightMouthRadius = 8.3;
	Eigen::Vector3d rightMouthCenter(-10, -29.23, -1005);
	Eigen::Vector3d rightMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d rightMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d rightMouthKEsp(0, 0, 0);
	Object* rightMouth = new Sphere(rightMouthRadius, rightMouthCenter, rightMouthKAmbient, rightMouthKDif, rightMouthKEsp, 0);

	double leftMouthRadius = 8.3;
	Eigen::Vector3d leftMouthCenter(10, -29.23, -1005);
	Eigen::Vector3d leftMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d leftMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d leftMouthKEsp(0, 0, 0);
	Object* leftMouth = new Sphere(leftMouthRadius, leftMouthCenter, leftMouthKAmbient, leftMouthKDif, leftMouthKEsp, 0);

	double upperLeftMouthRadius = 8.3;
	Eigen::Vector3d upperLeftMouthCenter(26.7, -20.9, -1005);
	Eigen::Vector3d upperLeftMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d upperLeftMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d upperLeftMouthKEsp(0, 0, 0);
	Object* upperLeftMouth = new Sphere(upperLeftMouthRadius, upperLeftMouthCenter, upperLeftMouthKAmbient, upperLeftMouthKDif, upperLeftMouthKEsp, 0);

	double hatBaseRadius = 80;
	Eigen::Vector3d hatBaseCenterBase(0, 30.6, -1100);
	Eigen::Vector3d hatBaseCenterTop(-2.352, 42.368, -1100);
	Eigen::Vector3d hatBaseKAmbient(0.2, 0.2, 0.2);
	Eigen::Vector3d hatBaseKDif(0.2, 0.2, 0.2);
	Eigen::Vector3d hatBaseKEsp(0, 0, 0);
	Object* hatBase = new Cilinder(hatBaseRadius, hatBaseCenterBase, hatBaseCenterTop, hatBaseKAmbient, hatBaseKDif, hatBaseKEsp, 0);

	double hatTopRadius = 64;
	Eigen::Vector3d hatTopCenterBase(-2.352, 42.368, -1100);
	Eigen::Vector3d hatTopCenterTop(-11.768, 89.432, -1100);
	Eigen::Vector3d hatTopKAmbient(0.2, 0.2, 0.2);
	Eigen::Vector3d hatTopKDif(0.2, 0.2, 0.2);
	Eigen::Vector3d hatTopKEsp(0, 0, 0);
	Object* hatTop = new Cilinder(hatTopRadius, hatTopCenterBase, hatTopCenterTop, hatTopKAmbient, hatTopKDif, hatTopKEsp, 0);

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

	scene.addObject(body);
	scene.addObject(head);
	scene.addObject(leftEye);
	scene.addObject(rightEye);
	scene.addObject(upperLeftMouth);
	scene.addObject(upperRightMouth);
	scene.addObject(leftMouth);
	scene.addObject(rightMouth);
	scene.addObject(hatTop);
	scene.addObject(hatBase);
	scene.addObject(cone);
	scene.addObject(wood);
	scene.addObject(cone2);
	scene.addObject(wood2);
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