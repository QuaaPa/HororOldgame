#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

#include "map.hpp" //подключили код с картой

int main()
{

    sf::RenderWindow window(sf::VideoMode(900, 600), "SFML works!", sf::Style::None);

//#### set max fps in window #####
    window.setFramerateLimit(120);

//##### turn off visibile cursor #######
    window.setMouseCursorVisible(false);

//########### CREATE CIRCL #########
    sf::CircleShape shape(10.f);
    shape.setFillColor(sf::Color::Blue);
    shape.setOrigin(10, 10);
//##################################

    sf::Vector2i position = sf::Mouse::getPosition(window);

//################### Load Font form file ####################
    sf::Font arial_font;
    if (!arial_font.loadFromFile("resources/BlackArial.ttf"))
    {
        std::cout << "ERROR LOAD FONT" << std::endl;
    }
//############################################################

//############ Position TEXT################
    sf::Text textPos;
    textPos.setFont(arial_font);
    textPos.setPosition(10, 570);
    textPos.setScale(0.5,0.5);
//###########################################

//################# FPS TEXT ################
    sf::Text textFPS;
    textFPS.setFont(arial_font);
    textFPS.setPosition(10, 550);
    textFPS.setScale(0.5,0.5);
    textFPS.setString("FPS: 0");
//###########################################

//################# Map ################
sf::Image map_image;//объект изображения для карты
map_image.loadFromFile("resources/MapIm.png");//загружаем файл для карты
//
sf::Texture map;//текстура карты
map.loadFromImage(map_image);//заряжаем текстуру картинкой
//
sf::Sprite s_map;//создаём спрайт для карты
s_map.setTexture(map);//заливаем текстуру спрайтом
//###########################################



//##### SET DEFAULT OPTION #################
sf::Mouse::setPosition(sf::Vector2i(450, 300), window);
textPos.setString("x = [450] y = [300]");
//########################################


    sf::Clock clock;
    int c = 0;
    int prev = 0;

    std::ostringstream ssPos;
    std::ostringstream ssFPS;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();

            if (event.type == sf::Event::MouseMoved)
            {
                // обработка движения мыши
                ssPos.str(""); // очистить содержимое ss
                ssPos << "x = [" << position.x << "] y = [" << position.y<<"]";
                textPos.setString(ssPos.str());
            }
        }

        position = sf::Mouse::getPosition(window);
        shape.setPosition(position.x, position.y);

        window.clear();


        //#########################  Рисуем карту  ############################
		for (int i = 0; i < HEIGHT_MAP; i++)
		{
            for (int j = 0; j < WIDTH_MAP; j++)
            {
                if (TileMap[i][j] == ' ')  s_map.setTextureRect(sf::IntRect(0, 0, 32, 32)); //если встретили символ пробел, то рисуем 1й квадратик
			    if (TileMap[i][j] == 's')  s_map.setTextureRect(sf::IntRect(64, 0, 32, 32));//если встретили символ s, то рисуем 2й квадратик
			    if ((TileMap[i][j] == '0')) s_map.setTextureRect(sf::IntRect(32, 0, 32, 32));//если встретили символ 0, то рисуем 3й квадратик


			    s_map.setPosition(j * 32, i * 32);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

			    window.draw(s_map);//рисуем квадратики на экран
            }
		}


        window.draw(shape);
        window.draw(textPos);
        window.draw(textFPS);
        window.display();

        int time = clock.getElapsedTime().asSeconds();

        if(time != prev)
        {
            ssFPS.str("");
            ssFPS << "FPS:"<< c;
            textFPS.setString(ssFPS.str());
            c = 0;
            prev = time;
        }

        c++;
    }

    return 0;
}