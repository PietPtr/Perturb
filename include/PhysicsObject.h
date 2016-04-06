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

        Vector2f getPosition() { return position; }

        static std::vector<MassiveBody>* bodies;
    protected:
        Vector2f position; // m
        Vector2f velocity; // m / s
        float thrust = 0;  // N
        double mass;       // kg
        double rotation = 0;
        std::vector<Vector2f> forces;
        std::string name;
    private:
};

struct MassiveBodyData
{
    double mass;
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
        void draw(RenderWindow* window, double zoom);
        std::string getName() { return name; }
    protected:
    private:
        int radius;
        Color color;
};

struct SpacecraftData
{
    double maxThrust;
    Vector2f position;
    Vector2f velocity;
    double mass = 20e3; // dry mass
    double fuel = 20e3;
};

class Spacecraft : public PhysicsObject
{
    public:
        Spacecraft(SpacecraftData data);
        void updateCraft(double dt);
        void draw(RenderWindow* window, double zoom);
    protected:
    private:
        double throttle = 0;
        double maxThrust = 0;
        double wetMass;             // kg
        double fuel;                // kg
        double specificImpulse;     // s


};

#endif // PHYSICSOBJECT_H
