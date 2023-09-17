#include <iostream>
#include <Eigen>  // Lib para álgebra linear
#include <SDL.h>  // Lib gráfica

// Estrutura de dados
#include "Tensor.h"
#include "Ray.h"
#include "PontualSource.h"
#include "Sphere.h"
#include "Canvas.h"

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_Log("Não foi possível inicializar o SDL");
		return 1;
	}

	Eigen::Vector3d origin(0, 0, 0);

	int windowDistance = 1000;
	int windowWidth = 800;
	int windowHeight = 600;
	int numColumns = 800;
	int numLines = 600;

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

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		SDL_Log("Não foi possível criar o renderer");
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	Canvas canvas(windowDistance, windowWidth, windowHeight, numLines, numColumns);

	double sphereRadius = 200;
	Eigen::Vector3d sphereCenter(0, 0, -(windowDistance + sphereRadius));
	Eigen::Vector3d kDif(197, 0, 250);
	Eigen::Vector3d kEsp(255, 255, 255);
	Sphere sphere(sphereRadius, sphereCenter, kDif, kEsp);

	Eigen::Vector3d intensity(0.7, 0.7, 0.7);
	Eigen::Vector3d sourceOrigin(0, 5, 0);
	PontualSource source(sourceOrigin, intensity);

	Tensor display = canvas.raycast(origin, sphere, source);
	display.normalize();

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