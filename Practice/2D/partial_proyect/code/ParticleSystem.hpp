/**
* @file ParticleSystem.hpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 16 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que lleva el comportamiento de la propia particula.
**/

#pragma once
#include <SFML/Graphics.hpp>
#pragma once

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
	///Constructor de la particula
	ParticleSystem(); 
	///Destructor de la particula
	~ParticleSystem();
	///Update de la partícula
	void Update(sf::Time deltaTime);
	///Para pintar la particula
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	#pragma region Funciones cuando son spameadas o para resetear sus variables
	///El emisor de esta partícula
	void SetEmitter(sf::Vector2f position);
	///El ángulo con el que se emite
	void SetEmitAngle(int angle);
	///La velocidad con la que inicia
	void SetInitialSpeed(float initialSpeed);
	#pragma endregion

private:
	///Datos de la particula
	struct Particle
	{
		//velocidad
		sf::Vector2f velocity;
		//tiempo que dura activa
		sf::Time lifetime;
		//tamaño de la particula
		sf::Vector2f size;
		//velocidad con la que viaja
		float growsSpeed;
		//rotación de la partícula
		float rotation;
		//tiempo que lleva estando activa
		sf::Time timePassed;
		//angulo con el que sale
		float angle;
		//aceleracion de la particula
		float velAcc;
		//aceleracion de rotación de la particula
		float rotAcc;
	};
	//lifetime de la particula para luego setearla en sus propiedades
	float p_lifetime = 50.0f;
	///Cuando se vuelve a su posicion inicial tras volverse invisible (actua como pool de particulas)
	void ResetParticle(std::size_t index);

	//Vector que guarda las particulas y las formas de este. Se utiliza vector para utilziar la funcion resize
	std::vector<Particle> m_particles;
	std::vector<sf::CircleShape> m_shapes; 

	///Tiempo de la particula estando activa
	sf::Time m_emiterLifetime;
	sf::Vector2f m_emitter;

	//Variables para luego setearlas a las varaibles creadas 
	int emiterAngle = 360;
	float initialSpeed = 500;
	int count = 20;

};
