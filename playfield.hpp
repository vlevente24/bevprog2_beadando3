#ifndef TORPEDO_PLAYFIELD_HPP
#define TORPEDO_PLAYFIELD_HPP

#include "widgets.hpp"
#include <functional>

class PlayField : public Widget {
    std::vector<Widget*> _things;
    int _focus;
    std::function<void()> _drawBackground, _handle, _set, _reset;
    bool focusChange;
public:
    PlayField(Application * app, int x, int y, int w, int h, std::vector<Widget*>, std::function<void()> drwBckgrnd,
              std::function<void()> handl, std::function<void()> set, std::function<void()> reset);
    bool is_selected(int, int) override;
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void changeFocus();
    void set();
};


#endif //TORPEDO_PLAYFIELD_HPP
