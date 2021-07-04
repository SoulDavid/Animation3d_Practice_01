/**
* @file ParticleSystemManager.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 16 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que contiene el comportamiento del sistema de particulas como un objeto
**/

#include "ParticleSystemManager.hpp"

///Constructor por defecto
ParticleSystemManager::ParticleSystemManager(sf::RenderWindow* window)
{

}

///Destructor por defecto
ParticleSystemManager::~ParticleSystemManager()
{

}

///Update del manager
void ParticleSystemManager::Update(sf::Time deltaTime)
{
	//Por cada particula, se llama a su update
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
	{
		m_particleSystem[i].Update(deltaTime);
	}
}

///Draw del manager
void ParticleSystemManager::Draw(sf::RenderWindow* window)
{
	//Por cada partícula, se llama a su draw
	for (std::size_t i = 0; i < m_particleSystem.size(); ++i)
		window->draw(m_particleSystem[i]);
}

///Función para crear unas partículas en una posición dada
void ParticleSystemManager::AddParticleSystem(sf::Vector2f position)
{
	//Se crea una partícula
	ParticleSystem* particleSystemToAdd = new ParticleSystem();
	//Se le añaden los valores inciales que le queramos dar
	particleSystemToAdd->SetEmitter(position);
	particleSystemToAdd->SetEmitAngle(rand() % 360);
	particleSystemToAdd->SetInitialSpeed(rand() % 200);
	//Y se inserta al final del vector de m_particleSystem que contiene las particulas creadas
	m_particleSystem.emplace_back(*particleSystemToAdd);
}