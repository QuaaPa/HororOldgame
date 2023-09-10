#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "map.hpp" // Подключили код с картой

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML works!", sf::Style::None);
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::RectangleShape shape;
    shape.setSize(sf::Vector2f(15.0f, 15.0f));
    shape.setFillColor(sf::Color::White);

    sf::Vector2f position(450, 300); // Измените начальную позицию игрока
    shape.setPosition(position);

    sf::Vector2i mousePosition; // Позиция мыши

    sf::Font arial_font;
    if (!arial_font.loadFromFile("resources/BlackArial.ttf"))
    {
        std::cout << "ERROR LOAD FONT" << std::endl;
    }

    sf::Text textPos;
    textPos.setFont(arial_font);
    textPos.setPosition(10, 570);
    textPos.setScale(0.5, 0.5);

    sf::Text textCol;
    textCol.setFont(arial_font);
    textCol.setPosition(10, 530);
    textCol.setScale(0.5, 0.5);

    sf::Text textGV;
    textGV.setFont(arial_font);
    textGV.setPosition(100, 230);
    textGV.setScale(3.5, 3.5);
    textGV.setString("GAME OVER");

    sf::Text textFPS;
    textFPS.setFont(arial_font);
    textFPS.setPosition(10, 550);
    textFPS.setScale(0.5, 0.5);
    textFPS.setString("FPS: 0");

    sf::Image map_image;
    map_image.loadFromFile("resources/MapIm.png");

    sf::Texture map;
    map.loadFromImage(map_image);

    sf::Sprite s_map;
    s_map.setTexture(map);

    sf::FloatRect playerBounds; // Границы игрока
    sf::FloatRect tileBounds;   // Границы тайла

    sf::Clock clock;
    int c = 0;
    int prev = 0;

    std::ostringstream ssPos;
    std::ostringstream ssFPS;

    //##### SET DEFAULT OPTION #################
    sf::Mouse::setPosition(sf::Vector2i(830, 540), window);
    textPos.setString("x = [450] y = [300]");
    //########################################

    sf::Clock gameOverClock; // Таймер для отображения "Game Over"
    bool showGameOver = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                mousePosition = sf::Mouse::getPosition(window);
                ssPos.str("");
                ssPos << "x = [" << mousePosition.x << "] y = [" << mousePosition.y << "]";
                textPos.setString(ssPos.str());
            }
        }

        if (gameOverClock.getElapsedTime().asSeconds() >= 2.0f)
        {
            showGameOver = false;
        }


        sf::Vector2f prevPosition = shape.getPosition();
        shape.setPosition(mousePosition.x, mousePosition.y);;

        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++)
        {
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (LevelMap[i][j] == ' ')
                {
                    s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));
                }
                else if (LevelMap[i][j] == 's')
                {
                    s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));
                }
                else if (LevelMap[i][j] == '0')
                {
                    s_map.setTextureRect(sf::IntRect(0, 0, 32, 32));
                }
                else if (LevelMap[i][j] == '@')
                {
                    s_map.setTextureRect(sf::IntRect(96, 0, 32, 32));
                }

                s_map.setPosition(j * 32, i * 32);
                window.draw(s_map);

                tileBounds = s_map.getGlobalBounds();
                playerBounds = shape.getGlobalBounds();

                if (LevelMap[i][j] == '0' && playerBounds.intersects(tileBounds))
                {
                    // Если есть коллизия с черным квадратом, перемещаемся на начальную позицию
                    shape.setPosition(sf::Vector2f(800, 520)); // Установите начальную позицию здесь
                    sf::Mouse::setPosition(sf::Vector2i(800, 520), window);
                    textCol.setString("Collision!!");

                    showGameOver = true;
                    gameOverClock.restart();
                }
            }
        }
        window.draw(shape);
        window.draw(textPos);
        window.draw(textFPS);
        window.draw(textCol);

        if (showGameOver)
        {
            window.draw(textGV); // Отображаем "Game Over"
        }

        window.display();

        int time = clock.getElapsedTime().asSeconds();
        if (time != prev)
        {
            ssFPS.str("");
            ssFPS << "FPS:" << c;
            textFPS.setString(ssFPS.str());
            c = 0;
            prev = time;
        }

        c++;
    }

    return 0;
}