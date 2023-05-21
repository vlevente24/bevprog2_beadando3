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
    bool _hit, _isShip;
    std::function<void(int, int)> _f;
public:
    Field(Application * app, int x, int y, int w, genv::canvas * norm, genv::canvas * inc, genv::canvas * corr,
          std::function<void(int, int)> f);
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void setHit();
    bool isShip() const;
    void setShip(bool, Ship*);
    int getWidth();
};


#endif //TORPEDO_FIELD_HPP
