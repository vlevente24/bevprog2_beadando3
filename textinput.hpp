#ifndef TEXTINPUT_HPP
#define TEXTINPUT_HPP

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"

class TextInput : public Widget {
protected:
    std::string _text;
    int _cursor_pos, _cursor_wait;
    bool _cursor_state;
    std::vector<int> _utf8_pos;
public:
    TextInput(Application*, int x, int y, int w, int h);
    virtual void print(bool marked) const override;
    virtual void handle(genv::event ev) override;
    virtual void reset() override;
    std::string getText() const;
};

#endif