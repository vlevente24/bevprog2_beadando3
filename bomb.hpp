#ifndef TORPEDO_BOMB_HPP
#define TORPEDO_BOMB_HPP

#include "widgets.hpp"
#include <functional>

class Bomb : public Widget {
    genv::canvas * _bomb;
    bool _play;
    size_t _i;
    int _dx, _dy;
public:
    Bomb(Application *app);
    bool is_selected(int, int) override;
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void PlayBombA(int x, int y);
};


#endif //TORPEDO_BOMB_HPP
