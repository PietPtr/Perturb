#ifndef PHYSICSOBJECT_H
#define PHYSICSOBJECT_H
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;

const double G = 6.67408e-11;

class MassiveBody;

struct SpaceState
{
    std::vector<Vector2f> bodyPositions;
    std::vector<Vector2f> spacecraftPositions;
    long double UT;
};

class PhysicsObject
{
    public:
        PhysicsObject();
        void update(double dt, double timeSpeed);
        Vector2f calculateAcceleration(Vector2f position, std::vector<MassiveBody>* bodyptr);
        void drawForces(RenderWindow* window);
        void drawPrediction(bool isSpacecraft, int index, double zoom, RenderWindow* window);

        Vector2f getPosition() { return position; }

        static std::vector<MassiveBody>* bodies;
    protected:
        Vector2f position; // m
        Vector2f velocity; // m / s
        float thrust = 0;  // N
        double mass;       // kg
        double rotation = 0;
        std::vector<Vector2f> forces;
        std::vector<SpaceState>* prediction;
        std::string name;
        Color color;
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
    std::vector<SpaceState>* prediction;
};

class MassiveBody : public PhysicsObject // Moons and the main gas giant.
{
    public:
        MassiveBody(MassiveBodyData data);
        void draw(RenderWindow* window, double zoom, int index);
        std::string getName() { return name; }
    protected:
    private:
        int radius;
};

struct SpacecraftData
{
    double maxThrust;
    Vector2f position;
    Vector2f velocity;
    double mass = 20e3; // dry mass
    double fuel = 20e3;
    bool playerControlled = false;
    std::vector<SpaceState>* prediction;
};

class Spacecraft : public PhysicsObject
{
    public:
        Spacecraft(SpacecraftData data);
        void updateCraft(double dt, double timeSpeed);
        void draw(RenderWindow* window, double zoom, int index);
    protected:
    private:
        double throttle = 0;
        double maxThrust = 0;
        double wetMass = 0;         // kg
        double fuel = 0;            // kg
        double specificImpulse = 0; // s
        bool playerControlled = false;


};

#endif // PHYSICSOBJECT_H
