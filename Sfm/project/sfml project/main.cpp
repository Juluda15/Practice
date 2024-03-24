#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include "SFML/Graphics.hpp"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

void TryLoadFont(sf::Font& font, std::string path);
int randomgen();

int main()
{
    sf::RenderWindow window(sf::VideoMode(700, 700), "Game");
    sf::Event event1;
    sf::CircleShape circ(50);
    circ.setFillColor(sf::Color::White);
    circ.setPosition(sf::Vector2f(randomgen(), randomgen()));
    bool circ2 = false;
    bool circledrawn = false;
    bool click = false;
    int count = 0;
    int rounds = 0;
    const int maxRounds = 8;
    sf::Font font;
    TryLoadFont(font, "8bitfont.ttf");
    sf::Text remainingtime("", font, 22);
    remainingtime.setFillColor(sf::Color::Red);
    remainingtime.setPosition(sf::Vector2f(200, 345));
    sf::Text accuracy("", font, 22);
    accuracy.setFillColor(sf::Color::Red);
    accuracy.setPosition(sf::Vector2f(206, 345));
    sf::Clock clock;
    sf::Clock clickclock;
    float cdown = 3.0f;
    float elapsed = 0.0f;
    float time = 0.0f;
    std::vector<float> times;

    while (window.isOpen())
    {
        while (window.pollEvent(event1))
        {
            if (event1.type == sf::Event::Closed)
                window.close();
        }
        elapsed = clock.getElapsedTime().asSeconds();
        float remtime = cdown - elapsed;
        std::string remtimestring = std::to_string(remtime);

        if (!circ2 && remtime <= 0.0f && circledrawn)
        {
            circledrawn = false;
            click = false;
            remainingtime.setString("");
            accuracy.setString("");
            if (rounds < maxRounds) 
            {
                rounds = 0;
                std::cout << "All Times: ";
                for (size_t i = 0; i < times.size(); ++i) {
                    std::cout << times[i] << " ";
                }
                std::cout << std::endl;
                times.clear();
            }
        }
        if (!circ2 && remtime <= 0.0f)
        {
            if (!circledrawn)
            {
                circ.setPosition(sf::Vector2f(randomgen(), randomgen()));
                circledrawn = true;
                circ2 = true;
                count = 0;
                rounds++;
                time = 0.0f;
            }
        }
        window.clear(sf::Color::Black);
        if (remtime > 0.0f && !circledrawn)
            remainingtime.setString("Remaining Time: " + remtimestring);
        else
            remainingtime.setString("");
        if (circ2)
        {
            window.draw(circ);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && circ.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
            {
                if (count < maxRounds)
                {
                    time = clock.getElapsedTime().asSeconds();
                    circ2 = false;
                    circ.setPosition(sf::Vector2f(-1000, -1000));
                    count++;
                    click = true;
                    clock.restart();
                }
            }
        }
        window.draw(remainingtime);
        if (click && time > 0) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << time - 3.0f;
            accuracy.setString("You were this fast: " + ss.str());
            window.draw(accuracy);
        }
        window.display();
    }
}

void TryLoadFont(sf::Font& font, std::string path)
{
    if (!font.loadFromFile(path))
    {
        std::cerr << "Failed to load font: " << path << std::endl;
        exit(EXIT_FAILURE);
    }
}

int randomgen()
{
    std::uniform_int_distribution<> dis(50, 600);
    int rndnum = dis(gen);
    return rndnum;
}