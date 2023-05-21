#ifndef TORPEDO_SHIP_HPP
#define TORPEDO_SHIP_HPP

#include "widgets.hpp"
#include <functional>

class Ship : public Widget {
    int _ssize, _dx, _dy, _x0, _y0, _mx, _my;
    bool _visible, _horizontal, _static, _follow;
    std::function<bool(bool,int,int,int,int)> canPlace;
    std::function<void(Ship*,bool)> placeShip;
    int calculateD();
public:
    Ship(Application * app, int x, int y, int shipsize, std::function<bool(bool,int,int,int,int)> cp,
         std::function<void(Ship*,bool)> ps);
    bool is_selected(int x, int y) override;
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void setVisibility(bool);
    void setStatic(bool);
    bool getHorizontal();
    int getShipSize();
    int getPosX();
    int getPosY();
    int getMx();
    int getMy();
};


#endif //TORPEDO_SHIP_HPP
