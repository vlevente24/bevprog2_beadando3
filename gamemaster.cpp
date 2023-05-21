#include "gamemaster.hpp"
#include <iostream>

using namespace std;

GameMaster::GameMaster(int * st, function<void(int, int)> f) : status(st), _f(f) {}

void GameMaster::fieldClick(int x, int y) {
    if (*status == 3)
    _f(x, y);
}