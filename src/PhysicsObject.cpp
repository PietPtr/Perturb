#include "PhysicsObject.h"
#include <iostream>

using namespace sf;

PhysicsObject::PhysicsObject()
{

}

std::vector<MassiveBody>* PhysicsObject::bodies = nullptr;

Vector2f PhysicsObject::calculateAcceleration(Vector2f pos, std::vector<MassiveBody>* bodyptr)
{
    forces.clear();

    for (int i = 0; i < bodyptr->size(); i++)
    {
        if (name != bodyptr->at(i).name)
        {
            float dx = pos.x - bodyptr->at(i).position.x;
            float dy = pos.y - bodyptr->at(i).position.y;

            double distance = sqrt(pow(dx, 2) + pow(dy, 2));

            double magnitude = -G * (mass * bodyptr->at(i).mass) / (pow(distance, 2));

            Vector2f gravitation;
            gravitation.x = (magnitude * dx) / distance;
            gravitation.y = (magnitude * dy) / distance;

            forces.push_back(gravitation);

            //std::cout << "distance: " << distance << ", magnitude: " << magnitude << "\n";
            //std::cout << gravitation.x << " " << gravitation.y << "\n";
        }
    }

    if (thrust != 0)
    {
        Vector2f thrustForce;
        thrustForce.x = cos(rotation) * thrust;
        thrustForce.y = sin(rotation) * thrust;
        forces.push_back(thrustForce);
    }

    Vector2f sumForce = Vector2f(0, 0);
    for (int i = 0; i < forces.size(); i++)
        sumForce += forces[i];

    return Vector2f(sumForce.x / mass, sumForce.y / mass);
}


void PhysicsObject::update(double dt, double timeSpeed)
{
    Vector2f acceleration = calculateAcceleration(position, bodies);
    velocity.x += acceleration.x * dt;
    velocity.y += acceleration.y * dt;
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;

    predict(timeSpeed);

    //std::cout << "acceleration: " << acceleration.x << " m/s2, velocity: " << velocity.x << " m/s, position: " << position.x << " m\n";
    //std::cout << "acceleration: " << acceleration.y << " m/s2, velocity: " << velocity.y << " m/s, position: " << position.y << " m\n";
    //std::cout << "\n";
}

void PhysicsObject::predict(double timeSpeed)
{

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
        //std::cout << forces.at(i).x << ", " << forces.at(i).y << "\n";
    }
    //std::cout << "drawing " << forces.size() << " forces..\n";
}








