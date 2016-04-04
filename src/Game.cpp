#include <SFML/Graphics.hpp>
#include "Game.h"

using namespace sf;

Game::Game(RenderWindow* _window)
{
    window = _window;
}

void Game::initialize()
{
    loadAudio(audioFileNames);
    loadTextures(textureFileNames);

    MassiveBodyData gasData;
    gasData.mass = 4.2332635e24;
    gasData.position = Vector2f(0, 0);
    gasData.velocity = Vector2f(0, 0);
    gasData.radius = 6e6;
    gasData.name = "JoolTEMP";

    MassiveBodyData moon1Data;
    moon1Data.mass = 2.9397663e22;
    moon1Data.position = Vector2f(-27e6, 0);
    moon1Data.velocity = Vector2f(0, 0);
    moon1Data.radius = 0.5e6;
    moon1Data.name = "LaytheTEMP";

    MassiveBodyData moon2Data;
    moon2Data.mass = 3.1088028e21;
    moon2Data.position = Vector2f(-43e6, 0);
    moon2Data.velocity = Vector2f(0, 0);
    moon2Data.radius = 0.3e6;
    moon2Data.name = "VallTEMP";

    MassiveBodyData moon3Data;
    moon3Data.mass = 4.2332635e22;
    moon3Data.position = Vector2f(-68e6, 0);
    moon3Data.velocity = Vector2f(0, 0);
    moon3Data.radius = 0.6e6;
    moon3Data.name = "TyloTEMP";

    bodies.push_back(MassiveBody(gasData));
    bodies.push_back(MassiveBody(moon1Data));
    bodies.push_back(MassiveBody(moon2Data));
    bodies.push_back(MassiveBody(moon3Data));

    PhysicsObject::bodies = &bodies;
}

void Game::update()
{
    Event event;
    while (window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window->close();
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
            if (event.key.code == Keyboard::Comma)
            {
                timeSpeed/=2;
            }
            if (event.key.code == Keyboard::Period)
            {
                timeSpeed*=2;
            }
        }
    }

    sfmldt = clock.restart();
    totalTime += sfmldt;
    dt = sfmldt.asSeconds() * timeSpeed;
    UT += dt;

    //std::cout << "UT: " << UT << ", dt: " << dt << ", timeSpeed: " << timeSpeed << ", real time: " << totalTime.asSeconds() << "\n";
    for (int i = 0; i < bodies.size(); i++)
        bodies[i].update(dt);

    frame++;
}

void Game::draw()
{
    window->clear();

    view.setSize(Vector2f(windowWidth, windowHeight));
    view.setCenter(viewPos);
    view.zoom(1.5e5);
    window->setView(view);

    for (int i = 0; i < bodies.size(); i++)
    {
        bodies.at(i).draw(window);
    }

    window->display();
}

bool Game::isWindowOpen()
{
    return window->isOpen();
}

void Game::loadAudio(std::vector<std::string> audioFileNames)
{
    for (int i = 0; i < audioFileNames.size(); i++)
    {
        sfx.push_back(new Audio());
        sfx.back()->init(audioFileNames[i]);
    }
}

void Game::loadTextures(std::vector<std::string> textureFileNames)
{
    for (int i = 0; i < textureFileNames.size(); i++)
    {
        //textures.push_back()
        Texture texture;
        if (!texture.loadFromFile("textures/" + textureFileNames.at(i)))
            window->close();
    }
}

int Game::randint(int low, int high)
{
    int value = rand() % (high + 1 - low) + low;
    srand(totalTime.asMicroseconds() * value * rand());

    return value;
}
