#ifndef TORPEDO_FIELD_HPP
#define TORPEDO_FIELD_HPP

#include "widgets.hpp"
#include <functional>


class Field : public Widget {
    genv::canvas * _normal;
    genv::canvas * _incorrect;
    genv::canvas * _correct;
    bool _hit, _isShip;
    std::function<void(int, int)> _f;
public:
    Field(Application * app, int x, int y, int w, genv::canvas * norm, genv::canvas * inc, genv::canvas * corr, bool ship,
          std::function<void(int, int)> f);
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    void setHit();
    bool isShip();
    int getWidth();
};


#endif //TORPEDO_FIELD_HPP
