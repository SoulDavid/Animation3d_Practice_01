/**
* @file MyListener.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 14 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que detecta las colisiones entre dos objetos de la escena
**/

#include "MyListener.hpp"
#include "Scene.hpp"

namespace Engine
{
	///Constructor que recoge una referencia a la escena y la guarda 
	MyListener::MyListener(Scene* given_scene)
	{
		scene = given_scene;
	}

	///Cuando hay colisión
	void MyListener::BeginContact(b2Contact* contact)
	{
		//Recoge las fixtures de los dos objetos
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		///Recoge el data del objeto para poder acceder al pointer (lo usamos como tag del objeto)
		b2BodyUserData bodyUserDataA = fixtureA->GetBody()->GetUserData();
		b2BodyUserData bodyUserDataB = fixtureB->GetBody()->GetUserData();


		//Colisiona bola (pointer == 1) con la plataforma de la derecha (pointer == 2)
		if (bodyUserDataA.pointer == 2 && bodyUserDataB.pointer == 1)
		{
			scene->colision_platform_01 = true;
			scene->circle.bodyEntity->SetGravityScale(20);
		}
		//Colisiona bola (pointer == 1) con la plataforma de la izquierda (pointer == 3)
		else if (bodyUserDataA.pointer == 3 && bodyUserDataB.pointer == 1)
		{
			scene->colision_platform_02 = true;
			scene->circle.bodyEntity->SetGravityScale(20);
		}
		//Colisiona bola (pointer == 1) con la plataforma ganadora (pointer == 9)
		else if (bodyUserDataA.pointer == 9 && bodyUserDataB.pointer == 1)
		{
			scene->exit = true;
		}
		//Colisiona bola (pointer == 1) con el piston que se encuentra primero (pointer == 11)
		else if (bodyUserDataA.pointer == 11 && bodyUserDataB.pointer == 1)
		{
			scene->start_piston_01 = true;
		}
		//Colisiona bola (pointer == 1) con el pistón catapulta para saltar el fuego (pointer == 17)
		else if (bodyUserDataA.pointer == 17 && bodyUserDataB.pointer == 1)
		{
			scene->start_piston_02 = true;
		}
		//Colisiona bola (pointer == 1) con la meta (pointer == 18)
		else if (bodyUserDataA.pointer == 18 && bodyUserDataB.pointer == 1)
		{
			scene->restart_Scene = true;
		}
		//Colisiona bola (pointer == 1) con la pared de arriba (pointer == 19)
		else if (bodyUserDataA.pointer == 19 && bodyUserDataB.pointer == 1)
		{
			scene->circle.bodyEntity->SetLinearVelocity({ 0, 0 });
			scene->circle.bodyEntity->SetGravityScale(20);
		}
	}

	///Cuando se acaba la colisión
	void MyListener::EndContact(b2Contact* contact)
	{
		//Recoge las fixtures de los dos objetos
		b2Fixture* fixtureA = contact->GetFixtureA();
		b2Fixture* fixtureB = contact->GetFixtureB();

		///Recoge el data del objeto para poder acceder al pointer (lo usamos como tag del objeto)
		b2BodyUserData bodyUserDataA = fixtureA->GetBody()->GetUserData();
		b2BodyUserData bodyUserDataB = fixtureB->GetBody()->GetUserData();

		//Termina de colisionar la bola (pointer == 1) con la plataforma de la derecha (pointer == 2)
		if (bodyUserDataA.pointer == 2 && bodyUserDataB.pointer == 1)
		{
			scene->colision_platform_01 = false;
			scene->circle.bodyEntity->SetGravityScale(1);
		}
		//Termina de colisionar la bola (pointer == 1) con la plataforma de la izquierda (pointer == 3)
		else if (bodyUserDataA.pointer == 3 && bodyUserDataB.pointer == 1)
		{
			scene->colision_platform_02 = false;
			scene->circle.bodyEntity->SetGravityScale(1);
		}
		//Termina de colisionar la bola (pointer == 1) con el piston que se encuentra primero (pointer == 11)
		else if (bodyUserDataA.pointer == 11 && bodyUserDataB.pointer == 1)
		{
			scene->start_piston_01 = false;
		}
		//Termina de colisionar la bola (pointer == 1) con el pistón catapulta para saltar el fuego (pointer == 17)
		else if (bodyUserDataA.pointer == 17 && bodyUserDataB.pointer == 1)
		{
			scene->start_piston_02 = false;
		}
	}

}
