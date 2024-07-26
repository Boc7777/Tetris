#include "SFML/Graphics.hpp"
#include <iostream>
#include "Board.h"
#include "Block_I.h"
#include "Block_O.h"
#include <cstdlib>

using namespace sf;
using namespace std;

const float cell_size = 40.f;
const int amount_of_blocks = 2;

unsigned display_width = cell_size*15.f; 
unsigned display_height = cell_size*20.f;

vector<TetrisBlock*> blocks_tab;

int score = 0;

vector<int> cells_in_rows;

bool game_on = true;

void Check_game_over() {
    for (TetrisBlock* block : blocks_tab) {
        for (auto& external_cell : block->getTabCells()) {
            if (!external_cell.get_underControl() && external_cell.getPosition().y < 0) {
                game_on = false;
            }
        }
    }
}

void Check_line(Board &board) {
    cells_in_rows.clear();

    for (int i = 0; i < 20;i++) {
        cells_in_rows.push_back(0);
    }
 
    for (TetrisBlock* block : blocks_tab) {
        for (auto& external_cell : block->getTabCells()) {
            if (external_cell.getPosition().y / cell_size >= 0) {
                cells_in_rows[external_cell.getPosition().y / cell_size] += 1;
            }
        }
    }

    int index = 0;
    for (auto& row : cells_in_rows) {
        if (row == 10) {
            float yToDelete = index * cell_size;
            score += 10;
            board.updateData(score);
            

            for (int i = 0;i < blocks_tab.size();i++) {
                int b = 0;
                vector<Cell> &mini_blocks_tab = blocks_tab[i]->getTabCells();
                for (auto& external_cell : mini_blocks_tab) {
                    if (external_cell.getPosition().y == yToDelete) {
                        external_cell.set_toDelete();

                    }
                    b += 1;

                    if (external_cell.getPosition().y < yToDelete) {
                        external_cell.setPosition(Vector2f(external_cell.getPosition().x, external_cell.getPosition().y + cell_size));
                    
                    }
                }
                mini_blocks_tab.erase(
                    remove_if(mini_blocks_tab.begin(), mini_blocks_tab.end(),
                        [](const Cell& obj) {return obj.get_toDelete();}),
                    mini_blocks_tab.end());
            }
        }
        index += 1;
    }
}

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

void Generate_random_block(RenderWindow* window, Board board) {

    int i = rand() % amount_of_blocks;
    if (i == 0) {
        blocks_tab.push_back(new Block_I(cell_size, Color::Blue, window, blocks_tab));
    }
    else if (i == 1) {
        blocks_tab.push_back(new Block_O(cell_size, Color::Green, window, blocks_tab));
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

    Board board(cell_size,&window);

    while (window.isOpen() ) {

        window.clear(Color::Black);
        //rysowanie boarda i drawRightPanel
        window.draw(board);
        board.DrawRightPanel();

        Time Move_X_timer = clock_X.getElapsedTime();
        Time Move_Y_timer = clock_Y.getElapsedTime();


        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
        }

        //jezeli jakis upadł generuje sie nastepny i sprawdzana jest linia i game over 
        if (Check_generate_moment() && game_on) {

            //sprawdzanie czy linia do usuniecia
            Check_line(board);

            //generowanie nastepnego bloku
            Generate_random_block(&window, board);
            
            //sprawdzanie czy gracz nie przegrał
            Check_game_over();
        }

        //spadanie
        //spadanie
        if (Move_Y_timer.asMilliseconds() >= 100 - board.getLevel()*10 && game_on) {

            for (TetrisBlock* block : blocks_tab) {
                    block->movement_X();
                    block->checkUnderCells();
                    block->moveDownCells();
               
            }
            clock_Y.restart();
  
        }

        //poruszanie prawo lewo 
        if (Move_X_timer.asMilliseconds() >= 500 && (Keyboard::isKeyPressed(Keyboard::Key::Left) || Keyboard::isKeyPressed(Keyboard::Key::Right) && game_on)){

            for (TetrisBlock* block : blocks_tab) {
                    block->movement_X();
            }
            clock_X.restart();
        }

        //rotejtowanie
        for (TetrisBlock* block : blocks_tab) {
            if (game_on) {
                block->rotate();
            }
        }

        //rysowanie 
        for (TetrisBlock* block : blocks_tab) {
            block->drawCells();
        }
     
        if (!game_on) {
            board.DrawGameOver();

            if (Keyboard::isKeyPressed(Keyboard::Enter)) {
                board.updateData(0);
                blocks_tab.clear();
                game_on = true;
            }
        }

        window.display();
        
    }
}



