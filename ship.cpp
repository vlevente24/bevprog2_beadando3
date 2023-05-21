#include "ship.hpp"

using namespace genv;

Ship::Ship(Application *app, int x, int y, int shipsize, std::function<bool(bool,int,int,int)> cp, std::function<void(Ship*,int,int)> ps):
           Widget(app, x, y,shipsize * 40 - 20, 20), _ssize(shipsize), _mx(-1), _my(-1), _horizontal(true), _visible(false),
           _static(true), _follow(false), _x0(x), _y0(y), canPlace(cp), placeShip(ps) {}

void Ship::print(bool) const {
    if (_visible) {
        gout << move_to(_xpos + 10, _ypos + 10) << color(0, 0,0);
        if (_horizontal) {
            gout << box(_ssize * 40 - 20, 20);
        } else {
            gout << box(20, _ssize * 40 - 20);
        }
    }
}

void Ship::handle(genv::event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (!_static and _visible) {
                _dx = ev.pos_x - _xpos;
                _dy = ev.pos_y - _ypos;
                _follow = true;
            }
        }
        if (ev.button == 0) {
            if (_follow and !_static and _visible) {
                if (canPlace(_horizontal, ev.pos_x - _dx, ev.pos_y - _dy, _ssize)) {
                    if (_x0 < _parent->getWidth() / 2) {
                        _xpos = _parent->getWidth() - 430 + ((ev.pos_x - _dx + 430 - _parent->getWidth()) / 40) * 40 ;
                    } else {
                        _xpos = 30 + ((ev.pos_x - _dx - 30) / 40) * 40;
                    }
                    _ypos = 110 + ((ev.pos_y - _dy - 110) / 40) * 40;
                }
                else if (_x0 < _parent->getWidth() / 2 and !(ev.pos_x >= _parent->getWidth() - 430 and
                        ev.pos_x < _parent->getWidth() - 30 and ev.pos_y >= 110 and ev.pos_y < 510)) {
                    _xpos = ev.pos_x - _dx;
                    _ypos = ev.pos_y - _dy;
                }
                else if (_x0 >= _parent->getWidth() / 2 and !(ev.pos_x >= 30 and ev.pos_x < 430 and ev.pos_y >= 110 and
                        ev.pos_y < 510)) {
                    _xpos = ev.pos_x - _dx;
                    _ypos = ev.pos_y - _dy;
                }
            }
        }
        if (ev.button == -btn_left) {
            if (_follow and !_static and _visible) {
                _dx = _dy = 0;
                if (canPlace(_horizontal, _xpos, _ypos, _ssize)) {
                    placeShip(this, ev.pos_x - _dx, ev.pos_y - _dy);
                }
                else {
                    _xpos = _x0;
                    _ypos = _y0;
                    _horizontal = true;
                }
                _follow = false;
            }
        }
    }
}

void Ship::reset() {}

void Ship::setVisibility(bool b) {
    _visible = b;
}

void Ship::setStatic(bool b) {
    _static = b;
}

bool Ship::is_selected(int x, int y) {
    return !_static and _visible and (x >= _xpos + 10) and (x < _xpos + _width + 10) and (y >= _ypos + 10) and
    (y < _ypos + _height + 10);
}

bool Ship::getHorizontal() {
    return _horizontal;
}

int Ship::getShipSize() {
    return _ssize;
}
