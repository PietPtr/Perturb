#include "MassiveBody.h"

using namespace sf;

MassiveBody::MassiveBody(MassiveBodyData data)
{
    mass = data.mass;
    velocity = data.velocity;
    position = data.position;
    radius = data.radius;
    name = data.name;
    color = data.color;
}

void MassiveBody::draw(RenderWindow* window)
{
    CircleShape body;
    body.setRadius(radius);
    //body.setFillColor(Color(position.x / 68e6 * 255, 0, 0));
    body.setPosition(position);
    body.setOrigin(radius, radius);
    body.setFillColor(color);
    window->draw(body);

    //drawForces(window);
}
