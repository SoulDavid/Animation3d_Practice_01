/**
* @file Scene.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 14 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que lleva todos los objetos de la escena, sus updates, y el ciclo del juego
**/

#include "Scene.hpp"

namespace Engine
{
    ///Constructor por defecto
    Scene::Scene(RenderWindow& window, const int window_height_given, const int window_width_given)
    {
        window.setVerticalSyncEnabled(true);

        //Recogemos las medidas de la ventana
        window_height = window_height_given;
        window_width = window_width_given;       

        //Referencia al input task
        it = new Input_Task(this);

        #pragma region Limites

        constexpr float left = 0.01f;
        constexpr float right = 19.1f;
        constexpr float top = 10.75f;
        constexpr float bottom = 0.01f;


        //Limites
        LimitBottomRight.create_edge(physics_world, b2_staticBody, left, bottom, right, bottom, 0);
        LimitBottomLeft.create_edge(physics_world, b2_staticBody, left, bottom, left, top, 0);
        LimitTopRight.create_edge(physics_world, b2_staticBody, left, top, right, top, 0);
        LimitTopLeft.create_edge(physics_world, b2_staticBody, right, bottom, right, top, 0);

        #pragma endregion

        #pragma region Main Character

        //    b2Body* Entity::create_circle(b2World& physics_world, b2BodyType body_type, float x, float y, float radius)
        circle.bodyEntity = circle.create_circle(physics_world, b2_dynamicBody, 2, 5, .3f, 1, constants.BIT_PLAYER, (short)(constants.BIT_LIMITS | constants.BIT_PLATFORM_MOVABLE | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON | constants.BIT_RAMP), (short) 0);

        #pragma endregion

        #pragma region Plataformas Movibles

        // b2Body* Entity::create_moving_platform(b2World& physics_world, float pointxstart, float pointystart, float pointxend, float pointyend, float x, float y, float width, float height, bool side, tag)
        Platform_Movable_01.bodyEntity = Platform_Movable_01.create_moving_platform(physics_world, 1, 1, 5, 9.2f, 18, 1, 1, .2f, true, 2, constants.BIT_PLATFORM_MOVABLE, (short)(constants.BIT_PLAYER), (short)0 );

        Platform_Movable_02.bodyEntity = Platform_Movable_02.create_moving_platform(physics_world, 1, 6.1f, 1, 9.1f, 5, 6, 1.7, .2f, true, 3, constants.BIT_PLATFORM_MOVABLE, (short)(constants.BIT_PLAYER), (short)0);

        #pragma endregion

        #pragma region Plataformas Solidas

        //b2Body* Entity::create_solid_platform(b2World & physics_world, float x, float y, float width, float height)

        floor.bodyEntity = floor.create_solid_platform(physics_world, 0, 1, 17, .2f, 4, constants.BIT_WALL, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON | constants.BIT_RAMP), (short)0);

        floor_Second_Level.bodyEntity = floor_Second_Level.create_solid_platform(physics_world, 8.55f, 6.f, 1.85f, .2f, 5, constants.BIT_WALL, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON | constants.BIT_RAMP), (short)0);

        floor_Second_Level_Part_2.bodyEntity = floor_Second_Level_Part_2.create_solid_platform(physics_world, 15.5f, 9.2f, 1.5f, .2f, 6, constants.BIT_WALL, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON | constants.BIT_RAMP), (short)0);
        floor_Second_Level_Part_2.bodyEntity->GetFixtureList()->SetFriction(1);
        #pragma endregion

        #pragma region Rampas

        //https://box2d.org/documentation/md__d_1__git_hub_box2d_docs_collision.html#autotoc_md38
        b2Vec2 vertex_Ramp_Down[4];
        vertex_Ramp_Down[0].Set(0.0f, 1.2f);
        vertex_Ramp_Down[1].Set(5.0f, 1.2f);
        vertex_Ramp_Down[2].Set(0.f, 3.f);
        vertex_Ramp_Down[3].Set(3.f, 3.f);

        RampDown.bodyEntity = RampDown.create_polygon(physics_world, b2_staticBody, vertex_Ramp_Down, countRamp, 7, constants.BIT_RAMP, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON), (short)0);

        //-------------------------------------------------------------------------------------------------------------------------------------------------

        b2Vec2 vertex_Ramp_Up[4];
        vertex_Ramp_Up[0].Set(10.4f, 6.2f);
        vertex_Ramp_Up[1].Set(10.4f, 5.8f);
        vertex_Ramp_Up[2].Set(14, 9);
        vertex_Ramp_Up[3].Set(14, 9.4f);

        Ramp_Up.bodyEntity = Ramp_Up.create_polygon(physics_world, b2_staticBody, vertex_Ramp_Up, countRamp, 8, constants.BIT_RAMP, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON), (short)0);
        Ramp_Up.bodyEntity->GetFixtureList()->SetFriction(20);
        Ramp_Up.bodyEntity->GetFixtureList()->SetRestitution(0);
        //-------------------------------------------------------------------------------------------------------------------------------------------------

        b2Vec2 vertex_Ramp_Win_Left[4];
        vertex_Ramp_Win_Left[0].Set(0, 9.4f);
        vertex_Ramp_Win_Left[1].Set(0, 9.f);
        vertex_Ramp_Win_Left[2].Set(1.5f, 8.f);
        vertex_Ramp_Win_Left[3].Set(1.5f, 7.6f);

        Ramp_Win_Left.bodyEntity = Ramp_Win_Left.create_polygon(physics_world, b2_staticBody, vertex_Ramp_Win_Left, countRamp, 9, constants.BIT_WIN_RAMP, (short)(constants.BIT_PLAYER), (short)0);

        b2Vec2 vertex_Ramp_Win_Right[4];
        vertex_Ramp_Win_Right[0].Set(3.3f, 9.4f);
        vertex_Ramp_Win_Right[1].Set(3.3f, 9.f);
        vertex_Ramp_Win_Right[2].Set(1.5f, 8.f);
        vertex_Ramp_Win_Right[3].Set(1.5f, 7.6f);

        Ramp_Win_Right.bodyEntity = Ramp_Win_Right.create_polygon(physics_world, b2_staticBody, vertex_Ramp_Win_Right, countRamp, 10, constants.BIT_WIN_RAMP, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_WIN_RAMP | constants.BIT_SENSOR | constants.BIT_PISTON), (short)0);

        #pragma endregion

        #pragma region Piston_01

        trigger_piston_01.bodyEntity = trigger_piston_01.create_trigger(physics_world, b2_dynamicBody, 2, 3, 0.5, 0.01, 11, constants.BIT_SENSOR, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_RAMP), (short)0);
        trigger_piston_01.bodyEntity->GetFixtureList()->SetFriction(0);
        trigger_piston_01.bodyEntity->GetFixtureList()->SetDensity(100);
        //piston_01.bodyEntity = piston_01.create_box(physics_world, b2_dynamicBody, 0.5, 3, 0.4, 0.3, 12, constants.BIT_PISTON, (short)(constants.BIT_WALL | constants.BIT_PLAYER | constants.BIT_RAMP), (short)0);
        piston_01_pusher.bodyEntity = piston_01_pusher.create_box(physics_world, b2_dynamicBody, 1, 3, 0.15, 0.3, 13, constants.BIT_PISTON, (short)(constants.BIT_PLAYER | constants.BIT_WALL | constants.BIT_RAMP), (short)0);

        #pragma endregion

        #pragma region Ventilador_01
        aspa_02.bodyEntity = aspa_02.create_box(physics_world, b2_dynamicBody, 4, 11.5, 2.f, 0.1f, 14, constants.BIT_PISTON, (short)(constants.BIT_PLAYER), (short)0);

        b2RevoluteJoint* aspa_static = aspa_02.create_revolute_joint_entities(physics_world, aspa_02.bodyEntity, floor_Second_Level.bodyEntity, -3.5, 5, true);
        aspa_static->SetMaxMotorTorque(75.f);
        aspa_static->SetMotorSpeed(1.f);

        #pragma endregion

        #pragma region Ventilador_02
        aspa_02_02.bodyEntity = aspa_02_02.create_box(physics_world, b2_dynamicBody, 18, 11.5, 2.f, 0.1f, 15, constants.BIT_PISTON, (short)(constants.BIT_PLAYER), (short)0);

        b2RevoluteJoint* aspa_static_02 = aspa_01.create_revolute_joint_entities(physics_world, aspa_02_02.bodyEntity, floor_Second_Level_Part_2.bodyEntity, 3.5, 2.5f, true);
        aspa_static_02->SetMaxMotorTorque(75.f);
        aspa_static_02->SetMotorSpeed(1.f);

        #pragma endregion        

        #pragma region Trampa Muelle

        //springTrap_Down.bodyEntity = springTrap_Down.create_box(physics_world, b2_dynamicBody, 7, 1.3f, 1.f, 0.1f, 16, constants.BIT_PISTON, (short)(constants.BIT_PLAYER | constants.BIT_WALL), (short)0);
        springTrap_Up.bodyEntity = springTrap_Up.create_box(physics_world, b2_dynamicBody, 7, 1.8f, 1.f, 0.1f, 17, constants.BIT_PISTON, (short)(constants.BIT_PLAYER | constants.BIT_WALL), (short)0);

        //b2RevoluteJoint* spring_static = aspa_01.create_revolute_joint_entities(physics_world, springTrap_Down.bodyEntity, floor.bodyEntity, 5, 1.f, false);
        joint_def = springTrap_Down.create_revolute_joint_catapult(physics_world, springTrap_Up.bodyEntity, floor.bodyEntity, 6.f, 0.3f ,0, 90, true);
        #pragma endregion

        #pragma region Trigger Sistema Partículas
        trigger_System_Particle.bodyEntity = trigger_System_Particle.create_box(physics_world, b2_dynamicBody, 9.3, 1.5f, 0.4, 0.4, 18, constants.BIT_SENSOR, (short)(constants.BIT_PLAYER | constants.BIT_WALL), (short)0);
        particle_collider = trigger_System_Particle.create_revolute_joint_catapult(physics_world, trigger_System_Particle.bodyEntity, floor.bodyEntity, 9.3, 0.6f, 0, 0, true);

        m_VFXManager = new ParticleSystemManager(&window);
        #pragma endregion
        
        #pragma region Pared Oscura Floor 2
        floor_Second_Level_Part_3.bodyEntity = floor_Second_Level_Part_3.create_box(physics_world, b2_dynamicBody, 3.2f, 7.3f, 0.1f, 1.5f, 19, constants.BIT_PISTON, (short)(constants.BIT_PLAYER | constants.BIT_WALL), (short)0);
        wall_floor_2 = floor_Second_Level_Part_3.create_revolute_joint_catapult(physics_world, floor_Second_Level_Part_3.bodyEntity, floor_Second_Level.bodyEntity, -5.4f, 1.5f, 0, 0, false);
        #pragma endregion

        #pragma region Inicio Variables
        //Inicio de las variables booleanas
        colision_platform_01 = false;
        colision_platform_02 = false;
        start_piston_01 = false;
        start_piston_02 = false;

        exit = false;

        restart_Scene = false;

        canJump = false;

        #pragma endregion
       
    }

    void Scene::Update(RenderWindow& window)
    {
        do
        {
            m_clock.restart();

            // Process window events:

            exit = it->process(tr, window, circle.bodyEntity, window_height, physics_to_graphics_scale);

            // Update:

            physics_world.Step(delta_time, 8, 4);

            //Se instancia el ContactListener (MyListener) para el registro de las colisiones
            physics_world.SetContactListener(new MyListener(this));

            #pragma region Updates de objetos
            //updates de los pistones y plataformas
            trigger_piston_01.bodyEntity->SetLinearVelocity({ 0, 0 });

            if (colision_platform_01)
                Platform_Movable_01.update_platform(Platform_Movable_01, true, 2);
            else
                Platform_Movable_01.update_platform(Platform_Movable_01, false, 2);

            if(colision_platform_02)
                Platform_Movable_02.update_platform(Platform_Movable_02, true, 3);
            else
                Platform_Movable_02.update_platform(Platform_Movable_02, false, 3);

            //  void Entity::update_piston(Entity entity, float speedx, float speedy, float x0, float y0, float x1, float y1, bool active)
            if (start_piston_01)
                piston_01_pusher.update_piston(piston_01_pusher, 3, 0, 1, 1, 2, 3, true);
            else
                piston_01_pusher.update_piston(piston_01_pusher, 3, 0, 1, 1, 2, 3, false);

            if (start_piston_02)
                springTrap_Down.update_spring(joint_def, true);
            else
                springTrap_Down.update_spring(joint_def, false);
            #pragma endregion

            //Si se tiene que resetear la escena
            if (restart_Scene)
            {
                trigger_System_Particle.set_start_pos();
                circle.set_start_pos();
                circle.bodyEntity->SetLinearVelocity({ 0, 0 });
                restart_Scene = false;
            }

            // Render:
            //Creación de partículas que se spamean en una X e Y aleatoria
            m_VFXManager->AddParticleSystem(Vector2f(rand() % 50 + 900, rand() % 50 + 900));

            window.clear();

            tr.render(physics_world, window, physics_to_graphics_scale);

            // update del sistema de partículas
            sf::Time deltaTime = m_clock.restart();
            m_VFXManager->Update(deltaTime);
            m_VFXManager->Draw(&window);

            window.display();

            // Si resulta necesario se detiene la ejecución unos instantes para no exceder la tasa de
            // fotogramas por segundo deseada:

            float elapsed = m_clock.getElapsedTime().asSeconds();

            if (elapsed < target_time)
            {
                sleep(seconds(target_time - elapsed));
            }

            // Se restablece la estimación de la duración del siguiente fotograma:

            delta_time = m_clock.getElapsedTime().asSeconds();

        } while (not exit);
    }  
}