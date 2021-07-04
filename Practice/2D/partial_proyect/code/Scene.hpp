/**
* @file Scene.hpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 14 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que lleva todos los objetos de la escena, sus updates, y el ciclo del juego
**/

#include <ciso646>
#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Input_Task.hpp"
#include "Render_Task.hpp"
#include "Entity.hpp"
#include "MyListener.hpp"
#include "Constants.h"
#include "ParticleSystemManager.hpp"


namespace Engine
{
	class Scene
	{
	public:
		const float target_fps = 60.f;                     // Cuántos fotogramas por segundo se busca conseguir
		const float target_time = 1.f / target_fps;        // Duración en segundos de un fotograma a la tasa deseada

		float delta_time = target_time;                    // Previsión de la duración del fotograma actual
		bool  exit;										   // Booleano para que no se salga del ciclo de juego

		Clock m_clock;									   //Timer que controla el tiempo del juego
		Clock m_timer;									   //Timer para las partículas

		///Referencia al Render Task
		Render_Task tr;				
		///Referencia al Input Task
		Input_Task * it;
		///Referencia a las constantes
		Constants constants;
		///Referencia al sistema de partículas
		ParticleSystemManager* m_VFXManager;

		///Entidades
		#pragma region Entidades
		//Bordes
		Entity LimitBottomRight;
		Entity LimitBottomLeft;
		Entity LimitTopRight;
		Entity LimitTopLeft;

		///Circulo - Main Character
		Entity circle;

		//Platafroma desplazable
		Entity Platform_Movable_01;
		Entity Platform_Movable_02;

		//Suelos
		Entity floor;
		Entity floor_Second_Level;
		Entity floor_Second_Level_Part_2;
		Entity floor_Second_Level_Part_3;

		//Rampas
		int32 countRamp = 4;
		Entity RampDown;
		Entity Ramp_Up;
		Entity Ramp_Win_Left;
		Entity Ramp_Win_Right;

		//Pistones
		Entity piston_01;
		Entity piston_01_pusher;
		Entity trigger_piston_01;
		Entity springTrap_Down;
		Entity springTrap_Up;

		//Aspas
		Entity aspa_01;
		Entity aspa_02;

		Entity aspa_01_02;
		Entity aspa_02_02;

		//Trigger
		Entity trigger_System_Particle;


		#pragma endregion

		///Joints

		#pragma region Joints
		b2RevoluteJoint* joint_def;
		b2RevoluteJoint* wall_floor_2;
		b2RevoluteJoint* particle_collider;
		#pragma endregion

		//Medidas de la ventana
		int window_height;
		int window_width;

		const float physics_to_graphics_scale = 100.f;      // Escala para pasar de unidades de física a unidades de gráficos

		// Se crea y se configura la escena física (de 8 x 6 metros):
		b2World physics_world{ b2Vec2{ 0, -10.f } };

		///Booleano para las plataformas y pistones, y de esta manera llamar a sus updates
		
		#pragma region Booleanos para el funcionamiento de los mecanismos de la escena
		bool colision_platform_01;
		bool colision_platform_02;

		bool start_piston_01;
		bool start_piston_02;
		#pragma endregion

		///Booleano para resetear la escena
		bool restart_Scene;

		bool canJump;

	public:
		///Constructor por defecto
		Scene(RenderWindow&, const int, const int);

		//Update de la escena, donde se encuentra todo el ciclo
		void Update(RenderWindow&);
	};
}


