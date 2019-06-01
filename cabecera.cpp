/**
 * @file cabecera.cpp
 * @brief Barra inferior que muestra el estado del jugador
 * @author Juan Carlos López Morales
 * @date 30/5/2019
 * @version 1.9
 */


#include "cabecera.h"
#include <string>


using namespace std;

static sf::Color cell_bg(203, 239, 241);

Cabecera::Cabecera(int sizex, int sizey, int vida, int fase, int huecos, int position) {

        cell = new sf::RectangleShape(sf::Vector2f(sizex, sizey));
        cell->move(sf::Vector2f(0, position));
        cell->setFillColor(sf::Color(66,66,66));
        font.loadFromFile("sansation.ttf");
        if (vida>0) {
                valorcabecera="vidas: "+to_string(vida)+"   fase: " + to_string(fase)+"   huecos: "+to_string(huecos);

        }

        this->text = new sf::Text(valorcabecera, font);
        this->text->setCharacterSize(25);
        sf::Vector2f pos_text = cell->getPosition();

        pos_text.x += cell->getSize().x/2.0 - this->text->getGlobalBounds().width/2;
        pos_text.y += cell->getSize().y/2.0 - this->text->getLocalBounds().height;
        this->text->setPosition(pos_text);
        this->text->setFillColor(sf::Color::White);
}


void Cabecera::draw(sf::RenderWindow &windows) {
        windows.draw(*cell);
        windows.draw(*text);
}

void Cabecera::updateText(string text) {
        this->text->setString(text);
}

Cabecera::~Cabecera(void) {
        if (text != nullptr) {
                delete text;
                text = nullptr;
        }
        if (cell != nullptr) {
                delete cell;
                cell = nullptr;
        }
}
