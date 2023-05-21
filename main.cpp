#include "application.hpp"
#include "widgets.hpp"
#include "playfield.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "textinput.hpp"
#include "gamemaster.hpp"
#include "field.hpp"
#include "ship.hpp"
#include <iostream>

using namespace genv;
using namespace std;

const string fontFileName = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const color white(255, 255, 255);
const color black(0, 0, 0);
const color green(0, 255, 0);
const color red(255, 0, 0);
const color lblue(130, 255, 255);

class Torpedo : public Application {
    GameMaster * GM;
    vector<PlayField*> _menus;
    int * _status;
    canvas * _nfld;
    canvas * _cfld;
    canvas * _icfld;
    Bomb * _bomb;

    Field * fld1;   // majd eltűnik
    TextBox * title;
    Button * beginning;

    string player1;
    TextBox * plr1t;
    TextInput * plr1;
    Button * plr1ok;
    vector<vector<Field*>> _plr1f;
    vector<Ship*> _plr1s;

    string player2;
    TextBox * plr2t;
    TextInput * plr2;
    Button * plr2ok;
    vector<vector<Field*>> _plr2f;
    vector<Ship*> _plr2s;
public:
    Torpedo() : Application(genv::color(255, 255, 255), 1000, 550), _status(new int(0)) {
        gout.open(_window_width, _window_height);
        gout.load_font(fontFileName, 20);
        string tmpname;

        // canvas
        {
            _nfld = new canvas(40, 40);
            *_nfld << move_to(0,0) << white << box(40, 40) << move_to(1,1) << lblue << box(38, 38);
        }

        // welcome window
        {
            tmpname = "Start Placing Ships";
            beginning = new Button(this, _window_width / 2 - gout.twidth(tmpname) / 2, _window_height / 2,
                                   gout.twidth(tmpname) + 10,gout.cascent() + gout.cdescent() + 10, tmpname,
                                   [=](){ this->resetLastPlayField(); *_status = 1; this->setNewPlayField();},
                                   fontFileName, 20, green, white);

            tmpname = "Torpedo";
            gout.load_font(fontFileName, 50);
            title = new TextBox(this, _window_width / 2 - gout.twidth(tmpname) / 2, _window_height / 4, tmpname,
                                fontFileName, 50, white, black);
            vector<Widget*> v1menu = {title, beginning};

            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v1menu,
                                           [=](){gout << move_to(0, 0) << _bckgrnd_clr
                                           << box(_window_width, _window_height);}, [](){}, [](){},
                                           [](){}));
        }
        // 1st player options window
        {
            gout.load_font(fontFileName, 15);
            tmpname = "Player 1 name:";
            plr1t = new TextBox(this, _window_width * 3 / 5, 40, tmpname, fontFileName, 15,
                                red, white);
            plr1 = new TextInput(this, _window_width * 3 / 5, 60, 200, 25);
            vector<Widget*> v2menu = {plr1t, plr1};
            _plr1f = vector<vector<Field*>>(10, vector<Field*>(10));
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    _plr1f[i][j] = new Field(this, 30 + i * 40, 110 + j * 40, 40, _nfld, _icfld, _cfld,
                                             [=](int x, int y){GM->fieldClick(x, y);});
                    v2menu.push_back(_plr1f[i][j]);
                }
            }
            _plr1s = vector<Ship*>(15);
            int ii = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5 - i; j++) {
                    _plr1s[ii] = new Ship(this, _window_width / 2 + 40 + j * (i + 1) * 40, 300 + i * 40, i + 1,
                                          [=](bool b, int x, int y, int s){
                        return this->canPlace(b, x, y, s);
                    }, [=](Ship*s, int x, int y){
                        this->placeShip(s, x, y);
                    });
                    v2menu.push_back(_plr1s[ii]);
                    ii++;
                }
            }
            tmpname = "NEXT Player";
            plr1ok = new Button(this, _window_width * 3 / 5 + 250, 50, gout.twidth(tmpname) + 10, 40, tmpname,
                                [=](){
                                    if (plr1->getText() != "") {
                                        this->player1 = plr1->getText();
                                        this->resetLastPlayField();
                                        *_status = 2;
                                        this->setNewPlayField();
                                    } else if (false) {

                                    } else {
                                        plr1t->changeSign(true);
                                    }
                                }, fontFileName, 15, green, white);
            v2menu.push_back(plr1ok);
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v2menu,[=](){
                gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);
                gout << move_to(20, 100) << color(255, 255, 220) << box(_window_width - 40, 420);
            }, [=](){
                if (plr1->getText() != "") {
                    plr1t->changeSign(false);
                }
            }, [=](){
                    for (Ship * s : _plr1s) {
                        s->setVisibility(true);
                        s->setStatic(false);
                    }
                }, [=](){
                    for (Ship * s : _plr1s) {
                        s->setVisibility(false);
                        s->setStatic(true);
                    }
            }));
        }

        // 2nd player options window
        {
            gout.load_font(fontFileName, 15);
            tmpname = "Player 2 name:";
            plr2t = new TextBox(this, 50, 40, tmpname, fontFileName, 15,
                                red, white);
            plr2 = new TextInput(this, 50, 60, 200, 25);
            vector<Widget*> v3menu = {plr2t, plr2};
            _plr2f = vector<vector<Field*>>(10, vector<Field*>(10));
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    _plr2f[i][j] = new Field(this, _window_width - 430 + i * 40, 110 + j * 40, 40, _nfld,
                                             _icfld,_cfld,[=](int x, int y){GM->fieldClick(x, y);});
                    v3menu.push_back(_plr2f[i][j]);
                }
            }
            _plr2s = vector<Ship*>(15);
            int ii = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5 - i; j++) {
                    _plr2s[ii] = new Ship(this, 40 + j * (i + 1) * 40, 300 + i * 40, i + 1,
                                          [=](bool b, int x, int y, int s){
                        return this->canPlace(b, x, y, s);
                    }, [=](Ship*s, int x, int y){
                        this->placeShip(s, x, y);
                    });
                    v3menu.push_back(_plr2s[ii]);
                    ii++;
                }
            }
            tmpname = "Start Game";
            plr2ok = new Button(this, 300, 50, gout.twidth(tmpname) + 10, 40, tmpname,
                                [=](){
                                    if (plr2->getText() != "") {
                                        this->player2 = plr2->getText();
                                        this->resetLastPlayField();
                                        *_status = 3;
                                        this->setNewPlayField();
                                    } else if (false) {

                                    } else {
                                        plr2t->changeSign(true);
                                    }
                                }, fontFileName, 15, green, white);
            v3menu.push_back(plr2ok);
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v3menu,[=](){
                gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);
                gout << move_to(20, 100) << color(255, 255, 220) << box(_window_width - 40, 420);
            }, [=](){
                if (plr2->getText() != "") {
                    plr2t->changeSign(false);
                }
            }, [=](){
                    for (Ship * s : _plr2s) {
                        s->setVisibility(true);
                        s->setStatic(false);
                    }
                }, [=](){
                    for (Ship * s : _plr2s) {
                        s->setVisibility(false);
                        s->setStatic(true);
                    }
            }));
        }

        // play window
        {
            fld1 = new Field(this, 100, 400, 40, _nfld, _nfld, _nfld,
                             [=](int x, int y){GM->fieldClick(x, y);});
            _bomb = new Bomb(this);
            vector<Widget*> v4menu = {fld1, _bomb};
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v4menu,
                    [=](){
                        gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height)
                             << move_to(10, 100) << color(0, 255, 0) << box(400, 400);
                }, [](){}, [](){}, [](){}));
        }


        GM = new GameMaster(_status, [=](int x, int y){_bomb->PlayBombA(x, y); changeFocus();});
        _menus[0]->print(true);
        gout << refresh;
    }
    void action(genv::event ev) override {
        _menus[*_status]->handle(ev);
    }
    void setNewPlayField() {
        _menus[*_status]->set();
    }
    void resetLastPlayField() {
        _menus[*_status]->reset();
    }
    void changeFocus() {
        _menus[*_status]->changeFocus();
    }
    bool canPlace(bool hor, int x, int y, int s) {
        bool b;
        if (*_status == 1) {
            b = (x >= 30) and (x < 430) and (y >= 110) and (y < 510);
                if (!b) {return false;}

            int x0 = (x - 30) / 40, y0 = (y - 110) / 40;
            if (hor) {
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr1f[x0][y0 + i]->isShip());
                }
            } else {
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr1f[x0 + i][y0]->isShip());
                }
            }
            return b;
        } else if (*_status == 2) {
            b = (x >= _window_width - 430) and (x < _window_width - 30) and (y >= 110) and (y < 510);
                if (!b) {return false;}

            int x0 = (x + 430 - _window_width) / 40, y0 = (y - 110) / 40;
            if (hor) {
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr2f[x0][y0 + i]->isShip());
                }
            } else {
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr2f[x0 + i][y0]->isShip());
                }
            }
            return b;
        }
    }
    void placeShip(Ship *sh, int x, int y) {
        if (*_status == 1 and (x >= 30) and (x < 430) and (y >= 110) and (y < 510)) {
            int x0 = (x - 30) / 40, y0 = (y - 110) / 40;
            if (sh->getHorizontal()) {
                for (int i = 0; i < sh->getShipSize(); i++) {
                    _plr1f[x0][y0 + i]->setShip(true, sh);
                }
            } else {
                for (int i = 0; i < sh->getShipSize(); i++) {
                    _plr1f[x0 + i][y0]->setShip(true, sh);
                }
            }
        } else if (*_status == 2 and (x >= _window_width - 430) and (x < _window_width - 30) and (y >= 110) and (y < 510)) {
            int x0 = (x + 430 - _window_width) / 40, y0 = (y - 110) / 40;
            if (sh->getHorizontal()) {
                for (int i = 0; i < sh->getShipSize(); i++) {
                    _plr1f[x0][y0 + i]->setShip(true, sh);
                }
            } else {
                for (int i = 0; i < sh->getShipSize(); i++) {
                    _plr1f[x0 + i][y0]->setShip(true, sh);
                }
            }
        }
    }
};

int main() {
    Torpedo torpedo;
    torpedo.event_loop();
    return 0;
}