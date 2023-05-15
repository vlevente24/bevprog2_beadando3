#ifndef WIDGETS_BUTTON_HPP
#define WIDGETS_BUTTON_HPP

#include "widgets.hpp"
#include <functional>

class Button : public Widget {
    std::string _text;
    std::function<void()> _f;
public:
    Button(Application * app, int x, int y, int w, int h, std::string text, std::function<void()> f);
    void print(bool) override;
    void handle(genv::event) override;
    void reset() override;
    void action();
};


#endif //WIDGETS_BUTTON_HPP
