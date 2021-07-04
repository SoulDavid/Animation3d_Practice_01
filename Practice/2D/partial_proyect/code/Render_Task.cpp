/**
* @file Render_Task.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 12 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que pinta por pantalla todas las entidades/objetos de la escena
**/

#include "Render_Task.hpp"

namespace Engine
{
    ///Función para renderizar circulo
    void Render_Task::render_circle (b2Vec2 center, float radius, const b2Transform& transform, RenderWindow& renderer, float window_height, float scale, Color color)
    {
        //Coge el shape
        CircleShape shape;

        radius *= scale;

        shape.setPosition(box2d_position_to_sfml_position(b2Mul(transform, center), window_height, scale) - Vector2f(radius, radius));
        shape.setRadius(radius);
        //Pinta la forma del color que le pasamos
        shape.setFillColor(color);

        //Se dibuja a traves del render
        renderer.draw(shape);
    }

    ///Función para renderizar segmento
    void Render_Task::render_segment (const Vector2f& start, const Vector2f& end, const Color& color, RenderWindow& renderer)
    {
        //Por cada vertice le da un color
        Vertex line[] =
        {
            Vertex(start, color),
            Vertex(end, color),
        };

        //Se dibuja a traves del render
        renderer.draw(line, 2, Lines);
    }

    ///Funciones para pasarlo a box2d (Para escalar)
    inline Vector2f Render_Task::box2d_position_to_sfml_position(const b2Vec2& box2d_position, float window_height, float scale)
    {
        return Vector2f(box2d_position.x * scale, window_height - box2d_position.y * scale);
    }

    ///Funciones para pasarlo a box2d (Para escalar)
    b2Vec2 Render_Task::sfml_position_to_box2d_position(const Vector2f& sfml_position, float window_height, float scale)
    {
        return b2Vec2(sfml_position.x / scale, (window_height - sfml_position.y) / scale);
    }

    ///Función para renderizar segmento
    void Render_Task::render_segment (b2Vec2 start, b2Vec2 end, const b2Transform& transform, RenderWindow& renderer, float window_height, float scale)
    {
        start = b2Mul(transform, start);
        end = b2Mul(transform, end);

        render_segment
        (
            box2d_position_to_sfml_position(start, window_height, scale),
            box2d_position_to_sfml_position(end, window_height, scale),
            Color::Green,
            renderer
        );
    }

    ///Función para renderizar polígono
    void Render_Task::render_polygon (const b2Vec2* vertices, int number_of_vertices, const b2Transform& transform, RenderWindow& renderer, float window_height, float scale, Color color)
    {

        ConvexShape sfml_polygon;

        sfml_polygon.setPointCount(number_of_vertices);

        //Lo rellena del color que le digamos
        sfml_polygon.setFillColor(color);

        //Por cada punto, lo pone en la pantalla escalado
        for (int index = 0; index < number_of_vertices; index++)
        {
            sfml_polygon.setPoint
            (
                index,
                box2d_position_to_sfml_position(b2Mul(transform, vertices[index]), window_height, scale)
            );
        }

        //Se dibuja a traves del render
        renderer.draw(sfml_polygon);
    }

    //Función para renderizar todos los objetos de la escena
    void Render_Task::render(b2World& physics_world, RenderWindow& renderer, float scale)
    {
        // Se cachea el alto de la ventana en una variable local:

        float window_height = (float)renderer.getSize().y;

        // Se recorre toda la lista de bodies de physics_world:

        for (b2Body* body = physics_world.GetBodyList(); body != nullptr; body = body->GetNext())
        {
            // Se obtiene el transform del body:

            const b2Transform& body_transform = body->GetTransform();

            // Se recorre la lista de fixtures del body:

            for (b2Fixture* fixture = body->GetFixtureList(); fixture != nullptr; fixture = fixture->GetNext())
            {
                // Se obtiene el tipo de forma de la fixture:

                b2Shape::Type shape_type = fixture->GetShape()->GetType();

                switch (shape_type)
                {
                    case b2Shape::e_circle:
                    {
                        // Se crea un CircleShape a partir de los atributos de la forma de la fixture y del body:
                        // En SFML el centro de un círculo no está en su position. Su position es la esquina superior izquierda
                        // del cuadrado en el que está inscrito. Por eso a position se le resta el radio tanto en X como en Y.

                        b2CircleShape* circle = dynamic_cast<b2CircleShape*>(fixture->GetShape());

                        render_circle(circle->m_p, circle->m_radius, body_transform, renderer, window_height, scale, Color::Magenta);

                        break;
                    }

                    case b2Shape::e_edge:
                    {
                        // Se toman los dos vértices del segmento y se ajusta su posición usando el transform del body.
                        // Los vértices resultantes se convierten y se ponen en un array para finalmente dibujar el segmento
                        // que los une usando la sobrecarga del método draw() que permite dibujar primitivas de OpenGL a
                        // partir de datos de vértices.

                        b2EdgeShape* edge = dynamic_cast<b2EdgeShape*>(fixture->GetShape());

                        render_segment(edge->m_vertex1, edge->m_vertex2, body_transform, renderer, window_height, scale);

                        break;
                    }

                    case b2Shape::e_polygon:
                    {
                        // Se toma la forma poligonal de Box2D (siempre es convexa) y se crea a partir de sus vértices un
                        // ConvexShape de SFML. Cada vértice de Box2D hay que transformarlo usando el transform del body.

                        b2PolygonShape* box2d_polygon = dynamic_cast<b2PolygonShape*>(fixture->GetShape());

                        //Dependiendo del tag que tenga el objeto, se pintará con un color u otro
                        switch (body->GetUserData().pointer)
                        {
                        case 2:
                        case 3:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::Green);
                            break;
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::Blue);
                            break;
                        case 9:
                        case 10:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::Red);
                            break;
                        case 11:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::Cyan);
                            break;
                        case 12:
                        case 13:
                        case 14:
                        case 15:
                        case 16:
                        case 17:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::Yellow);
                            break;
                        case 18:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::Black);
                            break;
                        case 19:
                            render_polygon(box2d_polygon->m_vertices, box2d_polygon->m_count, body_transform, renderer, window_height, scale, Color::White);
                            break;
                        }
                       
                        break;
                    }
                }
            }
        }
    }
}
