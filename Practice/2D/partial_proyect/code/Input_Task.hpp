/**
* @file Input_Task.hpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 12 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que recoge la entrada del input (controles para manejar el juego)
**/

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Render_Task.hpp"

using namespace sf;
using namespace std;

namespace Engine
{
    //Referencia a la escena
    class Scene;
	class Input_Task
	{
    public:
        //Objeto que recoge referencia a la escena
       Scene * scene;
    public:
        ///Constructor por defecto
        Input_Task(Scene*);
    public:
        ///Función que recoge cuando entra el input
        bool process(Render_Task&, Window&, b2Body*, float, float);
	};
}


