#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <vector>
#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"

class Widget;

class Application {
protected:
    std::vector<Widget*> _widgets;
    genv::color _bckgrnd_clr;
    int _window_width, _window_height;
public:
    Application(genv::color background_color, int width, int height);
    void event_loop();
    void register_widget(Widget*);
    virtual void action(genv::event) = 0;
    genv::color get_color();
};

#endif