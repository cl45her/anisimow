#include <SFML/Graphics.hpp>
#include <optional>
#include <vector>

const int TILE_SIZE = 25;
const int MAP_HEIGHT = 21;
const int MAP_WIDTH = 19;

// Карта (1 - стена, 0 - проход)
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
    sf::RenderWindow window(sf::VideoMode({MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE}), "Tomb of the Mask: Proto");

    
    sf::RectangleShape player(sf::Vector2f({18.f, 18.f}));
    player.setFillColor(sf::Color::Yellow);
    player.setOrigin({9.f, 9.f});
    player.setPosition({TILE_SIZE * 1.5f, TILE_SIZE * 1.5f});

    sf::RectangleShape wallBlock(sf::Vector2f({(float)TILE_SIZE - 2, (float)TILE_SIZE - 2}));
    wallBlock.setFillColor(sf::Color(33, 33, 255));

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                sf::Vector2f currentPos = player.getPosition();
                sf::Vector2f direction(0.f, 0.f);

                if (keyPressed->code == sf::Keyboard::Key::Left)  direction.x = -(float)TILE_SIZE;
                if (keyPressed->code == sf::Keyboard::Key::Right) direction.x = (float)TILE_SIZE;
                if (keyPressed->code == sf::Keyboard::Key::Up)    direction.y = -(float)TILE_SIZE;
                if (keyPressed->code == sf::Keyboard::Key::Down)  direction.y = (float)TILE_SIZE;

                
                if (direction.x != 0 || direction.y != 0) {
                    sf::Vector2f nextPos = currentPos + direction;
                    while (canMove(nextPos)) {
                        currentPos = nextPos;
                        nextPos += direction;
                    }
                    player.setPosition(currentPos);
                }
            }
        }

        window.clear(sf::Color::Black);
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < MAP_WIDTH; j++) {
                if (maze[i][j] == 1) {
                    wallBlock.setPosition({(float)j * TILE_SIZE + 1, (float)i * TILE_SIZE + 1});
                    window.draw(wallBlock);
                }
            }
        }
        window.draw(player);
        window.display();
    }
    return 0;
}