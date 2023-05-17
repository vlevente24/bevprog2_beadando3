#ifndef WIDGETS_HPP
#define WIDGETS_HPP

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "application.hpp"

class Widget {
protected:
    Application * _parent;
    int _xpos, _ypos;
    int _width, _height;
public:
    Widget(Application * app, int x, int y, int w, int h);
    virtual ~Widget() = default;
    virtual bool is_selected(int, int);
    virtual void print(bool) const = 0;
    virtual void handle(genv::event) = 0;
    virtual void reset() = 0;
};

#endif