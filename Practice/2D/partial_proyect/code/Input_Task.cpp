/**
* @file Input_Task.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 12 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que recoge la entrada del input (controles para manejar el juego)
**/

#include "Input_Task.hpp"
#include "Scene.hpp"

namespace Engine
{
    /// Constructor por defecto
    Input_Task::Input_Task(Scene * given_scene)
    {
        //Recoge y guarda el valor de la escena
        scene = given_scene;
    }

    ///Función que recoge cuando entra el input
    bool Input_Task::process(Render_Task& tr, Window& window, b2Body* circle, float window_height, float scale)
    {
        Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case Event::KeyPressed:
                {
                    switch (event.key.code)
                    {
                        //Si se pulsa la tecla R se resetea la escena
                        case Keyboard::R:
                        {
                            scene->circle.set_start_pos();
                            break;
                        }
                        //Si se pulsa la tecla escape se sale de la aplicación
                        case Keyboard::Escape:
                        {
                            return true;
                            break;
                        }
                    }
                    break;
                }

                case Event::Closed:
                {
                    return true;
                }
            }
        }

        return false;
    }
}
