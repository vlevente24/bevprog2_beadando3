#include "widgets.hpp"
#include "textbox.hpp"

using namespace genv;

TextBox::TextBox(Application * app, int x, int y, std::string text, std::string fontfile, unsigned short fontsize, color bclr1,
                 color tclr1) : Widget(app, x, y, gout.twidth(text), gout.cascent() + gout.cdescent()), _text(text),
                _fontfile(fontfile), _fontsize(fontsize), bckgrndColor1(bclr1), txtColor1(tclr1) {}

void TextBox::print(bool marked) const {
    gout.load_font(_fontfile, _fontsize);
    if (_sign) {
        gout << bckgrndColor1 << move_to(_xpos, _ypos) << box(_width, _height);
        gout << move_to(_xpos, _ypos) << txtColor1 << text(_text);
    } else {
        gout << _parent->get_color() << move_to(_xpos, _ypos) << box(_width, _height);
        gout << move_to(_xpos, _ypos) << color(0, 0, 0) << text(_text);
    }
}

void TextBox::handle(event ev) {}

void TextBox::reset() {}

bool TextBox::is_selected(int a, int b) {
    return false;
}

void TextBox::changeSign(bool b) {
    _sign = b;
}
