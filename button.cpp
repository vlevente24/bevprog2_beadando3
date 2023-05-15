#include "button.hpp"

using namespace genv;
using namespace std;

Button::Button(Application * app, int x, int y, int w, int h, string text, function<void()> f) : Widget(app, x, y, w, h), _text(text), _f(f) {}

void Button::print(bool) { // legyen const majd
    gout << move_to(_xpos, _ypos) << color(200, 200, 200) << box(_width, _height)
         << move_to(_xpos + _width / 2 - gout.twidth(_text) / 2, _ypos + _height / 2) << color(0, 0, 0) << text(_text);
}

void Button::handle(genv::event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            if (is_selected(ev.pos_x, ev.pos_y)) {
                action();
            }
        }
    }
}

void Button::reset() {}

void Button::action() {
    _f();
}
