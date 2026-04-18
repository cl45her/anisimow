#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

const int TILE_SIZE = 25;
const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 19;

int maze[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,0,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,1,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,1,1},
    {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
    {1,1,1,1,0,1,0,1,1,0,1,1,0,1,0,1,1,1,1},
    {0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0},
    {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
    {0,0,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,0},
    {1,1,1,1,0,1,0,1,1,1,1,1,0,1,0,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1},
    {1,0,1,1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,1},
    {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
    {1,1,0,1,0,1,0,1,1,1,1,1,0,1,0,1,0,1,1},
    {1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,1},
    {1,0,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

bool canMove(sf::Vector2f pos) {
    int x = static_cast<int>(pos.x / TILE_SIZE);
    int y = static_cast<int>(pos.y / TILE_SIZE);
    if (x >= 0 && x < MAP_WIDTH && y >= 0 && y < MAP_HEIGHT) {
        return maze[y][x] == 0;
    }
    return false;
}

int main() {
    sf::RenderWindow window(sf::VideoMode({MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE}), "Pacman Classic");

    sf::CircleShape pacman(10.f);
    pacman.setFillColor(sf::Color::Yellow);
    pacman.setOrigin({10.f, 10.f});
    pacman.setPosition({TILE_SIZE * 1.5f, TILE_SIZE * 1.5f});

    sf::RectangleShape wallBlock(sf::Vector2f({(float)TILE_SIZE - 1, (float)TILE_SIZE - 1}));
    wallBlock.setFillColor(sf::Color(25, 25, 166));

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                sf::Vector2f currentPos = pacman.getPosition();
                sf::Vector2f nextPos = currentPos;
                float step = (float)TILE_SIZE; 

                if (keyPressed->code == sf::Keyboard::Key::Left)  nextPos.x -= step;
                if (keyPressed->code == sf::Keyboard::Key::Right) nextPos.x += step;
                if (keyPressed->code == sf::Keyboard::Key::Up)    nextPos.y -= step;
                if (keyPressed->code == sf::Keyboard::Key::Down)  nextPos.y += step;

               
                if (canMove(nextPos)) {
                    pacman.setPosition(nextPos);
                }
            }
        }

        window.clear();
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                if (maze[i][j] == 1) {
                    wallBlock.setPosition({(float)j * TILE_SIZE, (float)i * TILE_SIZE});
                    window.draw(wallBlock);
                }
            }
        }
        window.draw(pacman);
        window.display();
    }
    return 0;
}
 