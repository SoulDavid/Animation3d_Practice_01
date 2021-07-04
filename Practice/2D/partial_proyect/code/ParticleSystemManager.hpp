/**
* @file ParticleSystemManager.hpp
* Copyright (c) David Martín
* @author David Martín Almazán
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
	///Función para crear unas partículas en una posición dada
	void AddParticleSystem(sf::Vector2f position);
private:
	///Vector que recoge las particulas que se van creando
	std::vector<ParticleSystem> m_particleSystem;
};

