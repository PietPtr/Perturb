#include "PhysicsObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

Spacecraft::Spacecraft(SpacecraftData data)
{
    maxThrust = data.maxThrust;
    position = data.position;
    velocity = data.velocity;
    mass = data.mass;
}

void Spacecraft::draw(RenderWindow* window, double zoom)
{
    CircleShape body;
    body.setPosition(position);
    body.setRadius(zoom);
    window->draw(body);

    //drawForces(window);
}
