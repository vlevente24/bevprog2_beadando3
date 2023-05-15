#include "application.hpp"
#include "widgets.hpp"
using namespace genv;

Application::Application(genv::color background_color, int width, int height) : _bckgrnd_clr(background_color), _window_width(width), _window_height(height) {}

void Application::event_loop() {
    event ev;
    int focus = -1;
    while (gin >> ev and ev.keycode != key_escape) {
        if (ev.type == ev_mouse and ev.button == btn_left) {
            if (!(focus != -1 and _widgets[focus]->is_selected(ev.pos_x, ev.pos_y))) {
                if (focus != -1) {_widgets[focus]->reset();}
                focus = -1;
                for (size_t i = 0; i < _widgets.size(); i++) {
                    if (_widgets[i]->is_selected(ev.pos_x, ev.pos_y)) {
                        focus = i;
                    }
                }
            }
        }
        action(ev);
        if (focus != -1) {
            _widgets[focus]->handle(ev);
        }
        for (Widget * w : _widgets) {
            w->print(false);
        }
        if (focus != -1) {
            _widgets[focus]->print(true);
        }
        gout << refresh;
    }
}

void Application::register_widget(Widget * w) {
    _widgets.push_back(w);
}

genv::color Application::get_color() {
    return _bckgrnd_clr;
}