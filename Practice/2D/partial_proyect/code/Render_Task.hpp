/**
* @file Render_Task.hpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 12 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que pinta por pantalla todas las entidades/objetos de la escena
**/

#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

namespace Engine
{
	class Render_Task
	{
	public:
		///Función para renderizar circulo
		void render_circle	 (b2Vec2, float, const b2Transform&, RenderWindow&, float, float, Color);

		///Función para renderizar segmento
		void render_segment	 (const Vector2f&, const Vector2f&, const Color&, RenderWindow&);

	public:
		///Funciones para pasarlo a box2d (Para escalar)
		inline Vector2f box2d_position_to_sfml_position(const b2Vec2&, float, float);
		b2Vec2 sfml_position_to_box2d_position  (const Vector2f&, float, float);

		///Función para renderizar segmento
		void render_segment (b2Vec2, b2Vec2, const b2Transform&, RenderWindow&, float, float);

		///Función para renderizar polígono
		void render_polygon (const b2Vec2*, int, const b2Transform&, RenderWindow&, float, float, Color);

		///Función para renderizar todos los objetos de la escena
		void render			(b2World&, RenderWindow&, float);
	};
}


