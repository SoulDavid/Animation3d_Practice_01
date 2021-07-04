/**
* @file MyListener.hpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 14 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que detecta las colisiones entre dos objetos de la escena
**/

#pragma once

#include <Box2D/Box2D.h>
#include <iostream>
#include <cstddef>

using namespace std;

namespace Engine
{
	//Declaracion adelantada para hacer referencia a la escena
	class Scene;
	class MyListener : public b2ContactListener
	{
	public:
		//Referencia a la escena
		Scene* scene;
	public:
		///Constructor por defecto
		MyListener(Scene*);

		///Cuando hay colisión
		void BeginContact(b2Contact*) override;

		///Cuando se acaba la colisión
		void EndContact(b2Contact*) override;
	};
}




