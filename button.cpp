#include "button.hpp"

using namespace genv;
using namespace std;

Button::Button(Application * app, int x, int y, int w, int h, string text, function<void()> f,
               std::string fontfile, unsigned short fontsize, color bclr, color tclr) : Widget(app, x, y, w, h), _text(text), _f(f),
               _fontfile(fontfile), _fontsize(fontsize), backgroundColor(bclr), textColor(tclr) {}

void Button::print(bool) const {
    gout.load_font(_fontfile, _fontsize);
    gout << move_to(_xpos, _ypos) << backgroundColor << box(_width, _height)
         << move_to(_xpos + _width / 2 - gout.twidth(_text) / 2, _ypos + (_height - gout.cascent() - gout.cdescent()) / 2 )
         << textColor << text(_text);
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
