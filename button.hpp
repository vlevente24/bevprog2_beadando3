#ifndef WIDGETS_BUTTON_HPP
#define WIDGETS_BUTTON_HPP

#include "widgets.hpp"
#include <functional>

class Button : public Widget {
    const std::string _text;
    std::function<void()> _f;
    const std::string _fontfile;
    const unsigned short _fontsize;
    const genv::color backgroundColor;
    const genv::color textColor;
public:
    Button(Application * app, int x, int y, int w, int h, std::string text, std::function<void()> f,
           std::string fontfile, unsigned short fontsize, genv::color bclr, genv::color tclr);
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void action();
};


#endif //WIDGETS_BUTTON_HPP
