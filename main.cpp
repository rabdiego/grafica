#include <iostream>
#include <Eigen>  // Lib para álgebra linear
#include <SDL.h>  // Lib gráfica
#include <SDL_image.h>  // Lib texturas
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
	double numColumns = 500;
	double numLines = 500;

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

	// Texturas

	SDL_Surface* springTexture = IMG_Load("spring.png");
	SDL_Surface* summerTexture = IMG_Load("summer.png");
	SDL_Surface* autumnTexture = IMG_Load("fall.png");
	SDL_Surface* winterTexture = IMG_Load("winter.png");

	// Canvas e cena
	Canvas canvas(windowDistance, windowWidth, windowHeight, numLines, numColumns);
	Scene scene;

	/* Background */
	Object* sky = new Plane
	(
		NULL,
		Eigen::Vector3d(0, 0, 1),
		Eigen::Vector3d(0, 0, -1000),
		Eigen::Vector3d(32, 116, 219),
		Eigen::Vector3d(32, 116, 219),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* grass = new Plane
	(
		autumnTexture,
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(0, -100, 0),
		Eigen::Vector3d(0, 0, 0),
		Eigen::Vector3d(100, 100, 100),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	/* Pinheiros */

	Object* pineLog1 = new Cilinder
	(
		10,
		60,
		Eigen::Vector3d(-130, -100, -230),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* pineLeaves1 = new Cone
	(
		30,
		50,
		Eigen::Vector3d(-130, -40, -230),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(10, 156, 53),
		Eigen::Vector3d(10, 156, 53),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* pineLog2 = new Cilinder
	(
		10,
		60,
		Eigen::Vector3d(-130, -100, -300),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* pineLeaves2 = new Cone
	(
		30,
		50,
		Eigen::Vector3d(-130, -40, -300),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(10, 156, 53),
		Eigen::Vector3d(10, 156, 53),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* pineLog3 = new Cilinder
	(
		10,
		60,
		Eigen::Vector3d(-130, -100, -160),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* pineLeaves3 = new Cone
	(
		30,
		50,
		Eigen::Vector3d(-130, -40, -160),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(10, 156, 53),
		Eigen::Vector3d(10, 156, 53),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	/* Carvalhos */

	Object* oakLog1 = new Cilinder
	(
		10,
		60,
		Eigen::Vector3d(130, -100, -230),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLeavesBottom1 = new Sphere
	(
		30,
		Eigen::Vector3d(130, -30, -230),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLeavesTop1 = new Sphere
	(
		22,
		Eigen::Vector3d(130, 0, -230),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLog2 = new Cilinder
	(
		10,
		60,
		Eigen::Vector3d(130, -100, -300),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLeavesBottom2 = new Sphere
	(
		30,
		Eigen::Vector3d(130, -30, -300),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLeavesTop2 = new Sphere
	(
		22,
		Eigen::Vector3d(130, 0, -300),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLog3 = new Cilinder
	(
		10,
		60,
		Eigen::Vector3d(130, -100, -160),
		Eigen::Vector3d(0, 1, 0),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLeavesBottom3 = new Sphere
	(
		30,
		Eigen::Vector3d(130, -30, -160),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* oakLeavesTop3 = new Sphere
	(
		22,
		Eigen::Vector3d(130, 0, -160),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	/* Mesa */

	Object* table = new Cube
	(
		Eigen::Vector3d(-50, -80, -180),
		100,
		10,
		100,
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0.3, 0.3, 0.3),
		10
	);

	HitBox* tableHitBox = new HitBox
	(
		75,
		Eigen::Vector3d(0, -80, -230),
		Eigen::Vector3d(0, -70, -230)
	);

	Object* leg1 = new Cube
	(
		Eigen::Vector3d(-50, -100, -180),
		10,
		20,
		10,
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0.3, 0.3, 0.3),
		10
	);

	HitBox* leg1HitBox = new HitBox
	(
		8,
		Eigen::Vector3d(-45, -100, -188),
		Eigen::Vector3d(-45, -80, -188)
	);

	Object* leg2 = new Cube
	(
		Eigen::Vector3d(40, -100, -180),
		10,
		20,
		10,
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0.3, 0.3, 0.3),
		10
	);

	HitBox* leg2HitBox = new HitBox
	(
		8,
		Eigen::Vector3d(45, -100, -188),
		Eigen::Vector3d(45, -80, -188)
	);

	Object* leg3 = new Cube
	(
		Eigen::Vector3d(-50, -100, -265),
		10,
		20,
		10,
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0.3, 0.3, 0.3),
		10
	);

	HitBox* leg3HitBox = new HitBox
	(
		8,
		Eigen::Vector3d(-45, -100, -273),
		Eigen::Vector3d(-45, -80, -273)
	);

	Object* leg4 = new Cube
	(
		Eigen::Vector3d(40, -100, -265),
		10,
		20,
		10,
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0.3, 0.3, 0.3),
		10
	);

	HitBox* leg4HitBox = new HitBox
	(
		8,
		Eigen::Vector3d(45, -100, -273),
		Eigen::Vector3d(45, -80, -273)
	);

	tableHitBox->addObject(table);
	leg1HitBox->addObject(leg1);
	leg2HitBox->addObject(leg2);
	leg3HitBox->addObject(leg3);
	leg4HitBox->addObject(leg4);

	/* Roger */

	Object* rogerBody = new Sphere
	(
		30,
		Eigen::Vector3d(0, -70, -380),
		Eigen::Vector3d(255, 255, 255),
		Eigen::Vector3d(255, 255, 255),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* rogerHead = new Sphere
	(
		20,
		Eigen::Vector3d(0, -30, -380),
		Eigen::Vector3d(255, 255, 255),
		Eigen::Vector3d(255, 255, 255),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* rogerLeftEye = new Sphere
	(
		5,
		Eigen::Vector3d(-10, -20, -365),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	Object* rogerRightEye = new Sphere
	(
		5,
		Eigen::Vector3d(10, -20, -365),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(50, 31, 20),
		Eigen::Vector3d(0, 0, 0),
		0
	);

	/* Botões */

	Object* springButton = new Sphere
	(
		10,
		Eigen::Vector3d(-40, -60, -230),
		Eigen::Vector3d(255, 72, 132),
		Eigen::Vector3d(255, 72, 132),
		Eigen::Vector3d(40, 40, 40),
		6
	);

	Object* summerButton = new Sphere
	(
		10,
		Eigen::Vector3d(-13.3, -60, -230),
		Eigen::Vector3d(12, 242, 0),
		Eigen::Vector3d(12, 242, 0),
		Eigen::Vector3d(40, 40, 40),
		6
	);

	Object* autumnButton = new Sphere
	(
		10,
		Eigen::Vector3d(13.3, -60, -230),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(240, 104, 4),
		Eigen::Vector3d(40, 40, 40),
		6
	);

	Object* winterButton = new Sphere
	(
		10,
		Eigen::Vector3d(40, -60, -230),
		Eigen::Vector3d(44, 157, 201),
		Eigen::Vector3d(44, 157, 201),
		Eigen::Vector3d(40, 40, 40),
		6
	);

	
	scene.addObject(sky);
	scene.addObject(grass);

	scene.addObject(pineLeaves1);
	scene.addObject(pineLeaves2);
	scene.addObject(pineLeaves3);
	scene.addObject(pineLog1);
	scene.addObject(pineLog2);
	scene.addObject(pineLog3);
	
	scene.addObject(oakLeavesBottom1);
	scene.addObject(oakLeavesBottom2);
	scene.addObject(oakLeavesBottom3);
	scene.addObject(oakLeavesTop1);
	scene.addObject(oakLeavesTop2);
	scene.addObject(oakLeavesTop3);
	scene.addObject(oakLog1);
	scene.addObject(oakLog2);
	scene.addObject(oakLog3);
	
	scene.addHitBox(tableHitBox);
	scene.addHitBox(leg1HitBox);
	scene.addHitBox(leg2HitBox);
	scene.addHitBox(leg3HitBox);
	scene.addHitBox(leg4HitBox);
	/*
	scene.addObject(rogerBody);
	scene.addObject(rogerHead);
	scene.addObject(rogerLeftEye);
	scene.addObject(rogerRightEye);
	*/
	scene.addObject(springButton);
	scene.addObject(summerButton);
	scene.addObject(autumnButton);
	scene.addObject(winterButton);

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