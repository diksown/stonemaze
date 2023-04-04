// g++ chessboard.cpp -o chessboard -lsfml-graphics -lsfml-window -lsfml-system

#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Chessboard");

    // Create the black and white squares of the chessboard
    sf::RectangleShape square(sf::Vector2f(50, 50));
    square.setFillColor(sf::Color::Black);
    sf::RectangleShape whiteSquare(square);
    whiteSquare.setFillColor(sf::Color::White);

    // Create the green square and initialize its position
    sf::RectangleShape greenSquare(sf::Vector2f(20, 20));
    greenSquare.setFillColor(sf::Color::Green);
    sf::Vector2f greenSquarePos(0, 0);
    greenSquare.setPosition(greenSquarePos);

    // Position the squares to form the chessboard
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            sf::RectangleShape* currentSquare;
            if ((x + y) % 2 == 0) {
                currentSquare = &whiteSquare;
            } else {
                currentSquare = &square;
            }
            currentSquare->setPosition(x * 50, y * 50);
            window.draw(*currentSquare);
        }
    }

    window.draw(greenSquare);
    window.display();

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    // Move the green square based on arrow key presses
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            greenSquarePos.y =
                                std::max(greenSquarePos.y - 50.0f, 0.0f);
                            greenSquare.setPosition(greenSquarePos);
                            break;
                        case sf::Keyboard::Down:
                            greenSquarePos.y =
                                std::min(greenSquarePos.y + 50.0f, 350.0f);
                            greenSquare.setPosition(greenSquarePos);
                            break;
                        case sf::Keyboard::Left:
                            greenSquarePos.x =
                                std::max(greenSquarePos.x - 50.0f, 0.0f);
                            greenSquare.setPosition(greenSquarePos);
                            break;
                        case sf::Keyboard::Right:
                            greenSquarePos.x =
                                std::min(greenSquarePos.x + 50.0f, 350.0f);
                            greenSquare.setPosition(greenSquarePos);
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        window.clear();
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                sf::RectangleShape* currentSquare;
                if ((x + y) % 2 == 0) {
                    currentSquare = &whiteSquare;
                } else {
                    currentSquare = &square;
                }
                currentSquare->setPosition(x * 50, y * 50);
                window.draw(*currentSquare);
            }
        }
        window.draw(greenSquare);
        window.display();
    }

    return 0;
}