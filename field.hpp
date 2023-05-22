#ifndef TORPEDO_FIELD_HPP
#define TORPEDO_FIELD_HPP

#include "widgets.hpp"
#include "ship.hpp"
#include <functional>


class Field : public Widget {
    genv::canvas * _normal;
    genv::canvas * _incorrect;
    genv::canvas * _correct;
    Ship * _ship;
    bool _hit, _isShip, _clickable;
    std::function<void(Field*)> _f;
public:
    Field(Application * app, int x, int y, int w, genv::canvas * norm, genv::canvas * inc, genv::canvas * corr,
          std::function<void(Field*)> f);
    bool is_selected(int x, int y) override;
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void setHit();
    bool isHit();
    bool isShip() const;
    void setShip(bool, Ship*);
    int getWidth();
    void setClick(bool);
    int getPosX();
    int getPosY();
    bool isShipDead();
    void absReset();
};


#endif //TORPEDO_FIELD_HPP
