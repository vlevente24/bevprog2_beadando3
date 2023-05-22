#ifndef TORPEDO_GAMEMASTER_HPP
#define TORPEDO_GAMEMASTER_HPP

// coordinating the whole game, without drawing

#include <functional>
#include <vector>
#include "field.hpp"
#include "bomb.hpp"
#include "textbox.hpp"

class GameMaster {
    bool isPlayer1;
    int * status;
    Bomb * _bomb;
    TextBox * _tb1;
    TextBox * _tb2;
    std::vector<std::vector<Field*>> _plr1f;
    std::vector<std::vector<Field*>> _plr2f;
    std::function<void()> _f;
    std::function<void(bool)> _win;
public:
    GameMaster(int * st, Bomb*, TextBox*, TextBox*, std::vector<std::vector<Field*>> p1f, std::vector<std::vector<Field*>>p2f,
               std::function<void()> f, std::function<void(bool)> win);
    void fieldClick(Field*);
    void fieldClick2();
};


#endif //TORPEDO_GAMEMASTER_HPP
