/**
* @file Entity.cpp
* Copyright (c) David Martín
* @author David Martín Almazán
* @date 15 de Abril de 2021
* @section LICENSE
* Licencia MIT
* @section DESCRIPTION
* Script que guarda el body con sus propias fixtures y la posición inicial de cada objeto de la escena
**/

#include "Entity.hpp"

namespace Engine
{
    Entity::Entity()
    {
        x0 = 0;
        y0 = 0;
        x1 = 0;
        y1 = 0;

        sidePlatform = false;
    }

    ///Función para crear un circulo 
    b2Body* Entity::create_circle(b2World& physics_world, b2BodyType body_type, float x, float y, float radius, uintptr_t tag, short cBits, short mBits, short gIndex)
    {
        // Se crea el body:
        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set(x, y);                            
        
        // Se guarda la posición inicial absoluta
        //get_start_pos();
        initialPos = { x, y };

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:

        b2CircleShape body_shape;

        body_shape.m_radius = radius;

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 2.00f;
        body_fixture.restitution = 0.0f;
        body_fixture.friction = 0.50f; 

        //Se le adjunta la categoría de Bits (su propia capa), la mascara de Bits (con las capas que colisiona) y el grupo al que pertenece
        body_fixture.filter.categoryBits = cBits;
        body_fixture.filter.maskBits = mBits;
        body_fixture.filter.groupIndex = gIndex;


        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata
        body->GetUserData().pointer = tag;
       
        return body;
    }

    ///Función para crear un cubo
    b2Body* Entity::create_box(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height, uintptr_t tag, short cBits, short mBits, short gIndex)
    {
        // Se crea el body:
        b2BodyDef body_definition;

        body_definition.type = body_type;
        body_definition.position.Set(x, y);       

        // Se guarda la posición inicial absoluta
        initialPos = { x, y };

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:
        b2PolygonShape body_shape;

        body_shape.SetAsBox(width, height);

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.50f;
        body_fixture.friction = 0.50f;

        //Se le adjunta la categoría de Bits (su propia capa), la mascara de Bits (con las capas que colisiona) y el grupo al que pertenece
        body_fixture.filter.categoryBits = cBits;
        body_fixture.filter.maskBits = mBits;
        body_fixture.filter.groupIndex = gIndex;

        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata
        body->GetUserData().pointer = tag;

        return body;
    }

    ///Función para crear líneas, usada para los bordes
    b2Body* Entity::create_edge(b2World& physics_world, b2BodyType body_type, float x0, float y0, float x1, float y1, uintptr_t tag)
    {
        // Se crea el body:

        b2BodyDef body_definition;

        body_definition.type = body_type;
        
        // Posición inicial absoluta
        body_definition.position.Set(0.f, 0.f);                        

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:
        b2EdgeShape body_shape;

        body_shape.SetTwoSided(b2Vec2(x0, y0), b2Vec2(x1, y1));        // Coordenadas locales respecto al centro del body

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;

        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata
        body->GetUserData().pointer = tag;

        return body;
    }

    ///Función para crear una plataforma sólida usada por ejemplo para crear el suelo
    b2Body* Entity::create_solid_platform(b2World& physics_world, float x, float y, float width, float height, uintptr_t tag, short cBits, short mBits, short gIndex)
    {
        // Se crea el body:
        b2BodyDef body_definition;

        body_definition.type = b2_kinematicBody;
        
        // Posición inicial absoluta
        body_definition.position.Set(x, y);     

        initialPos = { x, y };

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:
        b2PolygonShape body_shape;

        body_shape.SetAsBox(width, height);

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.50f;
        body_fixture.friction = 0.50f;

        //Se le adjunta la categoría de Bits (su propia capa), la mascara de Bits (con las capas que colisiona) y el grupo al que pertenece
        body_fixture.filter.categoryBits = cBits;
        body_fixture.filter.maskBits = mBits;
        body_fixture.filter.groupIndex = gIndex;

        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata
        body->GetUserData().pointer = tag;

        return body;
    }

    ///Función para crear una plataforma que se mueve
    b2Body* Entity::create_moving_platform(b2World& physics_world, float pointxstart, float pointystart, float pointxend, float pointyend, float x, float y, float width, float height, bool side, uintptr_t tag, short cBits, short mBits, short gIndex)
    {
        //Puntos para despues poner los límites al movimiento
        x0 = pointxstart;
        y0 = pointystart;
        x1 = pointxend;
        y1 = pointyend;

        //Se elige el lado
        sidePlatform = side;

        // Se crea el body:
        b2BodyDef body_definition;

        body_definition.type = b2_kinematicBody; 
        
        // Posición inicial absoluta
        body_definition.position.Set(x, y);      

        initialPos = { x, y };

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:
        b2PolygonShape body_shape;

        body_shape.SetAsBox(width, height);

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 1.00f;
        body_fixture.restitution = 0.0f;
        body_fixture.friction = 0.50f;

        //Se le adjunta la categoría de Bits (su propia capa), la mascara de Bits (con las capas que colisiona) y el grupo al que pertenece
        body_fixture.filter.categoryBits = cBits;
        body_fixture.filter.maskBits = mBits;
        body_fixture.filter.groupIndex = gIndex;

        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata y se le aplica una gravedad de 9.8
        body->GetUserData().pointer = tag;
        body->SetGravityScale(9.8);

        return body;
    }

    ///Función para crear polígonos, usada para rampas
    b2Body* Entity::create_polygon(b2World& physics_world, b2BodyType body_type, b2Vec2 points [], int32 count, uintptr_t tag, short cBits, short mBits, short gIndex)
    {
        // Se crea el body:
        b2BodyDef body_definition;

        body_definition.type = body_type;

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:
        b2PolygonShape polygon;

        polygon.Set(points, count);

        b2FixtureDef body_fixture;

        body_fixture.shape = &polygon;

        //Se le adjunta la categoría de Bits (su propia capa), la mascara de Bits (con las capas que colisiona) y el grupo al que pertenece
        body_fixture.filter.categoryBits = cBits;
        body_fixture.filter.maskBits = mBits;
        body_fixture.filter.groupIndex = gIndex;

        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata
        body->GetUserData().pointer = tag;

        return body;
    }

    ///Función para crear triggers
    b2Body* Entity::create_trigger(b2World& physics_world, b2BodyType body_type, float x, float y, float width, float height, uintptr_t tag, short cBits, short mBits, short gIndex)
    {
        // Se crea el body:
        b2BodyDef body_definition;

        body_definition.type = body_type;
        
        // Posición inicial absoluta
        body_definition.position.Set(x, y);

        initialPos = { x, y };

        b2Body* body = physics_world.CreateBody(&body_definition);

        // Se añande una fixture:
        b2PolygonShape body_shape;

        body_shape.SetAsBox(width, height);

        b2FixtureDef body_fixture;

        body_fixture.shape = &body_shape;
        body_fixture.density = 4.00f;
        body_fixture.restitution = 0.f;
        body_fixture.friction = 0.50f;

        //Se le adjunta la categoría de Bits (su propia capa), la mascara de Bits (con las capas que colisiona) y el grupo al que pertenece
        body_fixture.filter.categoryBits = cBits;
        body_fixture.filter.maskBits = mBits;
        body_fixture.filter.groupIndex = gIndex;

        body->CreateFixture(&body_fixture);

        //Se le añade un tag que se guarda en la variable pointer del userdata y le aplica una gravedad de 2
        body->GetUserData().pointer = tag;
        body->SetGravityScale(2.f);

        return body;
    }

    /// Función para crear el joint que se usará en los ventiladores (todo el rato girando)
    b2RevoluteJoint* Entity::create_revolute_joint_ventilador(b2World& physics_world, b2Body* body_a, b2Body* body_b, float min_angle, float max_angle, bool enable_motor)
    {
        b2RevoluteJointDef joint_def;

        //Recoge los dos cuerpos:
        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;

        //Se le pone las características tales como enableMotor para moverse, o los ángulos máximos
        joint_def.enableMotor = enable_motor;
        joint_def.collideConnected = false;

        joint_def.lowerAngle = min_angle * b2_pi / 180;
        joint_def.upperAngle = max_angle * b2_pi / 180;

        return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
    }

    ///Función para crear un joint normal
    b2RevoluteJoint* Entity::create_revolute_joint(b2World& physics_world, b2Body* body_a, b2Body* body_b, float min_angle, float max_angle, bool enable_motor)
    {
        b2RevoluteJointDef joint_def;

        //Recoge los dos cuerpos:
        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;

        //Se le pone las características tales como enableMotor para moverse, o los ángulos máximos, o mover el segundo objeto a una posicion
        joint_def.enableMotor = enable_motor;
        joint_def.localAnchorB = { 0.f, 0.2f };
        joint_def.enableLimit = true;

        joint_def.lowerAngle = min_angle * b2_pi / 180;
        joint_def.upperAngle = max_angle * b2_pi / 180;

        return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
    }

    ///Función para crear un joint para juntar dos entidades : Joint básico
    b2RevoluteJoint* Entity::create_revolute_joint_entities(b2World& physics_world, b2Body* body_a, b2Body* body_b, float x, float y, bool enable_motor)
    {
        b2RevoluteJointDef joint_def;

        //Recoge los dos cuerpos:
        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;

        //Se le pone las características tales como enableMotor para moverse, o mover el segundo objeto a una posicion
        joint_def.localAnchorB = { x, y };
        joint_def.enableMotor = enable_motor;

        return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
    }

    ///Función para crear los joints para las catapultas o para paredes que no se quieran mover y no pertenezcan al escenario : Joint complejo
    b2RevoluteJoint* Entity::create_revolute_joint_catapult(b2World& physics_world, b2Body* body_a, b2Body* body_b, float x, float y, float min_angle, float max_angle, bool enable_motor)
    {
        b2RevoluteJointDef joint_def;

        //Recoge los dos cuerpos:
        joint_def.bodyA = body_a;
        joint_def.bodyB = body_b;

        //Se le pone las características tales como enableMotor para moverse, o los ángulos máximos, o mover el segundo objeto a una posicion
        joint_def.enableMotor = enable_motor;
        joint_def.localAnchorB = { x, y };
        joint_def.enableLimit = true;

        joint_def.lowerAngle = min_angle * b2_pi / 180;
        joint_def.upperAngle = max_angle * b2_pi / 180;

        return dynamic_cast<b2RevoluteJoint*>(physics_world.CreateJoint(&joint_def));
    }

    ///Función que lleva el update de la plataforma para moverse. Tiene en cuenta los puntos que le dimos con anterioridad y que recogió la entidad
    void Entity::update_platform(Entity entity, bool active, float speed)
    {
        //Si el lado es falso, se moverá verticalmente
        if (!entity.sidePlatform)
        {
            //Si esta activa
            if (active) 
                //Si esta por debajo del valor x final:
                if(entity.bodyEntity->GetPosition().x < entity.x0)
                    //Se le añade una speed en el eje de las X
                    entity.bodyEntity->SetLinearVelocity({ speed, 0 });

            //Si no esta activa
            else if (!active) 
                    //Si esta por encima del valor x inicial:
                    if(entity.bodyEntity->GetPosition().x > entity.x1)
                        //Se le resta una speed en el eje de las X
                        entity.bodyEntity->SetLinearVelocity({ -speed, 0 });
        }
        //Si el lado es verdadero, se moverá horizontalmente
        else
        {
            //Si esta activo 
            if (active)
            {
                //Si esta por debajo del valor Y final: 
                if (entity.bodyEntity->GetPosition().y <= entity.y1)
                    //Se le añade una speed en el eje de las Y
                    entity.bodyEntity->SetLinearVelocity({ 0, speed });
                else 
                    //Se queda parada
                    entity.bodyEntity->SetLinearVelocity({ 0, 0 });
            }

            //Si no esta activo
            else
            {
                //Si esta por encima del valor Y final: 
                if (entity.bodyEntity->GetPosition().y >= entity.y0)
                    //Se le resta una speed en el eje de las Y
                    entity.bodyEntity->SetLinearVelocity({ 0, -speed });
                else
                    //Se queda parada
                    entity.bodyEntity->SetLinearVelocity({ 0, 0 });
            }
        }
    }

    ///Función que lleva el update del piston. Se le pasa los puntos y si esta activa
    void Entity::update_piston(Entity entity, float speedx, float speedy, float x0, float y0, float x1, float y1, bool active)
    {
        //Si no esta activa
        if (!active)
        {
            //Se comprueba la posición en el eje de las X, y que sea mayor al X inicial
            if (entity.bodyEntity->GetPosition().x > x0)
                //Se le añade una speed negativa en el eje de las X
                entity.bodyEntity->SetLinearVelocity({ -speedx, speedy });
            else
                //Se queda parado
                entity.bodyEntity->SetLinearVelocity({ 0, 0 });
        }
        //Si esta activa
        else 
            //Se mueve en el eje de las X con una speed siempre que este por debajo del valor final
            if (entity.bodyEntity->GetPosition().x <= x1)
                entity.bodyEntity->SetLinearVelocity({ speedx, speedy });
            else
                //Se queda parado si ha llegado al tope
                entity.bodyEntity->SetLinearVelocity({ 0, 0 });

    }

    ///Función que lleva el update de los pistones y ventiladores.
    void Entity::update_spring(b2RevoluteJoint* joint, bool active)
    {
        //Se coge un valor aleatorio entre el 20 y el 1
        float speed = rand() % 20 + 1;

        //Si esta activo
        if (active)
        {
            //Se le aplica una speed, y no supera los 75.f
            joint->SetMaxMotorTorque(75.f);
            joint->SetMotorSpeed(speed);
        }
        else
        {
            //Se le aplica una speed negativa, y no supera los 75.f
            joint->SetMaxMotorTorque(75.f);
            joint->SetMotorSpeed(-10.f);
        }

    }

    ///Función para recoger la posición donde se inicia la pelota
    void Entity::get_start_pos() { initialPos = bodyEntity->GetPosition(); }

    ///Función para setear la posición de la pelota
    void Entity::set_start_pos() { bodyEntity->SetTransform(initialPos, bodyEntity->GetAngle()); }
}