#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"
#include "textbox.hpp"

using namespace genv;

TextBox::TextBox(Application * app, int x, int y, int w, int h, std::string text) : Widget(app, x, y, w, h), _text(text) {}

void TextBox::print(bool marked) {
    gout << _parent->get_color() << move_to(_xpos, _ypos) << box(_width, _height);
    gout << move_to(_xpos, _ypos) << color(0, 0, 0) << text(_text);
}

void TextBox::handle(event ev) {}

void TextBox::reset() {}

bool TextBox::is_selected(int a, int b) {
    return false;
}