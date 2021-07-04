

#include <ciso646>
#include <memory>
#include <vector>
#include <Box2D/Box2D.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

using namespace sf;
using namespace std;
using namespace Engine;

int main ()
{
    ///Medidas de la ventana
    constexpr int window_width  = 1920;
    constexpr int window_height = 1080;

    //Se crea la ventana
    RenderWindow window (VideoMode(window_width, window_height), "Box2D Forces", Style::Titlebar | Style::Close, ContextSettings(32));    
    
    ///Se crea la escena, y se llama a su update
    Scene scene_01 (window, window_height, window_width);
    scene_01.Update(window);

    return 0;
}
