#include "field.hpp"
#include "gamemaster.hpp"

using namespace genv;
using namespace std;

Field::Field(Application *app, int x, int y, int w, canvas *norm, canvas *inc, canvas *corr, bool ship, function<void(int, int)> f) :
             Widget(app, x, y, w, w), _normal(norm), _incorrect(inc), _correct(corr), _isShip(ship), _hit(false), _f(f) {

}

void Field::reset() {}

void Field::handle(genv::event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (is_selected(ev.pos_x, ev.pos_y)) {
                _f(_xpos, _ypos);
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
}

bool Field::isShip() {
    return _isShip;
}

int Field::getWidth() {
    return _width;
}
