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
    playerControlled = data.playerControlled;
    prediction = data.prediction;
    color = Color(255, 255, 255);
}

void Spacecraft::updateCraft(double dt, double timeSpeed)
{
    const float THROTTLESPEED = 120; // %/s
    if (Keyboard::isKeyPressed(Keyboard::Z))
        throttle = 100;
    if (Keyboard::isKeyPressed(Keyboard::X))
        throttle = 0;
    if (Keyboard::isKeyPressed(Keyboard::LShift))
        throttle += THROTTLESPEED * dt;
    if (Keyboard::isKeyPressed(Keyboard::LControl))
        throttle -= THROTTLESPEED * dt;

    throttle = throttle > 100 ? 100 : throttle;
    throttle = throttle < 0   ? 0   : throttle;

    thrust = (throttle / 100.0) * maxThrust;

    //std::cout << throttle << "\n";

    update(dt, timeSpeed);
}

void Spacecraft::draw(RenderWindow* window, double zoom, int index)
{
    CircleShape body;
    body.setPosition(position);
    body.setRadius(zoom);
    window->draw(body);

    //draw prediction;

    drawPrediction(true, index, zoom, window);

    //drawForces(window);
}
