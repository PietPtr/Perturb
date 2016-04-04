#include "PhysicsObject.h"
#include <iostream>

using namespace sf;

PhysicsObject::PhysicsObject()
{

}

std::vector<MassiveBody>* PhysicsObject::bodies = nullptr;

void PhysicsObject::update(double dt)
{
    // calculate all forces (gravitational, thrust, perhaps even aerobraking later?)
    // done fres = ma
    // done apply acceleration on velocity
    // done apply velocity on position

    forces.clear();

    for (int i = 0; i < bodies->size(); i++)
    {
        if (name != bodies->at(i).name)
        {
            float dx = position.x - bodies->at(i).position.x;
            float dy = position.x - bodies->at(i).position.x;

            double distance = sqrt(pow(dx, 2) + pow(dy, 2));

            double magnitude = G * (mass * bodies->at(i).mass) / (pow(distance, 2));

            Vector2f gravitation;
            gravitation.x = (magnitude * dx) / distance;
            gravitation.y = (magnitude * dy) / distance;

            forces.push_back(gravitation);

            //std::cout << "distance: " << distance << ", magnitude: " << magnitude << "\n";
            std::cout << gravitation.x << " " << gravitation.y << "\n";
        }
    }

    Vector2f sumForce = Vector2f(0, 0);
    for (int i = 0; i < forces.size(); i++)
        sumForce += forces[i];

    Vector2f acceleration = Vector2f(sumForce.x / mass, sumForce.y / mass);
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    //std::cout << "acceleration: " << acceleration.x << " m/s2, velocity: " << velocity.x << " m/s, position: " << position.x << " m\n";
    //std::cout << "acceleration: " << acceleration.y << " m/s2, velocity: " << velocity.y << " m/s, position: " << position.y << " m\n";
    std::cout << "\n";
}

void PhysicsObject::drawForces(RenderWindow* window)
{
    for (int i = 0; i < forces.size(); i++)
    {
        float mod = 1;

        Vertex force[] =
        {
            Vertex(position),
            Vertex(position + Vector2f(forces.at(i).x / mod, forces.at(i).y / mod))
        };
        force[0].color = Color::Red;
        force[1].color = Color::Red;
        window->draw(force, 2, Lines);
    }
}








