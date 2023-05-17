#include "playfield.hpp"

using namespace genv;
using namespace std;

PlayField::PlayField(Application * app, int x, int y, int w, int h, vector<Widget*> vw, function<void()> drwBckgrnd,
                     function<void()> f) : Widget(app, x, y, w, h), _things(vw), _drawBackground(drwBckgrnd), _f(f), _focus(-1) {
    /*
    _bomb = new canvas(31, 31);
    for (int i = 0; i < 31; i++) {
        for (int j = 0; j < 31; j++) {
            if ((i - 15) * (i - 15) + (j - 15) * (j - 15) <= 225) {
                *_bomb << color(1, 1, 1) << dot;
            }
        }
    }
    _bomb->transparent(true);
     */
}

bool PlayField::is_selected(int, int) {
    return false;
}

void PlayField::print(bool) const {
    _drawBackground();
    for (Widget * w : _things) {
        w->print(false);
    }
    if (_focus != -1) {
        _things[_focus]->print(true);
    }
}

void PlayField::handle(genv::event ev) {
    if (ev.type == ev_mouse and ev.button == btn_left) {
        if (!(_focus != -1 and _things[_focus]->is_selected(ev.pos_x, ev.pos_y))) {
            if (_focus != -1) {_things[_focus]->reset();}
            _focus = -1;
            for (size_t i = 0; i < _things.size(); i++) {
                if (_things[i]->is_selected(ev.pos_x, ev.pos_y)) {
                    _focus = i;
                }
            }
        }
    }
    if (_focus != -1) {
        _things[_focus]->handle(ev);
    }
    _f();
    print(true);
    gout << refresh;
}

void PlayField::reset() {
    _parent->clearWindow();
}