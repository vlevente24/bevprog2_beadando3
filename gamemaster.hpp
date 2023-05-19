#ifndef TORPEDO_GAMEMASTER_HPP
#define TORPEDO_GAMEMASTER_HPP

// coordinating the whole game, without drawing

#include <functional>
#include "field.hpp"
#include "bomb.hpp"

class GameMaster {
    int * status;
    std::function<void(int, int)> _f;
public:
    GameMaster(int * st, std::function<void(int, int)> f);
    void fieldClick(int x, int y);
};


#endif //TORPEDO_GAMEMASTER_HPP
