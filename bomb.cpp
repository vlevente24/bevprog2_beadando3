#include "bomb.hpp"

using namespace genv;
using namespace std;

Bomb::Bomb(Application *app) : Widget(app, 0, 0, 40, 40), _play(false), _i(0), _dx(0), _dy(0) {
    _bomb = new canvas(40, 40);
    *_bomb << move_to(0, 0) << color(0, 0, 0) << box(40, 40);
    for (int i = 0; i < 40; i++) {
        for (int j = 0; j < 40; j++) {
            if ((i - 20) * (i - 20) + (j - 20) * (j - 20) <= 256) {
                *_bomb << move_to(i,j) << color(1, 0, 0) << dot;
            }
        }
    }
    _bomb->transparent(true);
}

void Bomb::print(bool b) const {
    if (b and _play) {
        gout << stamp(*_bomb, _xpos, _ypos);
    }
}

bool Bomb::is_selected(int, int) {return _play;}

void Bomb::handle(genv::event ev) {
    if (_play) {
        if (_i == 0) {
            _xpos = _parent->getWidth() / 2 - _width / 2;
            _ypos = 0;
            gin.timer(20);
            ++_i;
        }
        if (ev.type == ev_timer and _i < 42) {
            int vx = _dx - (_parent->getWidth() / 2 - _width / 2);
            int x0 = (_parent->getWidth() / 2 - _width / 2);
            _xpos = x0 + vx / 40.0 * _i;
            _ypos = _dy / 40.0 * _i;
            ++_i;
        }
        if (_i >= 42) {
            gin.timer(0);
            _play = false;
            _i = 0;
        }
    }
}

void Bomb::reset() {}

void Bomb::PlayBombA(int x, int y) {
    _dx = x;
    _dy = y;
    _play = true;
}