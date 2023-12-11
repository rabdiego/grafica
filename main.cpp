#include <iostream>
#include <Eigen>  // Lib para �lgebra linear
#include <SDL.h>  // Lib gr�fica
#include <SDL_image.h>  // Lib texturas
#include <ctime>

// Estrutura de dados
#include "AmbientSource.h"
#include "Camera.h"
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
	int numColumns = 500;
	int numLines = 500;

	// Cria��o da janela
	SDL_Window* window = SDL_CreateWindow
	(
		"Cena",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		numColumns,
		numLines,
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
	Camera* camera = new Camera
	(
		Eigen::Vector3d(-160, 100, -100),
		Eigen::Vector3d(0, 0, -230),
		Eigen::Vector3d(0, 1, 0)
	);
	scene.setCamera(camera);

	// Texturas

	SDL_Surface* springTexture = IMG_Load("spring.png");
	SDL_Surface* summerTexture = IMG_Load("summer.png");
	SDL_Surface* autumnTexture = IMG_Load("fall.png");
	SDL_Surface* winterTexture = IMG_Load("winter.png");

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

		Object* skyLeft = new Plane
		(
			NULL,
			Eigen::Vector3d(1, 0, 0),
			Eigen::Vector3d(-1000, 0, 0),
			Eigen::Vector3d(32, 116, 219),
			Eigen::Vector3d(32, 116, 219),
			Eigen::Vector3d(0, 0, 0),
			0
		);

		Object* skyRight = new Plane
		(
			NULL,
			Eigen::Vector3d(-1, 0, 0),
			Eigen::Vector3d(1000, 0, 0),
			Eigen::Vector3d(32, 116, 219),
			Eigen::Vector3d(32, 116, 219),
			Eigen::Vector3d(0, 0, 0),
			0
		);

		Object* skyTop = new Plane
		(
			NULL,
			Eigen::Vector3d(0, -1, 0),
			Eigen::Vector3d(0, 1000, 0),
			Eigen::Vector3d(32, 116, 219),
			Eigen::Vector3d(32, 116, 219),
			Eigen::Vector3d(0, 0, 0),
			0
		);

		Object* grass = new Plane
		(
			summerTexture,
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
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(0, 0, 0),
			0
		);

		Object* oakLeavesTop1 = new Sphere
		(
			22,
			Eigen::Vector3d(130, 0, -230),
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(12, 242, 0),
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
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(0, 0, 0),
			0
		);

		Object* oakLeavesTop2 = new Sphere
		(
			22,
			Eigen::Vector3d(130, 0, -300),
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(12, 242, 0),
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
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(0, 0, 0),
			0
		);

		Object* oakLeavesTop3 = new Sphere
		(
			22,
			Eigen::Vector3d(130, 0, -160),
			Eigen::Vector3d(12, 242, 0),
			Eigen::Vector3d(12, 242, 0),
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

	/* Adicionando objetos a cena */

		scene.addObject(sky);
		scene.addObject(skyLeft);
		scene.addObject(skyRight);
		scene.addObject(skyTop);
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
	
	/** Fontes de luz
	 * 
	 * Pontual e Ambiente
	*/
		Eigen::Vector3d pontualIntensity(0.7, 0.7, 0.7);
		Eigen::Vector3d pontualOrigin(-30, 60, 0);
		LightSource* pontual = new PontualSource(pontualOrigin, pontualIntensity);

		Eigen::Vector3d ambientIntensity(0.3, 0.3, 0.3);
		LightSource* ambient = new AmbientSource(ambientIntensity);

		scene.addSource(pontual);
		scene.addSource(ambient);

	/* Display */
		std::cout << "Renderiza��o iniciada.\n";
		time_t startTime = time(NULL);
		Tensor display = canvas.raycast(origin, scene, true);
		time_t renderTime = time(NULL);
		std::cout << "Tempo para renderizar objetos: " << renderTime - startTime << std::endl;
		display.normalize();

	
	/* Loop principal */
		bool isRunning = true;
		SDL_Event event;
		double mouseX, mouseY, mouseX2, mouseY2;
		int season = 1;

		// iteracao da janela
		while (isRunning)
		{
			// listeng pro evento(pick)
			while (SDL_PollEvent(&event))
			{
				// encerra a exibição
				if (event.type == SDL_QUIT)
				{
					isRunning = false;
				}
				// clique do mouse
				else if (event.type == SDL_MOUSEBUTTONDOWN)
				{
					// coordenadas do evento, onde o mouse clicou
					mouseX = (double) event.motion.x;
					mouseY = (double) event.motion.y;

					mouseY2 = canvas.jYMax - mouseY * canvas.deltaY - canvas.deltaY / 2;
					mouseX2 = canvas.jXMin + mouseX * canvas.deltaX + canvas.deltaX / 2;

					// raio do pick
					Ray pickRay
					(
						origin,
						Eigen::Vector3d(mouseX2, mouseY2, -canvas.windowDistance)
					);

					// Qual botao foi interceptado pelo raio do pick
					if (springButton->hasInterceptedRay(pickRay) < 0)
					{
						if (season != 0)
						{
							// limpando objetos da cena
							scene.cleanObjects();

							// setando cenario para primavera
							Object* grass = new Plane
							(
								springTexture,
								Eigen::Vector3d(0, 1, 0),
								Eigen::Vector3d(0, -100, 0),
								Eigen::Vector3d(0, 0, 0),
								Eigen::Vector3d(100, 100, 100),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom1 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -230),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop1 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -230),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom2 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -300),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop2 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -300),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom3 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -160),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop3 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -160),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(255, 72, 132),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							scene.addObject(grass);
							scene.addObject(oakLeavesBottom1);
							scene.addObject(oakLeavesBottom2);
							scene.addObject(oakLeavesBottom3);
							scene.addObject(oakLeavesTop1);
							scene.addObject(oakLeavesTop2);
							scene.addObject(oakLeavesTop3);
							scene.convertObjectsToCamera(false);

							scene.addObject(sky);
							scene.addObject(skyLeft);
							scene.addObject(skyRight);
							scene.addObject(skyTop);

							scene.addObject(pineLeaves1);
							scene.addObject(pineLeaves2);
							scene.addObject(pineLeaves3);
							scene.addObject(pineLog1);
							scene.addObject(pineLog2);
							scene.addObject(pineLog3);

							scene.addObject(oakLog1);
							scene.addObject(oakLog2);
							scene.addObject(oakLog3);

							scene.addHitBox(tableHitBox);
							scene.addHitBox(leg1HitBox);
							scene.addHitBox(leg2HitBox);
							scene.addHitBox(leg3HitBox);
							scene.addHitBox(leg4HitBox);

							scene.addObject(springButton);
							scene.addObject(summerButton);
							scene.addObject(autumnButton);
							scene.addObject(winterButton);

							std::cout << "Primavera iniciada\n";
							startTime = time(NULL);
							display = canvas.raycast(origin, scene, false);
							renderTime = time(NULL);
							std::cout << "Tempo para renderizar objetos: " << renderTime - startTime << std::endl;
							display.normalize();
							season = 0;
						}
						else
						{
							std::cout << "J� est� na primavera" << std::endl;
						}
					}
					else if (summerButton->hasInterceptedRay(pickRay) < 0)
					{
						if (season != 1)
						{
							// limpando objetos da cena
							scene.cleanObjects();

							// setando cenario para verão
							Object* grass = new Plane
							(
								summerTexture,
								Eigen::Vector3d(0, 1, 0),
								Eigen::Vector3d(0, -100, 0),
								Eigen::Vector3d(0, 0, 0),
								Eigen::Vector3d(100, 100, 100),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom1 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -230),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop1 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -230),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom2 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -300),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop2 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -300),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom3 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -160),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop3 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -160),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(12, 242, 0),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							scene.addObject(grass);
							scene.addObject(oakLeavesBottom1);
							scene.addObject(oakLeavesBottom2);
							scene.addObject(oakLeavesBottom3);
							scene.addObject(oakLeavesTop1);
							scene.addObject(oakLeavesTop2);
							scene.addObject(oakLeavesTop3);
							scene.convertObjectsToCamera(false);

							scene.addObject(sky);
							scene.addObject(skyLeft);
							scene.addObject(skyRight);
							scene.addObject(skyTop);

							scene.addObject(pineLeaves1);
							scene.addObject(pineLeaves2);
							scene.addObject(pineLeaves3);
							scene.addObject(pineLog1);
							scene.addObject(pineLog2);
							scene.addObject(pineLog3);

							scene.addObject(oakLog1);
							scene.addObject(oakLog2);
							scene.addObject(oakLog3);

							scene.addHitBox(tableHitBox);
							scene.addHitBox(leg1HitBox);
							scene.addHitBox(leg2HitBox);
							scene.addHitBox(leg3HitBox);
							scene.addHitBox(leg4HitBox);

							scene.addObject(springButton);
							scene.addObject(summerButton);
							scene.addObject(autumnButton);
							scene.addObject(winterButton);

							std::cout << "Ver�o iniciado\n";
							startTime = time(NULL);
							display = canvas.raycast(origin, scene, false);
							renderTime = time(NULL);
							std::cout << "Tempo para renderizar objetos: " << renderTime - startTime << std::endl;
							display.normalize();
							season = 1;
						}
						else
						{
							std::cout << "J� est� no ver�o" << std::endl;
						}
					}
					else if (autumnButton->hasInterceptedRay(pickRay) < 0)
					{
						if (season != 2)
						{
							// limpando objetos da cena
							scene.cleanObjects();

							// setando cenario para outuno
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

							scene.addObject(grass);
							scene.addObject(oakLeavesBottom1);
							scene.addObject(oakLeavesBottom2);
							scene.addObject(oakLeavesBottom3);
							scene.addObject(oakLeavesTop1);
							scene.addObject(oakLeavesTop2);
							scene.addObject(oakLeavesTop3);
							scene.convertObjectsToCamera(false);

							scene.addObject(sky);
							scene.addObject(skyLeft);
							scene.addObject(skyRight);
							scene.addObject(skyTop);

							scene.addObject(pineLeaves1);
							scene.addObject(pineLeaves2);
							scene.addObject(pineLeaves3);
							scene.addObject(pineLog1);
							scene.addObject(pineLog2);
							scene.addObject(pineLog3);

							scene.addObject(oakLog1);
							scene.addObject(oakLog2);
							scene.addObject(oakLog3);

							scene.addHitBox(tableHitBox);
							scene.addHitBox(leg1HitBox);
							scene.addHitBox(leg2HitBox);
							scene.addHitBox(leg3HitBox);
							scene.addHitBox(leg4HitBox);

							scene.addObject(springButton);
							scene.addObject(summerButton);
							scene.addObject(autumnButton);
							scene.addObject(winterButton);

							std::cout << "Outono iniciado\n";
							startTime = time(NULL);
							display = canvas.raycast(origin, scene, false);
							renderTime = time(NULL);
							std::cout << "Tempo para renderizar objetos: " << renderTime - startTime << std::endl;
							display.normalize();
							season = 2;
						}
						else
						{
							std::cout << "J� est� no outono" << std::endl;
						}
					}
					else if (winterButton->hasInterceptedRay(pickRay) < 0)
					{
						if (season != 3)
						{
							// limpando elementos da cena
							scene.cleanObjects();

							// setando objetos para inverno
							Object* grass = new Plane
							(
								winterTexture,
								Eigen::Vector3d(0, 1, 0),
								Eigen::Vector3d(0, -100, 0),
								Eigen::Vector3d(0, 0, 0),
								Eigen::Vector3d(100, 100, 100),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom1 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -230),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop1 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -230),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom2 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -300),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop2 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -300),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesBottom3 = new Sphere
							(
								30,
								Eigen::Vector3d(130, -30, -160),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							Object* oakLeavesTop3 = new Sphere
							(
								22,
								Eigen::Vector3d(130, 0, -160),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(255, 255, 255),
								Eigen::Vector3d(0, 0, 0),
								0
							);

							scene.addObject(grass);
							scene.addObject(oakLeavesBottom1);
							scene.addObject(oakLeavesBottom2);
							scene.addObject(oakLeavesBottom3);
							scene.addObject(oakLeavesTop1);
							scene.addObject(oakLeavesTop2);
							scene.addObject(oakLeavesTop3);

							scene.addObject(rogerBody);
							scene.addObject(rogerHead);
							scene.addObject(rogerLeftEye);
							scene.addObject(rogerRightEye);

							scene.convertObjectsToCamera(false);

							scene.addObject(sky);
							scene.addObject(skyLeft);
							scene.addObject(skyRight);
							scene.addObject(skyTop);

							scene.addObject(pineLeaves1);
							scene.addObject(pineLeaves2);
							scene.addObject(pineLeaves3);
							scene.addObject(pineLog1);
							scene.addObject(pineLog2);
							scene.addObject(pineLog3);

							scene.addObject(oakLog1);
							scene.addObject(oakLog2);
							scene.addObject(oakLog3);

							scene.addHitBox(tableHitBox);
							scene.addHitBox(leg1HitBox);
							scene.addHitBox(leg2HitBox);
							scene.addHitBox(leg3HitBox);
							scene.addHitBox(leg4HitBox);

							scene.addObject(springButton);
							scene.addObject(summerButton);
							scene.addObject(autumnButton);
							scene.addObject(winterButton);

							std::cout << "Inverno iniciado\n";
							startTime = time(NULL);
							display = canvas.raycast(origin, scene, false);
							renderTime = time(NULL);
							std::cout << "Tempo para renderizar objetos: " << renderTime - startTime << std::endl;
							display.normalize();
							season = 3;
						}
						else
						{
							std::cout << "J� est� no inverno" << std::endl;
						}
					}
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

	/* Limpando */
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}