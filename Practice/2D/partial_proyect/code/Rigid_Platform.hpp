#pragma once
#include "Render_Task.hpp"

using namespace sf;
using namespace std;

namespace Engine
{
	class Rigid_Platform
	{
	public:
		Rigid_Platform(Render_Task&, float, float, b2World);
	};
}


