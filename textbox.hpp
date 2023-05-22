#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"

class TextBox : public Widget {
protected:
    const std::string _text;
    const std::string _fontfile;
    const unsigned short _fontsize;
    bool _sign, _visible;
    const genv::color bckgrndColor1;
    const genv::color txtColor1;
public:
    TextBox(Application*, int x, int y, std::string text, std::string fontfile, unsigned short fontsize,
            genv::color bclr1, genv::color tclr1);
    virtual ~TextBox() = default;
    bool is_selected(int, int) override;
    virtual void print(bool marked) const override;
    virtual void handle(genv::event ev) override;
    virtual void reset() override;
    virtual void changeSign(bool);
    virtual void setVisibility(bool);
};

#endif