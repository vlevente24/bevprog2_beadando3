#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "list.hpp"
#include <vector>

using namespace genv;
using namespace std;

List::List(Application * app, int x, int y, int w, int h, int myd, vector<string> v) : Widget(app, x, y, w, h), _value(""), _y_down_max(myd), _y_down(0), _sv(v), _index(v.size()), _shift(0) {
    _v = vector<canvas*>(v.size() + 1);
    //gout.load_font("/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf", 15);
    for (size_t i = 0; i < v.size(); i++) {
        _v[i] = new canvas(w, v.size() * (gout.cascent() + gout.cdescent() + 10));
        * _v[i] << color(134, 134, 134) << box(w, v.size() * (gout.cascent() + gout.cdescent() + 10)) << move_to(1, 0) << color(255, 255, 255) << box(w - 2, v.size() * (gout.cascent() + gout.cdescent() + 10));
        for (size_t j = 0; j < v.size(); j++) {
            if (j == i) {
                * _v[i] << move_to(1, j * (gout.cascent() + gout.cdescent() + 10)) << color(0, 120, 215) << box(w - 2, gout.cascent() + gout.cdescent() + 10) << move_to(5, j * (gout.cascent() + gout.cdescent() + 10) + 5 + gout.cascent()) << color(255, 255, 255) << text(v[i]);
            }
            else {
                * _v[i] << move_to(5, j * (gout.cascent() + gout.cdescent() + 10) + 5 + gout.cascent()) << color(0, 0, 0) << text(v[j]);
            }
        }
    }
    _v[v.size()] = new canvas(w, v.size() * (gout.cascent() + gout.cdescent() + 10));
    * _v[v.size()] << color(134, 134, 134) << box(w, v.size() * (gout.cascent() + gout.cdescent() + 10)) << move_to(1, 0) << color(255, 255, 255) << box(w - 2, v.size() * (gout.cascent() + gout.cdescent() + 10));
    for (size_t j = 0; j < v.size(); j++) {
        * _v[v.size()] << move_to(5, j * (gout.cascent() + gout.cdescent() + 10) + 5 + gout.cascent()) << color(0, 0, 0) << text(v[j]);
    }
}
List::~List() {
    for (size_t i = 0; i < _v.size(); i++) {
        delete _v[i];
    }
}

void List::print(bool marked) {
    gout << (marked ? color(20, 131, 218) : color(134, 134, 134));
    gout << move_to(_xpos, _ypos) << box(_width, _height) << move_to(_xpos + 2, _ypos + 2) << color(255, 255, 255) << box(_width - 4, _height - 4);
    gout << move_to(_xpos + 2 + 3, _ypos + 2 + 3) << color(0, 0, 0) << text(_value);
    print_btn((_y_down > 0 ? true : false));
    if (_y_down > 0) {print_box();}
}

void List::print_btn(bool down) {
    int button_w = (_height * 0.85 - 2), button_h = (_height - 2);
    gout << move_to(_xpos + _width - 1 - button_w, _ypos + 1) << (down ? color(18, 97, 161) : color(110, 110, 110)) << box(button_w, button_h) << move_to(_xpos + _width - button_w, _ypos + 2) << (down ? color(203, 228, 247) : color(240, 240, 240)) << box(button_w - 2, button_h - 2);
    gout << color(60, 60, 60);
    if (down) {
        gout << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h * 2 / 5) << line_to(_xpos + _width - 1 - button_w * 0.3, _ypos + 1 + button_h * 3 / 5) << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h * 2 / 5) << line_to(_xpos + _width - 1 - button_w * 0.7, _ypos + 1 + button_h * 3 / 5);
    }
    else {       
        gout << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h * 3 / 5) << line_to(_xpos + _width - 1 - button_w * 0.3, _ypos + 1 + button_h * 2 / 5) << move_to(_xpos + _width - 1 - button_w * 0.5, _ypos + 1 + button_h * 3 / 5) << line_to(_xpos + _width - 1 - button_w * 0.7, _ypos + 1 + button_h * 2 / 5);
    }
}

void List::print_box() {
    gout << move_to(_xpos, _ypos + _height) << color(0, 0, 0) << line(_width, 0);
    gout << stamp(*_v[_index], 0, _shift, _width, _y_down - 2, _xpos, _ypos + _height + 1);
    gout << move_to(_xpos, _ypos + _height + _y_down - 1) << color(0, 0, 0) << line(_width, 0);
}

void List::handle(event ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {
            // click to arrow
            if (ev.pos_x >= _xpos + _width - 1 - (_height * 0.85 - 2) and ev.pos_x < _xpos + _width - 1 and ev.pos_y >= _ypos + 1 and ev.pos_y < _ypos + _height - 1) {
                if (_y_down == 0) {
                    _y_down = (2 + _sv.size() * (gout.cascent() + gout.cdescent() + 10) >= _y_down_max ? _y_down_max : 2 + _sv.size() * (gout.cascent() + gout.cdescent() + 10));
                    print_btn(true);
                    print_box();
                }
                else {
                    reset();
                }
            }
            else if (ev.pos_x >= _xpos and ev.pos_x < _xpos + _width and ev.pos_y >= _ypos and ev.pos_y < _ypos + _height and _y_down > 0) {
                reset();
            }
            else if (ev.pos_x >= _xpos and ev.pos_x < _xpos + _width and ev.pos_y >= _ypos + _height and ev.pos_y < _ypos + _height + _y_down and _y_down > 0) {
                if (_index < _sv.size()) {
                    _value = _sv[_index];
                }
                reset();
            }
        }
        if (ev.button == 0) {
            if (ev.pos_x >= _xpos and ev.pos_x < _xpos + _width and ev.pos_y >= _ypos and ev.pos_y < _ypos + _height + _y_down and _y_down > 0) {
                _index = calc_index(ev.pos_y);
            }
        }
        if (ev.button == btn_wheelup) {
            if (ev.pos_x >= _xpos and ev.pos_x < _xpos + _width and ev.pos_y >= _ypos + _height and ev.pos_y < _ypos + _height + _y_down and _y_down > 0) {
                _shift = (_shift < 10 ? 0 : _shift - 10);
            }
        }
        if (ev.button == btn_wheeldown) {
            if (ev.pos_x >= _xpos and ev.pos_x < _xpos + _width and ev.pos_y >= _ypos + _height and ev.pos_y < _ypos + _height + _y_down and _y_down > 0) {
                _shift = (_y_down + _shift + 10 >= _sv.size() * (gout.cascent() + gout.cdescent() + 10) ? _sv.size() * (gout.cascent() + gout.cdescent() + 10) - _y_down - 1 : _shift + 10);
            }
        }
    }
}

int List::calc_index(int y) {
    if (y >= _ypos + _height + 1 and y < _ypos + _height + _y_down - 1) {
        return (_shift + y - 1 - _ypos - _height) / (gout.cascent() + gout.cdescent() + 10);
    }
    else {
        return (_v.size() - 1);
    }
}

bool List::is_selected(int x, int y) {
    return (x >= _xpos) and (x < _xpos + _width) and (y >= _ypos) and (y < _ypos + _height + _y_down);
}

void List::reset() {
    gout << move_to(_xpos, _ypos + _height) << _parent->get_color() << box(_width, _y_down);
    _y_down = 0;
    _index = _v.size() - 1;
    _shift = 0;
    print_btn(false);
}

string List::get_value() {
    return _value;
}