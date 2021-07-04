/**
* @file ParticleSystem.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 16 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que lleva el comportamiento de la propia particula.
**/


#include "ParticleSystem.hpp"
#include <math.h>
#define PI 3.1415926

///Constructor por defecto
ParticleSystem::ParticleSystem()
{
	///https://www.cplusplus.com/reference/vector/vector/resize/
	//Reseteo de todo, para que comience desde un punto bueno
	m_particles.resize(count);
	m_shapes.resize(count);
	m_emiterLifetime = sf::seconds(3);
	m_emitter.x = 0;
	m_emitter.y = 0;

	//Se crean con un tamaño random
	for (int i = 0; i < m_shapes.size(); i++)
	{
		m_shapes[i].setRadius(rand() % 10 + 5);
	}
}

///Destructor
ParticleSystem::~ParticleSystem()
{

}

///Update de la particula
void ParticleSystem::Update(sf::Time deltaTime)
{
	//Por cada particula
	for (std::size_t i = 0; i < m_particles.size(); ++i)
	{
		// update el tiempo de la particula estando activa
		Particle& p = m_particles[i];
		p.lifetime -= deltaTime;
		p.timePassed += deltaTime;

		// Si ha acabado su tiempo de activación se resetea la particula (haciendo como una pool de objetos)
		if (p.lifetime <= sf::Time::Zero)
			ResetParticle(i);

		//Updateamos la forma de las particulas y su posición
		p.velocity += sf::Vector2f(p.velAcc * deltaTime.asMilliseconds() * std::cos(p.angle), p.velAcc * deltaTime.asMilliseconds() * std::sin(p.angle));
		sf::Vector2f lastFramePos = m_shapes[i].getPosition();
		sf::Vector2f newPos = lastFramePos + p.velocity * deltaTime.asSeconds();
		m_shapes[i].setPosition(newPos);

		//Updateamos la transparencia de la partícula, si esta a 0, significará que habrá muerto y por lo tanto se resetearía
		float ratio = p.lifetime.asSeconds() / m_emiterLifetime.asSeconds();

		//Nuemro aleatorio para que sea de dos colores: rojo o amarillo (de esta manera da la sensación de fuego)
		int num = rand() % 3 + 1;
		if(num == 1)
			m_shapes[i].setFillColor(sf::Color(255, 0, 0, static_cast<sf::Uint8>(ratio * 255)));
		else
			m_shapes[i].setFillColor(sf::Color(255, 255, 0, static_cast<sf::Uint8>(ratio * 255)));

	}
}

//Se pinta en la escena
void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	//Se aplica un transform
	states.transform *= getTransform();

	//Se recorre el array de particulas pintando su forma con su color
	for (int i = 0; i < m_shapes.size(); i++)
		target.draw(m_shapes[i], states);
}

///Función de reseteo. Cuando se vuelve a su posicion inicial tras volverse invisible (actua como pool de particulas)
void ParticleSystem::ResetParticle(std::size_t index)
{
	//Angulo de 200 y la velocidad es un random entre la velocidad inicial y 50
	float angle = 200;
	float speed = (std::rand() % 50) + initialSpeed;

	//Resetear el timer
	m_particles[index].timePassed = sf::Time::Zero;
	//Reseteamos la velocidad
	m_particles[index].velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

	//Reseteamos el angulo
	m_particles[index].angle = 0;

	//Reseteamos la rotación
	m_particles[index].rotation = 0;

	//Reseteamos la velocidad de aceleración 
	m_particles[index].velAcc = 0;

	//Reseteamos la rotación de aceleración
	m_particles[index].rotAcc = 0;

	//Reseteamos la velocidad con la que viaja
	m_particles[index].growsSpeed = 0;

	//Reseteamos el tamaño
	m_particles[index].size = sf::Vector2f(1.0f, 1.0f);
	m_shapes[index].setScale(m_particles[index].size);

	//Se resetea el lifetime
	m_particles[index].lifetime = sf::milliseconds(p_lifetime);

	//Reseteamos la posicion
	m_shapes[index].setPosition(m_emitter);

}

///El ángulo con el que se emite
void ParticleSystem::SetEmitAngle(int emiterAngle)
{
	this->emiterAngle = emiterAngle;
}

///La velocidad con la que inicia
void ParticleSystem::SetInitialSpeed(float initialSpeed)
{
	this->initialSpeed = initialSpeed;
}

///El emisor de esta partícula
void ParticleSystem::SetEmitter(sf::Vector2f position)
{
	m_emitter = position;
}

