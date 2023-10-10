#include <iostream>
#include <Eigen>  // Lib para álgebra linear
#include <SDL.h>  // Lib gráfica

// Estrutura de dados
#include "AmbientSource.h"
#include "Canvas.h"
#include "LightSource.h"
#include "Object.h"
#include "Plane.h"
#include "PontualSource.h"
#include "Ray.h"
#include "Sphere.h"
#include "Tensor.h"

int main(int argc, char* argv[])
{
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
	int windowWidth = 600;
	int windowHeight = 600;
	int numColumns = 600;
	int numLines = 600;

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

	double bodyRadius = 100;
	Eigen::Vector3d bodyCenter(0, -100, -1100);
	Eigen::Vector3d bodyKAmbient(1, 1, 1);
	Eigen::Vector3d bodyKDif(1, 1, 1);
	Eigen::Vector3d bodyKEsp(0, 0, 0);
	Object* body = new Sphere(bodyRadius, bodyCenter, bodyKAmbient, bodyKDif, bodyKEsp, 0);

	double headRadius = 75;
	Eigen::Vector3d headCenter(0, 35, -1100);
	Eigen::Vector3d headKAmbient(1, 1, 1);
	Eigen::Vector3d headKDif(1, 1, 1);
	Eigen::Vector3d headKEsp(0, 0, 0);
	Object* head = new Sphere(headRadius, headCenter, headKAmbient, headKDif, headKEsp, 0);

	double leftEyeRadius = 20;
	Eigen::Vector3d leftEyeCenter(-35, 55, -1045);
	Eigen::Vector3d leftEyeKAmbient(0, 0.4, 1);
	Eigen::Vector3d leftEyeKDif(0, 0.4, 1);
	Eigen::Vector3d leftEyeKEsp(0.3, 0.3, 0.3);
	Object* leftEye = new Sphere(leftEyeRadius, leftEyeCenter, leftEyeKAmbient, leftEyeKDif, leftEyeKEsp, 1);

	double rightEyeRadius = 20;
	Eigen::Vector3d rightEyeCenter(35, 55, -1045);
	Eigen::Vector3d rightEyeKAmbient(0, 0.4, 1);
	Eigen::Vector3d rightEyeKDif(0, 0.4, 1);
	Eigen::Vector3d rightEyeKEsp(0.3, 0.3, 0.3);
	Object* rightEye = new Sphere(rightEyeRadius, rightEyeCenter, rightEyeKAmbient, rightEyeKDif, rightEyeKEsp, 2);
	
	double upperRightMouthRadius = 10;
	Eigen::Vector3d upperRightMouthCenter(-32, 15, -1005);
	Eigen::Vector3d upperRightMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d upperRightMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d upperRightMouthKEsp(0, 0, 0);
	Object* upperRightMouth = new Sphere(upperRightMouthRadius, upperRightMouthCenter, upperRightMouthKAmbient, upperRightMouthKDif, upperRightMouthKEsp, 0);

	double rightMouthRadius = 10;
	Eigen::Vector3d rightMouthCenter(-12, 5, -1005);
	Eigen::Vector3d rightMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d rightMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d rightMouthKEsp(0, 0, 0);
	Object* rightMouth = new Sphere(rightMouthRadius, rightMouthCenter, rightMouthKAmbient, rightMouthKDif, rightMouthKEsp, 0);

	double leftMouthRadius = 10;
	Eigen::Vector3d leftMouthCenter(12, 5, -1005);
	Eigen::Vector3d leftMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d leftMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d leftMouthKEsp(0, 0, 0);
	Object* leftMouth = new Sphere(leftMouthRadius, leftMouthCenter, leftMouthKAmbient, leftMouthKDif, leftMouthKEsp, 0);

	double upperLeftMouthRadius = 10;
	Eigen::Vector3d upperLeftMouthCenter(32, 15, -1005);
	Eigen::Vector3d upperLeftMouthKAmbient(0.4, 0.2, 0);
	Eigen::Vector3d upperLeftMouthKDif(0.4, 0.2, 0);
	Eigen::Vector3d upperLeftMouthKEsp(0, 0, 0);
	Object* upperLeftMouth = new Sphere(upperLeftMouthRadius, upperLeftMouthCenter, upperLeftMouthKAmbient, upperLeftMouthKDif, upperLeftMouthKEsp, 0);
	
	scene.addObject(body);
	scene.addObject(head);
	scene.addObject(leftEye);
	scene.addObject(rightEye);
	scene.addObject(upperRightMouth);
	scene.addObject(upperLeftMouth);
	scene.addObject(rightMouth);
	scene.addObject(leftMouth);

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
	Eigen::Vector3d wallKDif(0.3, 0.3, 0.3);
	Eigen::Vector3d wallKEsp(0, 0, 0);
	int wallSpecularIndex = 0;
	Object* wall = new Plane(wallNormal, wallCenter, wallKAmbient, wallKDif, wallKEsp, wallSpecularIndex);

	scene.addObject(floor);
	scene.addObject(wall);

	Eigen::Vector3d pontualIntensity(0.7, 0.7, 0.7);
	Eigen::Vector3d pontualOrigin(-500, 500, 0);
	LightSource* pontual = new PontualSource(pontualOrigin, pontualIntensity);

	Eigen::Vector3d ambientIntensity(0.55, 0.55, 0.55);
	LightSource* ambient = new AmbientSource(ambientIntensity);

	scene.addSource(pontual);
	scene.addSource(ambient);
	

	// Display
	Tensor display = canvas.raycast(origin, scene);
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