#include "widgets.hpp"

using namespace genv;

Widget::Widget(Application * app, int x, int y, int w, int h) : _parent(app), _xpos(x), _ypos(y), _width(w), _height(h) {
    _parent->register_widget(this);
}

bool Widget::is_selected(int x, int y) {
    return (x >= _xpos) and (x < _xpos + _width) and (y >= _ypos) and (y < _ypos + _height);
}