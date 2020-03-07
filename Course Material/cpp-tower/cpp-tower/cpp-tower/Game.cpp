/**
 * C++ class for a game of the Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Game.h"
#include "Stack.h"
#include "uiuc/Cube.h"
#include "uiuc/HSLAPixel.h"
#include <assert.h>
#include <iostream>
using std::cout;
using std::endl;

// Solves the Tower of Hanoi puzzle.
// (Feel free to call "helper functions" to help you solve the puzzle.)
void Game::solve() {
  // Prints out the state of the game:
    cout << *this << endl;
    
    //hardcoded solution
    /*
    stacks_[1].push_back(stacks_[0].removeTop());
    stacks_[2].push_back(stacks_[0].removeTop());
    stacks_[2].push_back(stacks_[1].removeTop());
    stacks_[1].push_back(stacks_[0].removeTop());
    stacks_[0].push_back(stacks_[2].removeTop());
    stacks_[1].push_back(stacks_[2].removeTop());
    stacks_[1].push_back(stacks_[0].removeTop());
    stacks_[2].push_back(stacks_[0].removeTop());
    stacks_[2].push_back(stacks_[1].removeTop());
    stacks_[0].push_back(stacks_[1].removeTop());
    stacks_[0].push_back(stacks_[2].removeTop());
    stacks_[2].push_back(stacks_[1].removeTop());
    stacks_[1].push_back(stacks_[0].removeTop());
    stacks_[2].push_back(stacks_[0].removeTop());
    move(1, 2);*/
    
    int n = stacks_[0].size(); //number of disks
    int source = 0;
    int target = 2;
    int aux = 1;
    move_n(n, source, target, aux);
    
}

void Game::move_n(int n, int source, int target, int auxiliary) {
    if (n == 1) { //if only moving one disk, move it and return
        move(source, target);
        return;
    }
    // If more than one disk, move n-1 disks to the auxiliary rod
    move_n(n - 1, source, auxiliary, target);
    // then move the last disk to the target
    move(source, target);
    // then move everything from the auxiliary to the target using source as auxiliary
    move_n(n - 1, auxiliary, target, source);
    return;
}

void Game::move(int src, int dst) {
    assert(src <= (stacks_.size() - 1));
    assert(dst <= (stacks_.size() - 1));
    stacks_[dst].push_back(stacks_[src].removeTop());
}

// Default constructor to create the initial state:
Game::Game() {
  // Create the three empty stacks:
  for (int i = 0; i < 3; i++) {
    Stack stackOfCubes;
    stacks_.push_back( stackOfCubes );
  }

  // Create the four cubes, placing each on the [0]th stack:
  Cube blue(4, uiuc::HSLAPixel::BLUE);
  stacks_[0].push_back(blue);

  Cube orange(3, uiuc::HSLAPixel::ORANGE);
  stacks_[0].push_back(orange);

  Cube purple(2, uiuc::HSLAPixel::PURPLE);
  stacks_[0].push_back(purple);

  Cube yellow(1, uiuc::HSLAPixel::YELLOW);
  stacks_[0].push_back(yellow);
}

std::ostream& operator<<(std::ostream & os, const Game & game) {
  for (unsigned i = 0; i < game.stacks_.size(); i++) {
    os << "Stack[" << i << "]: " << game.stacks_[i];
  }
  return os;
}
