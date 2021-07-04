/**
* @file Entity.hpp
* Copyright (c) David Mart�n
* @author David Mart�n Almaz�n
* @date 13 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que guarda el body con sus propias fixtures y la posici�n inicial de cada objeto de la escena
**/

#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace Engine
{
	class Entity
	{
	public:

		//Recoge el body de la entidad para poder acceder a sus fixtures
		b2Body * bodyEntity;
		//Vector que recoge la posici�n inicial
		b2Vec2 initialPos;

	public:
		//Variable que recoge los puntos iniciales para las plataformas movibles
		float x0 ;
		float y0 ;
		float x1 ;
		float y1 ;

		//booleano que indica para donde se va a mover la plataforma: false horizontal || true vertical
		bool sidePlatform;

	public:
		///Constructor por defecto
		Entity();

		///Funci�n para crear un circulo 
		//(b2World& physics_world, b2BodyType body_type, float x, float y, float radius, uintptr_t tag, short cBits, short mBits, short gIndex)
		b2Body* create_circle(b2World&, b2BodyType, float, float, float, uintptr_t, short, short, short);

		///Funci�n para crear un cubo 
		//(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height, uintptr_t tag, short cBits, short mBits, short gIndex)
		b2Body* create_box(b2World&, b2BodyType, float, float, float, float, uintptr_t, short, short, short);

		///Funci�n para crear una plataforma s�lida usada por ejemplo para crear el suelo
		//(b2World& physics_world, float x, float y, float width, float height, uintptr_t tag, short cBits, short mBits, short gIndex)
		b2Body* create_solid_platform(b2World&, float, float, float, float, uintptr_t, short, short, short);

		///Funci�n para crear una plataforma que se mueve 
		//(b2World& physics_world, float pointxstart, float pointystart, float pointxend, float pointyend, float x, float y, float width, float height, bool side, uintptr_t tag, short cBits, short mBits, short gIndex)
		b2Body* create_moving_platform(b2World&, float, float, float, float, float, float, float, float, bool, uintptr_t, short, short, short);

		///Funci�n para crear l�neas, usada para los bordes 
		//(b2World& physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1, uintptr_t tag)
		b2Body* create_edge(b2World&, b2BodyType, float, float, float, float, uintptr_t);

		///Funci�n para crear pol�gonos, usada para rampas 
		//(b2World& physics_world, b2BodyType body_type, b2Vec2 points [], int32 count, uintptr_t tag, short cBits, short mBits, short gIndex)
		b2Body* create_polygon(b2World&, b2BodyType, b2Vec2[], int32, uintptr_t, short, short, short);

		///Funci�n para crear triggers
		//(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height, uintptr_t tag, short cBits, short mBits, short gIndex)
		b2Body* create_trigger(b2World&, b2BodyType, float, float, float, float, uintptr_t, short, short, short);

		/// Funci�n para crear el joint que se usar� en los ventiladores (todo el rato girando)
		//(b2World& physics_world, b2Body* body_a, b2Body* body_b, float min_angle, float max_angle, bool enable_motor)
		b2RevoluteJoint* create_revolute_joint_ventilador(b2World&, b2Body*, b2Body*, float, float, bool);

		///Funci�n para crear un joint normal
		//(b2World& physics_world, b2Body* body_a, b2Body* body_b, float min_angle, float max_angle, bool enable_motor)
		b2RevoluteJoint* create_revolute_joint(b2World&, b2Body*, b2Body*, float, float, bool);

		///Funci�n para crear un joint para juntar dos entidades : Joint b�sico
		//(b2World& physics_world, b2Body* body_a, b2Body* body_b, float x, float y, bool enable_motor)
		b2RevoluteJoint* create_revolute_joint_entities(b2World&, b2Body*, b2Body*, float, float, bool);

		///Funci�n para crear los joints para las catapultas o para paredes que no se quieran mover y no pertenezcan al escenario : Joint complejo
		//(b2World& physics_world, b2Body* body_a, b2Body* body_b, float x, float y, float min_angle, float max_angle, bool enable_motor)
		b2RevoluteJoint* create_revolute_joint_catapult(b2World&, b2Body*, b2Body*, float, float, float, float, bool);

		///Funci�n que lleva el update de la plataforma para moverse. Tiene en cuenta los puntos que le dimos con anterioridad y que recogi� la entidad
		//(Entity entity, bool active, float speed)
		void update_platform(Entity, bool, float);

		///Funci�n que lleva el update del piston. Se le pasa los puntos y si esta activa
		//(Entity entity, float speedx, float speedy, float x0, float y0, float x1, float y1, bool active)
		void update_piston(Entity, float, float, float, float, float, float, bool);

		///Funci�n que lleva el update de los pistones y ventiladores.
		//(b2RevoluteJoint* joint, bool active)
		void update_spring(b2RevoluteJoint*, bool);

		///Funci�n para recoger la posici�n donde se inicia la pelota
		void get_start_pos();

		///Funci�n para setear la posici�n de la pelota
		void set_start_pos();

	};
}

