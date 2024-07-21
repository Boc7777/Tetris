#include "SFML/Graphics.hpp"
#include <iostream>
#include "Board.h"
#include "Block_I.h"
#include "TetrisBlock.h"

using namespace sf;
using namespace std;

const float cell_size = 40.f;

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

int main()
{
    RenderWindow window(VideoMode(display_width, display_height), "TETRIS");
    window.setFramerateLimit(60);

    Clock clock_X;
    Clock clock_Y;

    
    Event event;

    Board board(cell_size * 10, cell_size * 20);

    
    Block_I block_I(cell_size, Color::Red, &window, blocks_tab);
    blocks_tab.push_back(&block_I);

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
            blocks_tab.push_back( new Block_I(cell_size, Color::Red, &window, blocks_tab));   
        }

        //spadanie
        if (Move_Y_timer.asMilliseconds() >= 100) {

            for (TetrisBlock* block : blocks_tab) {
                    block->movement_X();
                    block->checkUnderCells();
                    block->moveDownCells();
               
            }
            clock_Y.restart();
        }

        //poruszanie prawo lewo 
        if (Move_X_timer.asMilliseconds() >= 50) {
            for (TetrisBlock* block : blocks_tab) {
                    block->movement_X();
            }
            clock_X.restart();
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

