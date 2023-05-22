#include "gamemaster.hpp"

using namespace std;

GameMaster::GameMaster(int * st, Bomb *bmb, TextBox *tb1, TextBox *tb2, std::vector<std::vector<Field*>> p1f,
                       std::vector<std::vector<Field*>>p2f, function<void()> f, function<void(bool)> win) : status(st), _f(f),
                       _bomb(bmb), _plr1f(p1f), _plr2f(p2f), isPlayer1(true), _tb1(tb1), _tb2(tb2), _win(win) {}

void GameMaster::fieldClick(Field*fl) {
    if (*status == 3) {
        _bomb->PlayBombA(fl->getPosX(), fl->getPosY());
        _f();
        fl->setHit();
        fl->setClick(false);
        // player change
        if (!(fl->isShip())) {
            if (isPlayer1) {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        _plr2f[i][j]->setClick(false);
                        if (!(_plr1f[i][j]->isHit())) {
                            _plr1f[i][j]->setClick(true);
                        }
                    }
                }
                _tb1->setVisibility(false);
                _tb2->setVisibility(true);
            }
            else {
                for (int i = 0; i < 10; i++) {
                    for (int j = 0; j < 10; j++) {
                        _plr1f[i][j]->setClick(false);
                        if (!(_plr2f[i][j]->isHit())) {
                            _plr2f[i][j]->setClick(true);
                        }
                    }
                }
                _tb1->setVisibility(true);
                _tb2->setVisibility(false);
            }
            isPlayer1 = !isPlayer1;
        }
        bool b1 = true;
        for (vector<Field*> vf : _plr1f) {
            for (Field * fld : vf) {
                if (fld->isShip()) {
                    b1 = b1 and fld->isShipDead();
                }
            }
        }
        bool b2 = true;
        for (vector<Field*> vf : _plr2f) {
            for (Field * fld : vf) {
                if (fld->isShip()) {
                    b2 = b2 and fld->isShipDead();
                }
            }
        }
        if (b1) {
            _win(true);     // p2 win
            *status = 4;
        }
        else if (b2) {
            _win(false);    // p1 win
            *status = 4;
        }
    }
}

void GameMaster::fieldClick2() {

}
