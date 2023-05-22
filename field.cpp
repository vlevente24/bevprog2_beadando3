#include "field.hpp"
#include "gamemaster.hpp"

using namespace genv;
using namespace std;

Field::Field(Application *app, int x, int y, int w, canvas *norm, canvas *inc, canvas *corr, function<void(Field*)> f) :
             Widget(app, x, y, w, w), _normal(norm), _incorrect(inc), _correct(corr), _isShip(false), _hit(false), _f(f),
             _clickable(false) {}

void Field::reset() {}

void Field::handle(genv::event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (is_selected(ev.pos_x, ev.pos_y)) {
                _f(this);
            }
        }
    }
}

void Field::print(bool) const {
    if (_hit) {
        if (_isShip) {
            gout << stamp(*_correct, _xpos, _ypos);
        } else {
            gout << stamp(*_incorrect, _xpos, _ypos);
        }
    } else {
        gout << stamp(*_normal, _xpos, _ypos);
    }
}

void Field::setHit() {
    _hit = true;
    if (_ship and _isShip) {
        _ship->hit();
        if (isShipDead()) {
            _ship->setVisibility(true);
        }
    }
}

bool Field::isShip() const {
    return _isShip;
}

int Field::getWidth() {
    return _width;
}

void Field::setShip(bool b, Ship * sh) {
    _isShip = b;
    _ship = sh;
}

bool Field::is_selected(int x, int y) {
    return (x >= _xpos) and (x < _xpos + _width) and (y >= _ypos) and (y < _ypos + _height) and _clickable;
}

void Field::setClick(bool b) {
    _clickable = b;
}

int Field::getPosX() {
    return _xpos;
}

int Field::getPosY() {
    return _ypos;
}

bool Field::isShipDead() {
    if (_isShip and _ship) {
        return _ship->isDead();
    }
    else {
        return false;
    }
}

bool Field::isHit() {
    return _hit;
}

void Field::absReset() {
    _isShip = false;
    _hit = false;
    _clickable = false;
}
