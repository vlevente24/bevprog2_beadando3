#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"
#include "textinput.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace genv;
using namespace std;

TextInput::TextInput(Application * app, int x, int y, int sx, int sy) : Widget(app, x, y, sx, sy), _text(""), _cursor_pos(0), _utf8_pos(utf8_character_index(_text)), _cursor_wait(0), _cursor_state(true) {}

void TextInput::print(bool marked) {
    gout << (marked ? color(20, 131, 218) : color(134, 134, 134));
    gout << move_to(_xpos, _ypos) << box(_width, _height) << move_to(_xpos + 2, _ypos + 2) << color(255, 255, 255) << box(_width - 4, _height - 4);
    gout << move_to(_xpos + 5, _ypos + 5) << color(0, 0, 0) << text(_text);;
    if (marked and _cursor_state) {
        gout << move_to(_xpos + 5 + gout.twidth(_text.substr(0, _utf8_pos[_cursor_pos])), _ypos + 4) << color(0, 0, 0) << line(0, gout.cascent() + gout.cdescent() + 1);
    }
}

void TextInput::handle(event ev) {
    if (_cursor_wait == 0) {
        _cursor_wait = 600;
        gin.timer(_cursor_wait);
    }
    if (ev.type == ev_key) {
        _utf8_pos = utf8_character_index(_text);
        int textreallength = (_utf8_pos.size() - 1);
        if (ev.keycode == key_backspace and (_cursor_pos - 1) >= 0) {
            _text = utf8_remove_last(_text.substr(0, _utf8_pos[_cursor_pos])) + _text.substr(_utf8_pos[_cursor_pos]);
            _utf8_pos = utf8_character_index(_text);
            textreallength = (_utf8_pos.size() - 1);
            _cursor_pos -= (_cursor_pos - 1 >= 0 ? 1 : 0);
            _cursor_state = true;
            _cursor_wait = 0;
        }
        else if (gout.twidth(_text + ev.keyutf8) > _width - 2 * (2 + 5)) {}
        else if (ev.keycode == key_right and (_cursor_pos + 1) <= textreallength) {
            _cursor_pos += (_cursor_pos + 1 <= textreallength ? 1 : 0);
            _cursor_state = true;
            _cursor_wait = 0;
        }
        else if (ev.keycode == key_left and (_cursor_pos - 1) >= 0) {
            _cursor_pos -= (_cursor_pos - 1 >= 0 ? 1 : 0);
            _cursor_state = true;
            _cursor_wait = 0;
        }
        else if (ev.keyutf8 != "") {
            _text = _text.substr(0, _utf8_pos[_cursor_pos]) + ev.keyutf8 + _text.substr(_utf8_pos[_cursor_pos]);
            _utf8_pos = utf8_character_index(_text);
            textreallength = (_utf8_pos.size() - 1);
            _cursor_pos += (_cursor_pos + 1 <= textreallength ? 1 : 0);
            _cursor_state = true;
            _cursor_wait = 0;
        }
    }
    if (ev.type == ev_timer) {
        _cursor_state = !_cursor_state;
    }
}

void TextInput::reset() {
    _cursor_wait = 0;
    gin.timer(_cursor_wait);
}

string TextInput::get_text() const {
    return _text;
}