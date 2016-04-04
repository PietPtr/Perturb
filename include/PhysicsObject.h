#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

const double G = 6.67408e-11;

class MassiveBody;

class PhysicsObject
{
    public:
        PhysicsObject();
        void update(double dt);
        void drawForces(RenderWindow* window);
        static std::vector<MassiveBody>* bodies;
    protected:
        Vector2f position; // m
        Vector2f velocity; // m / s
        float thrust;      // N
        double mass;       // kg
        std::vector<Vector2f> forces;
        std::string name;
    private:
};

struct MassiveBodyData
{
    double  mass;
    int radius;
    Vector2f position;
    Vector2f velocity;
    std::string name;
    Color color;
};

class MassiveBody : public PhysicsObject // Moons and the main gas giant.
{
    public:
        MassiveBody(MassiveBodyData data);
        void draw(RenderWindow* window);
        std::string getName() { return name; }
    protected:
    private:
        int radius;
        Color color;
};

#endif // PHYSICSOBJECT_H
