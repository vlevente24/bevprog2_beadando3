#include "playfield.hpp"

using namespace genv;
using namespace std;

PlayField::PlayField(Application * app, int x, int y, int w, int h, vector<Widget*> vw, function<void()> drwBckgrnd, function<void()> f,
                     function<void()> set, std::function<void()> reset) : Widget(app, x, y, w, h), _things(vw),
                     _drawBackground(drwBckgrnd), _handle(f), _set(set), _reset(reset), _focus(-1), focusChange(false) {}

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
        if (focusChange) {focusChange = false; gin.timer(0);}
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
    _handle();
    print(true);
    gout << refresh;
}

void PlayField::reset() {
    _parent->clearWindow();
    _reset();
}

void PlayField::changeFocus() {
    if (!(_focus != -1 and _things[_focus]->is_selected(-1, -1))) {
        if (_focus != -1) {_things[_focus]->reset();}
        _focus = -1;
        for (size_t i = 0; i < _things.size(); i++) {
            if (_things[i]->is_selected(-1, -1)) {
                _focus = i;
            }
        }
    }
    gin.timer(1);
}

void PlayField::set() {
    _set();
}
