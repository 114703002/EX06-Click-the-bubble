#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Bubble.h" 

int main() {
    
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Click the Bubble - EX06");
    window.setFramerateLimit(60); 

    std::vector<Bubble> bubbles; 
    int score = 0;              
    sf::Clock spawnClock;        

    sf::Font font;
    bool hasFont = font.loadFromFile("arial.ttf");
    sf::Text scoreText;
    if (hasFont) {
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
    } else {
        std::cout << "Warning: Cannot load arial.ttf. Score won't be displayed." << std::endl;
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float mouseX = static_cast<float>(event.mouseButton.x);
                    float mouseY = static_cast<float>(event.mouseButton.y);

                    for (int i = bubbles.size() - 1; i >= 0; --i) {
                        if (bubbles[i].checkClick(mouseX, mouseY)) {
                            score += bubbles[i].getPoints(); 
                            break; 
                        }
                    }
                }
            }
        }

        if (spawnClock.getElapsedTime().asSeconds() > 1.0f) {
            float randomX = static_cast<float>(rand() % 700 + 50);
            float randomY = static_cast<float>(rand() % 500 + 50);
            float randomRadius = static_cast<float>(rand() % 30 + 20); 
            
            bubbles.push_back(Bubble(randomX, randomY, randomRadius));
            spawnClock.restart();
        }

        bubbles.erase(std::remove_if(bubbles.begin(), bubbles.end(),
            [](const Bubble& b) { return b.isPopped(); }), bubbles.end());

        window.clear(sf::Color(30, 30, 30)); 

        for (const auto& b : bubbles) {
            b.draw(window);
        }

        if (hasFont) {
            scoreText.setString("Score: " + std::to_string(score));
            window.draw(scoreText);
        }

        window.display();
    }

    return 0;
}