/**
* @file ParticleSystemManager.hpp
* Copyright (c) David Mart�n
* @author David Mart�n Almaz�n
* @date 16 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que contiene el comportamiento del sistema de particulas como un objeto 
**/

#pragma once
#include <SFML/Graphics.hpp>
#include "ParticleSystem.hpp"

class ParticleSystemManager
{
public:
	///Constructor por defecto
	ParticleSystemManager(sf::RenderWindow* window);
	///Destructor por defecto
	~ParticleSystemManager();
	///Update del manager
	void Update(sf::Time deltaTime);
	///Draw del manager
	void Draw(sf::RenderWindow* window);
	///Funci�n para crear unas part�culas en una posici�n dada
	void AddParticleSystem(sf::Vector2f position);
private:
	///Vector que recoge las particulas que se van creando
	std::vector<ParticleSystem> m_particleSystem;
};

