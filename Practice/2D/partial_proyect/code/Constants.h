#pragma once
/**
* @file Constants.h
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 15 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que recoge las capas de las entidades. El valor de la variable tiene que ser potencia de 2
**/

namespace Engine
{
	class Constants
	{
	public:
		static const short BIT_LIMITS = 1;				//2^0
		static const short BIT_PLAYER = 2;				//2^1
		static const short BIT_PLATFORM_MOVABLE = 4;	//2^2
		static const short BIT_WALL = 8;				//2^3
		static const short BIT_WIN_RAMP = 16;			//2^4
		static const short BIT_SENSOR = 32;				//2^5
		static const short BIT_PISTON = 64;				//2^6
		static const short BIT_RAMP = 128;				//2^7
	};
}
