#include <iostream>
#include <Eigen>  // Lib para álgebra linear
#include <SDL.h>  // Lib gráfica

// Estrutura de dados
#include "Tensor.h"
#include "Ray.h"
#include "PontualSource.h"
#include "Sphere.h"
#include "Canvas.h"
#include "Object.h"

int main(int argc, char* argv[]) {
	// Checando a inicialização do SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
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
	SDL_Window* window = SDL_CreateWindow(
		"Esfera",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		SDL_Log("Não foi possível criar a janela");
		SDL_Quit();
		return 1;
	}

	// Criação do objeto renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		SDL_Log("Não foi possível criar o renderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	// Canvas e cena
	Canvas canvas(windowDistance, windowWidth, windowHeight, numLines, numColumns);
	Scene scene;

	// OBJETOS
	double lowerBodyRadius = 100;
	Eigen::Vector3d lowerBodyCenter(0, -100, -1100);
	Eigen::Vector3d lowerBodyKDif(255, 255, 255);
	Eigen::Vector3d lowerBodyKEsp(0, 0, 0);
	Object* lowerBody = new Sphere(lowerBodyRadius, lowerBodyCenter, lowerBodyKDif, lowerBodyKEsp, 0);

	double upperBodyRadius = 75;
	Eigen::Vector3d upperBodyCenter(0, 35, -1100);
	Eigen::Vector3d upperBodyKDif(255, 255, 255);
	Eigen::Vector3d upperBodyKEsp(0, 0, 0);
	Object* upperBody = new Sphere(upperBodyRadius, upperBodyCenter, upperBodyKDif, upperBodyKEsp, 0);

	double leftEyeRadius = 20;
	Eigen::Vector3d leftEyeCenter(-35, 55, -1045);
	Eigen::Vector3d leftEyeKDif(0, 100, 255);
	Eigen::Vector3d leftEyeKEsp(80, 80, 80);
	Object* leftEye = new Sphere(leftEyeRadius, leftEyeCenter, leftEyeKDif, leftEyeKEsp, 1);

	double rightEyeRadius = 20;
	Eigen::Vector3d rightEyeCenter(35, 55, -1045);
	Eigen::Vector3d rightEyeKDif(0, 100, 255);
	Eigen::Vector3d rightEyeKEsp(80, 80, 80);
	Object* rightEye = new Sphere(rightEyeRadius, rightEyeCenter, rightEyeKDif, rightEyeKEsp, 2);

	double upperRightMouthRadius = 10;
	Eigen::Vector3d upperRightMouthCenter(-32, 15, -1005);
	Eigen::Vector3d upperRightMouthKDif(100, 50, 0);
	Eigen::Vector3d upperRightMouthKEsp(0, 0, 0);
	Object* upperRightMouth = new Sphere(upperRightMouthRadius, upperRightMouthCenter, upperRightMouthKDif, upperRightMouthKEsp, 0);

	double rightMouthRadius = 10;
	Eigen::Vector3d rightMouthCenter(-12, 5, -1005);
	Eigen::Vector3d rightMouthKDif(100, 50, 0);
	Eigen::Vector3d rightMouthKEsp(0, 0, 0);
	Object* rightMouth = new Sphere(rightMouthRadius, rightMouthCenter, rightMouthKDif, rightMouthKEsp, 0);

	double leftMouthRadius = 10;
	Eigen::Vector3d leftMouthCenter(12, 5, -1005);
	Eigen::Vector3d leftMouthKDif(100, 50, 0);
	Eigen::Vector3d leftMouthKEsp(0, 0, 0);
	Object* leftMouth = new Sphere(leftMouthRadius, leftMouthCenter, leftMouthKDif, leftMouthKEsp, 0);

	double upperLeftMouthRadius = 10;
	Eigen::Vector3d upperLeftMouthCenter(32, 15, -1005);
	Eigen::Vector3d upperLeftMouthKDif(100, 50, 0);
	Eigen::Vector3d upperLeftMouthKEsp(0, 0, 0);
	Object* upperLeftMouth = new Sphere(upperLeftMouthRadius, upperLeftMouthCenter, upperLeftMouthKDif, upperLeftMouthKEsp, 0);

	scene.addObject(lowerBody);
	scene.addObject(upperBody);
	scene.addObject(leftEye);
	scene.addObject(rightEye);
	scene.addObject(upperRightMouth);
	scene.addObject(upperLeftMouth);
	scene.addObject(rightMouth);
	scene.addObject(leftMouth);

	// Luz
	Eigen::Vector3d intensity(0.7, 0.7, 0.7);
	Eigen::Vector3d sourceOrigin(-500, 500, 0);
	PontualSource source(sourceOrigin, intensity);

	// Display
	Tensor display = canvas.raycast(origin, scene, source);
	display.normalize();

	// Loop principal
	bool isRunning = true;
	SDL_Event event;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
		}

		SDL_RenderClear(renderer);

		for (int i = 0; i < numLines; i++) {
			for (int j = 0; j < numColumns; j++) {
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