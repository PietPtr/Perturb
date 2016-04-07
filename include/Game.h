#include <SFML/Graphics.hpp>
#include <iostream>
#include "Audio.h"
#include "PhysicsObject.h"

using namespace sf;

class Game
{
    public:
        Game(RenderWindow* window);
        void initialize();
        void update();
        void draw();
        bool isWindowOpen();

        void loadAudio(std::vector<std::string> fileNames);
        void loadTextures(std::vector<std::string> fileNames);

        int randint(int low, int high, int seed);
        int randint(int low, int high);
    protected:
    private:
        RenderWindow* window;
        View view;
        Vector2f viewPos { 0, 0 };
        double zoom = 3e5;
        int focusedBody = 3;
        bool focus = true;

        int windowWidth = 1280; // px
        int windowHeight = 720; // px

        Time sfmldt;
        Time totalTime;
        Clock clock;
        int frame = 0;
        double timeSpeed = 1;
        double UT = 0;        // s
        double dt = 0;        // s

        std::vector<std::string> audioFileNames { };
        std::vector<std::string> textureFileNames { };

        std::vector<Audio*> sfx;
        std::vector<Texture> textures;

        std::vector<MassiveBody> bodies;
        std::vector<Spacecraft> spacecraft;
};
