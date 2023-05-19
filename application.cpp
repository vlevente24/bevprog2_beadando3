#include "application.hpp"
#include "widgets.hpp"
using namespace genv;

Application::Application(genv::color background_color, int width, int height) : _bckgrnd_clr(background_color),
                        _window_width(width), _window_height(height) {}

void Application::event_loop() {
    event ev;
    while (gin >> ev and ev.keycode != key_escape) {
        action(ev);
    }
}

void Application::register_widget(Widget * w) {
    _widgets.push_back(w);
}

genv::color Application::get_color() {
    return _bckgrnd_clr;
}

void Application::clearWindow() {
    gout << _bckgrnd_clr << move_to(0, 0) << box(_window_width, _window_height);
}

int Application::getWidth() {
    return _window_width;
}

int Application::getHeight() {
    return _window_height;
}
