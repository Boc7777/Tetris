#include "SFML/Graphics.hpp"
#include <iostream>
#include "Board.h"
#include "Block_I.h"
#include "Block_O.h"
#include "TetrisBlock.h"
#include <cstdlib>

using namespace sf;
using namespace std;

const float cell_size = 40.f;
const int amount_of_blocks = 2;

unsigned display_width = cell_size*15.f; 
unsigned display_height = cell_size*20.f;

vector<TetrisBlock*> blocks_tab;

bool Check_generate_moment() {
    for (TetrisBlock* block : blocks_tab) {
        vector<Cell> cells_of_block = block->getTabCells();
        for (auto& cell : cells_of_block) {
            if (cell.get_underControl()) {
                return false;
            }
        }
    }

    return true;
}

void Generate_random_block(RenderWindow* window) {
    int i = rand() % amount_of_blocks;
    if (i == 0) {
        blocks_tab.push_back(new Block_I(cell_size, Color::Yellow, window, blocks_tab));
    }
    else if (i == 1) {
        blocks_tab.push_back(new Block_O(cell_size, Color::Cyan, window, blocks_tab));
    }
}


int main()
{
    RenderWindow window(VideoMode(display_width, display_height), "TETRIS");
    window.setFramerateLimit(60);

    Clock clock_X;
    Clock clock_Y;

    srand(time(0));
    Event event;

    Board board(cell_size * 10, cell_size * 20);


    while (window.isOpen()) {

        window.clear(Color::Black);
        window.draw(board);

        Time Move_X_timer = clock_X.getElapsedTime();
        Time Move_Y_timer = clock_Y.getElapsedTime();


        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //jezeli jakis upadł generuje sie nastepny 
        if (Check_generate_moment()) {
            Generate_random_block(&window);
        }

        //spadanie
        if (Move_Y_timer.asMilliseconds() >= 200) {

            for (TetrisBlock* block : blocks_tab) {
                    block->movement_X();
                    block->checkUnderCells();
                    block->moveDownCells();
               
            }
            clock_Y.restart();
        }

        //poruszanie prawo lewo 
        if (Move_X_timer.asMilliseconds() >= 300 && (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::Right) )){

            for (TetrisBlock* block : blocks_tab) {
                    block->movement_X();
            }
            clock_X.restart();
            cout << Move_X_timer.asMilliseconds() << "\n";
        }

        //rotejtowanie
        for (TetrisBlock* block : blocks_tab) {
                block->rotate();
        }

        //rysowanie 
        for (TetrisBlock* block : blocks_tab) {
            block->drawCells();
        }
       
        window.display();
        
    }
}



