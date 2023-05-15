#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"

class TextBox : public Widget {
protected:
    const std::string _text;
public:
    TextBox(Application*, int x, int y, int w, int h, std::string text);
    virtual ~TextBox() = default;
    bool is_selected(int, int) override;
    virtual void print(bool marked) override;
    virtual void handle(genv::event ev) override;
    virtual void reset() override;
};

#endif