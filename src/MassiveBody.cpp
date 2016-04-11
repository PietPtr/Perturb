#include "PhysicsObject.h"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

MassiveBody::MassiveBody(MassiveBodyData data)
{
    mass = data.mass;
    velocity = data.velocity;
    position = data.position;
    radius = data.radius;
    name = data.name;
    color = data.color;
    prediction = data.prediction;
}


void MassiveBody::draw(RenderWindow* window, double zoom, int index)
{
    double drawSize = radius / zoom; // draw size in pixels

    if ((int)drawSize <= 1)
    {
        CircleShape body;
        body.setPosition(position);
        if (Keyboard::isKeyPressed(Keyboard::V))
            body.setRadius(zoom * 100);
        else
            body.setRadius(zoom);
        body.setFillColor(color);
        window->draw(body);
    }
    else
    {
        CircleShape body;
        body.setRadius(radius);
        //body.setFillColor(Color(position.x / 68e6 * 255, 0, 0));
        body.setPosition(position);
        body.setOrigin(radius, radius);
        body.setFillColor(color);
        window->draw(body);
    }

    float dx = position.x - bodies->at(0).position.x;
    float dy = position.y - bodies->at(0).position.y;

    double distance = sqrt(pow(dx, 2) + pow(dy, 2));

    CircleShape SOI;
    SOI.setRadius(distance * pow(mass / bodies->at(0).mass, 0.4));
    SOI.setPosition(position);
    SOI.setOrigin(SOI.getRadius(), SOI.getRadius());
    SOI.setOutlineColor(Color(color.r, color.g, color.b, 20));
    SOI.setOutlineThickness(zoom);
    SOI.setFillColor(Color(0, 0, 0, 0));
    if (Keyboard::isKeyPressed(Keyboard::F8))
        window->draw(SOI);

    //sstd::cout << SOI.getRadius() << "\n";

    drawPrediction(false, index, zoom, window);
    //drawForces(window);
}
