#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <vector>

int main() {
    
    sf::RenderWindow window(sf::VideoMode({600, 600}), "Pacman Project");

    
    sf::CircleShape pacman(15.f);
    pacman.setFillColor(sf::Color::Yellow);
    pacman.setPosition({65.f, 65.f}); 

    
    int maze[10][10] = {
        {1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,1,0,1,1,0,1},
        {1,0,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,0,0,1},
        {1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,1,0,0,0,0,1},
        {1,0,1,0,0,0,1,0,0,1},
        {1,1,1,1,1,1,1,1,1,1}
    };

    
    sf::RectangleShape wall(sf::Vector2f({60.f, 60.f}));
    wall.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                float step = 10.f; 
                if (keyPressed->code == sf::Keyboard::Key::Left)  pacman.move({-step, 0.f});
                if (keyPressed->code == sf::Keyboard::Key::Right) pacman.move({step, 0.f});
                if (keyPressed->code == sf::Keyboard::Key::Up)    pacman.move({0.f, -step});
                if (keyPressed->code == sf::Keyboard::Key::Down)  pacman.move({0.f, step});
            }
        }

        window.clear();

        
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (maze[i][j] == 1) {
                    wall.setPosition({(float)j * 60.f, (float)i * 60.f});
                    window.draw(wall);
                }
            }
        }

        
        window.draw(pacman);
        window.display();
    }

    return 0;
}