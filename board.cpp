/**
 * @file board.cpp
 * @brief Tablero matriz del SUDOKU con funcionalidades
 * @author Juan Carlos López Morales
 * @date 30/5/2019
 * @version 1.9
 */

#include "board.h"
#include "cabecera.h"
#include <iostream>
#include <string>
#include <fstream>
#include <SFML/Audio.hpp>
#include <unistd.h>


using namespace std;

static sf::Color cell_bg(203, 239, 241);

Board::Board(int nrows, int ncols, int size) {
        const int tam = nrows * ncols;
        this->nrows = nrows;
        this->ncols = ncols;
        this->size = size;
        this->current = nullptr;
        cells=nullptr;
        matriz=nullptr;
        text=nullptr;
        cells = new sf::RectangleShape *[tam];
        font.loadFromFile("sansation.ttf");
        text= new sf::Text *[tam];
        cabecera = new Cabecera(700,30,vidas, faseactual, valoresnulos, 675);

        carga_nivel(nivel);

        contar_casillas_0();

        draw_and_text_board(nrows, ncols, size);



        color(ncols, nrows);
}

void Board::color(int nrows, int ncols){

        int total=0;
        for(int i=0; i<nrows; i++) {
                for (int j=0; j<ncols; j++) {
                        if(i<3 && j<3) {
                                cells[total]->setFillColor(sf::Color(190,20,20));
                        }else{
                                if(i>5 && j<3) {
                                        cells[total]->setFillColor(sf::Color(190,20,20));
                                }else{
                                        if(i<3 && j>5) {
                                                cells[total]->setFillColor(sf::Color(190,20,20));
                                        }else{
                                                if(i>5 && j>5) {
                                                        cells[total]->setFillColor(sf::Color(190,20,20));
                                                }else{
                                                        if((i<6 && j<6)&&(i>2&&j>2)) {
                                                                cells[total]->setFillColor(sf::Color(190,20,20));
                                                        }else{
                                                                cells[total]->setFillColor(sf::Color(sf::Color(180,80,80)));

                                                        }
                                                }
                                        }
                                }
                        }


                        total++;

                }
        }
}

void Board::comprueba_casilla(){

        int fila, columna;


        numero_mal_colocado=false;

        fila=x;
        columna=y;

        for(int i=0; i<nrows; i++) {

                if(fila!=i) {

                        if(matriz[i][columna]==matriz[fila][columna]) {

                                numero_mal_colocado=true;

                        }
                }
        }

        for(int j=0; j<ncols; j++) {

                if(columna!=j) {

                        if(matriz[fila][j]==matriz[fila][columna]) {

                                numero_mal_colocado=true;

                        }
                }
        }

        if(fila%3==1) {
                fila-=1;
        }
        if(fila%3==2) {
                fila-=2;
        }
        if(columna%3==1) {
                columna-=1;
        }
        if(columna%3==2) {
                columna-=2;
        }

        for(int i=fila; i<fila+3; i++) {
                for(int j=columna; j<columna+3; j++) {

                        if (x!=i && y!=j) {

                                if(matriz[i][j]==matriz[x][y]) {

                                        numero_mal_colocado=true;

                                }

                        }
                }
        }

        if(numero_mal_colocado) {
                vidas--;
                buffer.loadFromFile("sonidoerror.wav");
                matriz[x][y]=11;
                sound.setBuffer(buffer);
                sound.play();

        }


}

void Board::carga_nivel(int fase){


        string name="fases/fase" + to_string(fase) + ".txt";
        ifstream file;
        vidas=3;
        faseactual=fase;
        file.open(name);

        if(file) {

                int filas, columnas;
                int total=nrows*ncols;

                file >> filas;
                file >> columnas;

                matriz= new int *[filas];

                for(int i=0; i<columnas; i++) {

                        matriz[i]=new int [columnas];
                }

                for(int i=0; i<filas; i++) {
                        cout << endl;
                        for(int j=0; j<columnas; j++) {
                                file>>matriz[i][j];
                                original[i][j]=matriz[i][j];
                                if(file.fail()) {

                                        throw string( "No se pudo leer el archivo");

                                }
                        }
                }

                if (puedoborrar) {

                        for(int i=0; i<total; i++) {

                                delete cells[i];
                                delete text[i];
                        }


                        contar_casillas_0();

                }


                draw_and_text_board(nrows, ncols, size);

                puedoborrar=true;

                file.close();
        }else{

                cerr << "Error en abrir el archivo: " << name;
        }
}


void Board::draw(sf::RenderWindow &windows) {
        int total = nrows * ncols;

        cabecera->draw(windows);


        for (int i = 0; i < total; i++) {
                windows.draw(*cells[i]);
                windows.draw(*text[i]);
        }


}

void Board::action(int px, int py) {
        int ix, iy;

        ix = px/this->size;
        iy = py/this->size;

        if (current != nullptr) {

                color(9,9);
        }

        current = cells[ix * nrows+ iy];

        current->setFillColor(sf::Color::Blue);

        x=ix;
        y=iy;


}

void Board::actionByKeyboard(int px, int py) {
        int ix, iy;

        ix=x;
        iy=y;

        if (current != nullptr) {

                color(9,9);
        }

        ix+=px;
        iy+=py;

        if(ix<0) {
                ix=8;
        }

        if(iy<0) {
                iy=8;
        }
        if(ix>8) {
                ix=0;
        }

        if(iy>8) {
                iy=0;
        }

        current = cells[ix * nrows+ iy];
        current->setFillColor(sf::Color::Blue);


        x=ix;
        y=iy;


}

void Board::update_board(int num){

        int total=nrows*ncols;


        if (matriz[x][y]==0) {
                valoresnulos--;
        }

        if(original[x][y]==0) {
                matriz[x][y]=num;
        }



        for(int i=0; i<total; i++) {

                delete cells[i];
                delete text[i];

        }


        comprueba_casilla();



        draw_and_text_board(nrows, ncols, size);

        if((vidas>0 && valoresnulos==0)&&!numero_mal_colocado) {
                faseactual++;
                ganar=true;
                if(faseactual>3) {
                        faseactual=1;

                }


                carga_nivel(faseactual);


        }else{
                ganar=false;

                for (int i = 0; i < total; i++) {
                        delete cells[i];
                        delete text[i];
                }



                draw_and_text_board(nrows, ncols, size);

        }


}

void Board::contar_casillas_0(){

        valoresnulos=0;

        for (int i=0; i<nrows; i++) {
                for(int j=0; j<ncols; j++) {

                        if(matriz[i][j]==0) {
                                valoresnulos++;
                        }
                }
        }
}

void Board::draw_and_text_board(int nrows,int ncols,int size){

        int total=0;

        if(vidas>0) {
                cabecera->updateText( "vidas: "+to_string(vidas)+"   fase: " + to_string(faseactual)+"   huecos: "+to_string(valoresnulos) );
        }else{
                buffer.loadFromFile("perder.wav");
                cabecera->updateText( "Has perdido!! Pulsa 'R' ");
                sound.setBuffer(buffer);
                sound.play();
        }

        if(ganar) {
                cabecera->updateText( "Has ganado. Enhorabuena!!");
                buffer.loadFromFile("ganar.wav");
                sound.setBuffer(buffer);
                sound.play();
        }


        for (int x = 0; x < ncols; x++) {

                for (int y = 0; y < nrows; y++) {

                        cells[total] = new sf::RectangleShape(sf::Vector2f(size - thickness, size - thickness));
                        cells[total]->setPosition(x*size, y*size);
                        cells[total]->setOutlineColor(sf::Color::Black);
                        cells[total]->setOutlineThickness(2.0);
                        valor_casilla=to_string(matriz[x][y]);

                        if (matriz[x][y]==0) {
                                valor_casilla='\0';
                        }
                        if (matriz[x][y]==11) {
                                valor_casilla=":'(";
                        }

                        text[total]= new sf::Text(valor_casilla, font);
                        text[total]->setCharacterSize(45);
                        sf::Vector2f pos_text = cells[total]->getPosition();

                        pos_text.x += cells[total]->getSize().x/2.0 - text[total]->getGlobalBounds().width/2;
                        pos_text.y += cells[total]->getSize().y/2.0 - text[total]->getLocalBounds().height;
                        text[total]->setPosition(pos_text);

                        if (original[x][y]==0) {
                                text[total]->setFillColor(sf::Color::White);

                        }else{

                                text[total]->setFillColor(sf::Color::Black);
                        }

                        total++;

                }

        }

        color(9,9);

}

void Board::get_max_lifes(){
        vidas=99;
        buffer.loadFromFile("vida.wav");
        sound.setBuffer(buffer);
        sound.play();
}

Board::~Board(void) {

        int total = nrows * ncols;

        if (cells == nullptr) {
                return;
        }


        for (int i = 0; i < total; i++) {
                delete cells[i];
                delete text[i];
        }

        for(int j=0; j<ncols; j++) {

                delete matriz[j];
        }

        delete[] cells;
        delete[] text;
        delete[] matriz;

}
