/**
 * @file main.cpp
 * @brief Archivo main de SUDOKU
 * @author Juan Carlos López Morales
 * @date 30/5/2019
 * @version 1.9
 */

#include "board.h"
#include "cabecera.h"
#include <SFML/Graphics.hpp>

using namespace sf;

int main(void) {


        sf::RenderWindow window(sf::VideoMode(675,700), "tablero sudoku");
        sf::Music music;
        music.openFromFile("m1.wav");
        music.setVolume(10.f);
        music.play();
        Board board(9,9,75);
        bool quit = true;
        int fase=1;
        int cancion=0;

        while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                        if (event.type == sf::Event::Closed) {
                                window.close();
                        }

                        if (event.type == sf::Event::KeyPressed) {
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                                        window.close();
                                        quit = false;
                                }
                        } else if (event.type == sf::Event::MouseButtonReleased) {
                                board.action(event.mouseButton.x, event.mouseButton.y);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {

                                board.actionByKeyboard(0, -1);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

                                board.actionByKeyboard(0, 1);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {

                                board.actionByKeyboard(-1, 0);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {

                                board.actionByKeyboard(1, 0);

                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {

                                board.update_board(1);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {

                                board.update_board(2);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {

                                board.update_board(3);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {

                                board.update_board(4);

                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {

                                board.update_board(5);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) {

                                board.update_board(6);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) {

                                board.update_board(7);
                        }  else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num8)) {

                                board.update_board(8);
                        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num9)) {

                                board.update_board(9);
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {

                                fase++;
                                if(fase>3) {
                                        fase=1;
                                }

                                board.carga_nivel(fase);
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {

                                fase--;
                                if(fase<0) {
                                        fase=3;
                                }

                                board.carga_nivel(fase);
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {


                                board.carga_nivel(fase);
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {

                                board.get_max_lifes();
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {

                                music.stop();
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {

                                music.play();
                        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {

                                if (cancion==0) {

                                        music.openFromFile("m2.wav");
                                        cancion=1;
                                }else{
                                        music.openFromFile("m1.wav");
                                        cancion=0;
                                }
                                music.play();
                        }


                }

                if(quit) {
                        window.clear();
                        board.draw(window);
                        window.display();
                }


        }

        return 0;
}
