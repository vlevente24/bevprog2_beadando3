#include "ship.hpp"

using namespace genv;

Ship::Ship(Application *app, int x, int y, int ships, std::function<bool(bool,int,int,int,int)> cp,
           std::function<void(Ship*,bool)> ps) : Widget(app, x, y,ships * 40 - 20, 20), _ssize(ships), _horizontal(true),
           _visible(false), _static(true), _follow(false), _x0(x), _y0(y), canPlace(cp), placeShip(ps), _mx(-1), _my(-1) {}

void Ship::print(bool) const {
    if (_visible) {
        gout << move_to(_xpos, _ypos) << color(0, 0,0)<< box(_width, _height);
    }
}

void Ship::handle(genv::event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (!_static and _visible) {
                placeShip(this, true);
                _dx = ev.pos_x - _xpos;
                _dy = ev.pos_y - _ypos;
                _follow = true;
            }
        }
        if (ev.button == 0) {
            if (_follow and !_static and _visible) {
                if (canPlace(_horizontal, ev.pos_x, ev.pos_y, _ssize, calculateD())) {
                    if (_x0 < _parent->getWidth() / 2) {
                        if (_horizontal) {
                            _xpos = _parent->getWidth() - 420 + ((ev.pos_x + 430 - _parent->getWidth()) / 40 - calculateD()) * 40;
                            _ypos = 120 + ((ev.pos_y - 110) / 40) * 40;
                        } else {
                            _xpos = _parent->getWidth() - 420 + ((ev.pos_x + 430 - _parent->getWidth()) / 40 ) * 40;
                            _ypos = 120 + ((ev.pos_y - 110) / 40 - calculateD()) * 40;
                        }
                    } else {
                        if (_horizontal) {
                            _xpos = 40 + ((ev.pos_x - 30) / 40 - calculateD()) * 40;
                            _ypos = 120 + ((ev.pos_y - 110) / 40) * 40;
                        } else {
                            _xpos = 40 + ((ev.pos_x - 30) / 40) * 40;
                            _ypos = 120 + ((ev.pos_y - 110) / 40 - calculateD()) * 40;
                        }
                    }
                }
                else {
                    _xpos = ev.pos_x - _dx ;
                    _ypos = ev.pos_y - _dy;
                    if (ev.pos_x - _dx < 0) {
                        _xpos = 0;
                    }
                    if (ev.pos_x - _dx + _width >= _parent->getWidth()) {
                        _xpos = _parent->getWidth() - _width;
                    }
                    if (ev.pos_y - _dy < 0) {
                        _ypos = 0;
                    }
                    if (ev.pos_y - _dy + _height >= _parent->getHeight()) {
                        _ypos = _parent->getHeight() - _height;
                    }
                }
            }
        }
        if (ev.button == -btn_left) {
            if (_follow and !_static and _visible) {
                if (canPlace(_horizontal, ev.pos_x, ev.pos_y, _ssize, calculateD())) {
                    placeShip(this, false);
                    _my = (_ypos - 110) / 40;
                    if (_x0 < _parent->getWidth() / 2) {
                        _mx = (_xpos + 430 - _parent->getWidth()) / 40;
                    } else {
                        _mx = (_xpos - 30) / 40;
                    }
                }
                else {
                    _mx = _my = -1;
                    _xpos = _x0;
                    _ypos = _y0;
                    if (!_horizontal) {
                        _horizontal = true;
                        int tmp = _width;
                        _width = _height;
                        _height = tmp;
                    }
                }
                _dx = _dy = 0;
                _follow = false;
            }
        }
    }
    if (_follow and !_static and _visible and ev.type == ev_key and ev.keycode == 'r') {
        _horizontal = !_horizontal;
        int tmp = _width;
        _width = _height;
        _height = tmp;
        tmp = _dx;
        _dx = _dy;
        _dy = tmp;
        if (_xpos < 0) {
            _xpos = 0;
        }
        if (_xpos + _width >= _parent->getWidth()) {
            _xpos = _parent->getWidth() - _width;
        }
        if (_ypos < 0) {
            _ypos = 0;
        }
        if (_ypos + _height >= _parent->getHeight()) {
            _ypos = _parent->getHeight() - _height;
        }
        print(true);
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
    return !_static and _visible and (x >= _xpos) and (x < _xpos + _width) and (y >= _ypos) and (y < _ypos + _height);
}

bool Ship::getHorizontal() {
    return _horizontal;
}

int Ship::getShipSize() {
    return _ssize;
}

int Ship::calculateD() {
    if (_horizontal) {
        if (_dx < 30) {return 0;}
        else if (_dx < 70) {return 1;}
        else if (_dx < 110) {return 2;}
        else if (_dx < 150) {return 3;}
        else {return 4;}
    } else {
        if (_dy < 30) {return 0;}
        else if (_dy < 70) {return 1;}
        else if (_dy < 110) {return 2;}
        else if (_dy < 150) {return 3;}
        else {return 4;}
    }
}

int Ship::getPosX() {
    return _xpos;
}

int Ship::getPosY() {
    return _ypos;
}

int Ship::getMx() {
    return _mx;
}

int Ship::getMy() {
    return _my;
}
