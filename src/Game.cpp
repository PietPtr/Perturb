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

    /*MassiveBodyData gasData;
    gasData.mass = 1.8986e27;
    gasData.position = Vector2f(0, 0);
    gasData.velocity = Vector2f(0, 0);
    gasData.radius = 69e6;
    gasData.color = Color(212, 184, 144);
    gasData.name = "Jupiter";

    MassiveBodyData moon1Data;
    moon1Data.mass = 8.931938e22;
    moon1Data.position = Vector2f(-420e6, 0);
    moon1Data.velocity = Vector2f(0, 17334);
    moon1Data.radius = 1.8e6;
    moon1Data.color = Color(255, 255, 0);
    moon1Data.name = "Io";

    MassiveBodyData moon2Data;
    moon2Data.mass = 4.799844e22;
    moon2Data.position = Vector2f(-664e6, 0);
    moon2Data.velocity = Vector2f(0, 13740);
    moon2Data.radius = 1.5e6;
    moon2Data.color = Color(255, 212, 184);
    moon2Data.name = "Europa";

    MassiveBodyData moon3Data;
    moon3Data.mass = 4.2332635e22;
    moon3Data.position = Vector2f(-1069e6, 0);
    moon3Data.velocity = Vector2f(0, 10880);
    moon3Data.radius = 2.6e6;
    moon3Data.color = Color(107, 107, 107);
    moon3Data.name = "Ganymede";

    MassiveBodyData moon4Data;
    moon4Data.mass = 4.2332635e22;
    moon3Data.position = Vector2f(-1869e6, 0);
    moon3Data.velocity = Vector2f(0, 10880);
    moon3Data.radius = 2.4e6;
    moon4Data.color = Color(122, 105, 100);
    moon4Data.name = "Callisto";*/

    MassiveBodyData gasData;
    gasData.mass = 4.2491e24;
    gasData.position = Vector2f(0, 0);
    gasData.velocity = Vector2f(0, 0);
    gasData.radius = 6e6;
    gasData.color = Color(255, 141, 79);
    gasData.name = "Caesar";
    gasData.prediction = &prediction;

    MassiveBodyData moon1Data;
    moon1Data.mass = 3.1440e21;
    moon1Data.position = Vector2f(-30e6, 0);
    moon1Data.velocity = Vector2f(0, 3082);
    moon1Data.radius = 0.3e6;
    moon1Data.color = Color(134, 217, 202);
    moon1Data.name = "Tessarius";
    moon1Data.prediction = &prediction;

    MassiveBodyData moon2Data;
    moon2Data.mass = 2.5158e22;
    moon2Data.position = Vector2f(-58e6, 0);
    moon2Data.velocity = Vector2f(0, 2216);
    moon2Data.radius = 0.42e6;
    moon2Data.color = Color(255, 255, 255);
    moon2Data.name = "Decurion";
    moon2Data.prediction = &prediction;

    MassiveBodyData moon3Data;
    moon3Data.mass = 3.9817e22;
    moon3Data.position = Vector2f(-103e6, 0);
    moon3Data.velocity = Vector2f(0, 1663);
    moon3Data.radius = 0.58e6;
    moon3Data.color = Color(171, 173, 109);
    moon3Data.name = "Centurion";
    moon3Data.prediction = &prediction;

    MassiveBodyData moon4Data;
    moon4Data.mass = 8.1337e19;
    moon4Data.radius = 75014;
    moon4Data.position = Vector2f(140e6, -30e6);
    moon4Data.velocity = Vector2f(0, 1520);
    moon4Data.color = Color(100, 100, 10);
    moon4Data.name = "Numerus";
    moon4Data.prediction = &prediction;

    bodies.push_back(MassiveBody(gasData));
    bodies.push_back(MassiveBody(moon1Data));
    bodies.push_back(MassiveBody(moon2Data));
    bodies.push_back(MassiveBody(moon3Data));
    bodies.push_back(MassiveBody(moon4Data));

    PhysicsObject::bodies = &bodies;

    // SPACECRAFT initialization happens at the start of every level
    // not at the start of every game instance.
    SpacecraftData playerData;
    playerData.maxThrust = 10e3;
    playerData.mass = 20e3;
    playerData.position = Vector2f(-103e6 + 2e6, 0);
    playerData.velocity = Vector2f(0, 2750);
    playerData.playerControlled = true;
    playerData.prediction = &prediction;
    spacecraft.push_back(Spacecraft(playerData));

    fillPrediction(64);
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
                std::cout << timeSpeed << "\n";
            }
            if (event.key.code == Keyboard::Period)
            {
                timeSpeed*=2;
                std::cout << timeSpeed << "\n";
            }
            if (event.key.code == Keyboard::Right)
                focusedBody++;
            if (event.key.code == Keyboard::Left)
                focusedBody--;
        }
        if (event.type == sf::Event::MouseWheelMoved)
        {
            if (event.mouseWheel.delta > 0)
                zoom/=2;
            if (event.mouseWheel.delta < 0)
                zoom*=2;
        }
        if (event.type == sf::Event::LostFocus)
            focus = false;
        if (event.type == sf::Event::GainedFocus)
            focus = true;
        if (event.type == Event::Resized)
        {
            windowWidth = event.size.width;
            windowHeight = event.size.height;
        }
    }

    realdt = clock.restart();
    totalTime += realdt;
    dt = realdt.asSeconds() * timeSpeed;
    UT += dt * timeSpeed;

    float SPEED = 1e8;
    if (focus)
    {
        if (Keyboard::isKeyPressed(Keyboard::W))
            viewPos.y -= SPEED * realdt.asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::A))
            viewPos.x -= SPEED * realdt.asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::S))
            viewPos.y += SPEED * realdt.asSeconds();
        if (Keyboard::isKeyPressed(Keyboard::D))
            viewPos.x += SPEED * realdt.asSeconds();
    }

    //std::cout << "UT: " << UT << /*", real time: " << totalTime.asSeconds() << ", dt: " << dt << ", timeSpeed: " << timeSpeed <<*/  "\n";

    for (int i = 0; i < timeSpeed; i++)
    {
        double approximatedt = dt;//(i / timeSpeed) * realdt.asSeconds();
        //std::cout << approximatedt << "\n";

        for (int b = 0; b < bodies.size(); b++)
            bodies[b].update(approximatedt, timeSpeed);
        for (int s = 0; s < spacecraft.size(); s++)
            spacecraft[s].updateCraft(approximatedt, timeSpeed);
    }

    focusedBody = focusedBody > bodies.size() - 1 ? -1 : focusedBody;
    focusedBody = focusedBody < -1 ? bodies.size() - 1 : focusedBody;

    if (focusedBody != -1)
        viewPos = bodies[focusedBody].getPosition();

    //std::cout << "FPS: " << 1.0 / realdt.asSeconds() << ", var: " <<  << "\n";

    frame++;
}

void Game::draw()
{
    if (!(Keyboard::isKeyPressed(Keyboard::C) && focus))
        window->clear();

    view.setSize(Vector2f(windowWidth, windowHeight));
    view.setCenter(viewPos);
    view.zoom(zoom);
    window->setView(view);

    for (int i = 0; i < bodies.size(); i++)
    {
        bodies.at(i).draw(window, zoom, i);
    }
    for (int i = 0; i < spacecraft.size(); i++)
    {
        spacecraft.at(i).draw(window, zoom, i);
    }

    window->display();
}

void Game::fillPrediction(int length)
{
    predictionBodies.clear();
    predictionSpacecraft.clear();

    predictionBodies = bodies;
    predictionSpacecraft = spacecraft;

    double predictiondt = timeSpeed;

    for (int i = 0; i < length; i++)
    {
        std::vector<Vector2f> bodyPositions;
        std::vector<Vector2f> spacecraftPositions;
        for (int b = 0; b < predictionBodies.size(); b++)
        {
            predictionBodies[b].update(predictiondt, timeSpeed);
            bodyPositions.push_back(predictionBodies.at(b).getPosition());
        }
        for (int s = 0; s < spacecraft.size(); s++)
        {
            predictionSpacecraft[s].updateCraft(predictiondt, timeSpeed);
            spacecraftPositions.push_back(predictionSpacecraft.at(s).getPosition());
        }
        SpaceState state;
        state.bodyPositions = bodyPositions;
        state.spacecraftPositions = spacecraftPositions;
        state.UT = UT + i * predictiondt;
        prediction.push_back(state);
    }
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
