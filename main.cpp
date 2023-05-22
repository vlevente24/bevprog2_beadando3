#include "application.hpp"
#include "widgets.hpp"
#include "playfield.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "textinput.hpp"
#include "gamemaster.hpp"
#include "field.hpp"
#include "ship.hpp"

using namespace genv;
using namespace std;

const string fontFileName = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const color white(255, 255, 255);
const color black(0, 0, 0);
const color green(0, 255, 0);
const color red(255, 0, 0);
const color blue(0, 0, 255);
const color lblue(130, 255, 255);

class Torpedo : public Application {
    GameMaster * GM;
    vector<PlayField*> _menus;
    int * _status;
    bool first;
    canvas * _nfld;
    canvas * _cfld;
    canvas * _icfld;
    Bomb * _bomb;

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

    TextBox * _plr1turn;
    TextBox * _plr2turn;

    TextBox * _winner;
    Button * _restart;
public:
    Torpedo() : Application(genv::color(255, 255, 255), 1000, 550), _status(new int(0)) {
        first = true;
        gout.open(_window_width, _window_height);
        gout.load_font(fontFileName, 20);
        string tmpname;

        // canvas
        {
            _nfld = new canvas(40, 40);
            *_nfld << move_to(0,0) << white << box(40, 40) << move_to(1,1) << lblue << box(38, 38);
            _cfld = new canvas(40, 40);
            *_cfld << move_to(0,0) << white << box(40, 40) << move_to(1,1) << lblue << box(38, 38);
            for (int i = 0; i < 40; i++) {
                for (int j = 0; j < 40; j++) {
                    if ((i - 20) * (i - 20) + (j - 20) * (j - 20) <= 100) {
                        *_cfld << move_to(i, j) << red << dot;
                    }
                }
            }
            _icfld = new canvas(40, 40);
            *_icfld << move_to(0,0) << white << box(40, 40) << move_to(1,1) << lblue << box(38, 38)
                    << move_to(5, 5) << blue << line_to(35, 35) << move_to(35, 5) << line_to(5, 35);
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
                                             [=](Field*fl){GM->fieldClick(fl);});
                    v2menu.push_back(_plr1f[i][j]);
                }
            }
            _plr1s = vector<Ship*>(15);
            int ii = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5 - i; j++) {
                    _plr1s[ii] = new Ship(this, _window_width / 2 + 40 + j * (i + 1) * 40, 300 + i * 40, i + 1,
                                          [=](bool b, int x, int y, int s, int d){
                        return this->canPlace(b, x, y, s, d);
                    }, [=](Ship*s, bool b){
                        this->placeShip(s, b);
                    });
                    v2menu.push_back(_plr1s[ii]);
                    ii++;
                }
            }
            tmpname = "NEXT Player";
            plr1ok = new Button(this, _window_width * 3 / 5 + 250, 50, gout.twidth(tmpname) + 10, 40, tmpname,
                                [=](){
                                    if (!canStep()) {
                                        gout.message("Please place all ships!");
                                    } else if (plr1->getText() == "") {
                                        plr1t->changeSign(true);
                                    } else {
                                        this->player1 = plr1->getText();
                                        this->resetLastPlayField();
                                        *_status = 2;
                                        this->setNewPlayField();
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
                                             _icfld,_cfld,[=](Field*fl){GM->fieldClick(fl);});
                    v3menu.push_back(_plr2f[i][j]);
                }
            }
            _plr2s = vector<Ship*>(15);
            int ii = 0;
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5 - i; j++) {
                    _plr2s[ii] = new Ship(this, 40 + j * (i + 1) * 40, 300 + i * 40, i + 1,
                                          [=](bool b, int x, int y, int s, int d){
                        return this->canPlace(b, x, y, s, d);
                    }, [=](Ship*s, bool b){
                        this->placeShip(s, b);
                    });
                    v3menu.push_back(_plr2s[ii]);
                    ii++;
                }
            }
            tmpname = "Start Game";
            plr2ok = new Button(this, 300, 50, gout.twidth(tmpname) + 10, 40, tmpname,
                                [=](){
                                    if (!canStep()) {
                                        gout.message("Please place all ships!");
                                    } else if (plr2->getText() == "") {
                                        plr2t->changeSign(true);
                                    } else {
                                        this->player2 = plr2->getText();
                                        this->resetLastPlayField();
                                        this->generatePlayfield(false);
                                        *_status = 3;
                                        this->setNewPlayField();
                                    }
                                }, fontFileName, 15, green, white);
            v3menu.push_back(plr2ok);
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v3menu,
                                           [=](){
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
    bool canPlace(bool hor, unsigned int x, unsigned int y, int s, int d) {
        bool b = true;
        if (*_status == 1) {
            if (hor) {
                int x0 = ((x - 30) / 40) - d, y0 = ((y - 110) / 40);
                if ((x0 + s > 10) or (x0 < 0) or (y0 < 0) or (y0 > 9)) {return false;}
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr1f[x0 + i][y0]->isShip());
                }
                return b;
            } else {
                int x0 = ((x - 30) / 40), y0 = ((y - 110) / 40) - d;
                if ((x0 > 9) or (x0 < 0) or (y0 < 0) or (y0 + s > 10)) {return false;}
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr1f[x0][y0 + i]->isShip());
                }
                return b;
            }
        } else if (*_status == 2) {
            if (hor) {
                int x0 = ((x + 430 - _window_width) / 40) - d, y0 = ((y - 110) / 40);
                if ((x0 + s > 10) or (x0 < 0) or (y0 < 0) or (y0 > 9)) {return false;}
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr2f[x0 + i][y0]->isShip());
                }
                return b;
            } else {
                int x0 = (x + 430 - _window_width) / 40, y0 = ((y - 110) / 40) - d;
                if ((x0 > 9) or (x0 < 0) or (y0 < 0) or (y0 + s > 10)) {return false;}
                for (int i = 0; i < s; i++) {
                    b = b and !(_plr2f[x0][y0 + i]->isShip());
                }
                return b;
            }
        }
        return false;
    }
    void placeShip(Ship *sh, bool del) {
        if (!del) {
            int x = sh->getPosX(), y = sh->getPosY();
            if (*_status == 1) {
                int x0 = (x - 30) / 40, y0 = (y - 110) / 40;
                if (sh->getHorizontal()) {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr1f[x0 + i][y0]->setShip(true, sh);
                    }
                } else {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr1f[x0][y0 + i]->setShip(true, sh);
                    }
                }
            } else if (*_status == 2) {
                int x0 = (x + 430 - _window_width) / 40, y0 = (y - 110) / 40;
                if (sh->getHorizontal()) {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr2f[x0 + i][y0]->setShip(true, sh);
                    }
                } else {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr2f[x0][y0 + i]->setShip(true, sh);
                    }
                }
            }
        } else if (del and sh->getMx() != -1 and sh->getMy() != -1) {
            if (*_status == 1) {
                if (sh->getHorizontal()) {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr1f[sh->getMx() + i][sh->getMy()]->setShip(false, 0);
                    }
                } else {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr1f[sh->getMx()][sh->getMy() + i]->setShip(false, 0);
                    }
                }
            }
            else if (*_status == 2) {
                if (sh->getHorizontal()) {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr2f[sh->getMx() + i][sh->getMy()]->setShip(false, 0);
                    }

                } else {
                    for (int i = 0; i < sh->getShipSize(); i++) {
                        _plr2f[sh->getMx()][sh->getMy() + i]->setShip(false, 0);
                    }
                }
            }
        }
    }
    bool canStep() {
        if (*_status == 1) {
            bool b = true;
            for (Ship * s : _plr1s) {
                b = b and s->getMx() != -1 and s->getMy() != -1;
            }
            return b;
        }
        if (*_status == 2) {
            bool b = true;
            for (Ship * s : _plr2s) {
                b = b and s->getMx() != -1 and s->getMy() != -1;
            }
            return b;
        }
        else {
            return false;
        }
    }
    void generatePlayfield(bool b) {
        if (*_status == 2 and first)
        {
            vector<Widget*> v4menu;
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    v4menu.push_back(_plr1f[i][j]);
                    v4menu.push_back(_plr2f[i][j]);
                }
            }
            for (int i = 0; i < 15; i++) {
                v4menu.push_back(_plr1s[i]);
                v4menu.push_back(_plr2s[i]);
            }
            gout.load_font(fontFileName, 30);
            _plr2turn = new TextBox(this, _window_width / 2 - gout.twidth(player2 + "'s turn") / 2,
                                    50, player2 + "'s turn",fontFileName, 30,
                                    white, black);
            _plr1turn = new TextBox(this, _window_width / 2 - gout.twidth(player1 + "'s turn") / 2,
                                    50, player1 + "'s turn",fontFileName, 30,
                                    white, black);
            v4menu.push_back(_plr1turn);
            v4menu.push_back(_plr2turn);
            _bomb = new Bomb(this);
            v4menu.push_back(_bomb);
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v4menu,
                                           [=](){
                gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height)
                     << move_to(20, 100) << color(255, 255, 220) << box(_window_width - 40, 420)
                     << move_to(_window_width / 2, 100) << black << line(0, 420);
                }, [](){}, [=](){
                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < 10; j++) {
                                _plr2f[i][j]->setClick(true);
                            }
                        }
                        _plr2turn->setVisibility(false);
                    }, [=](){
                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < 10; j++) {
                                _plr1f[i][j]->setClick(false);
                                _plr2f[i][j]->setClick(false);
                            }
                        }
                    }));

            GM = new GameMaster(_status, _bomb, _plr1turn, _plr2turn, _plr1f, _plr2f,
                                [=](){changeFocus();}, [=](bool b){generatePlayfield(b);});
        }
        else if (*_status == 3) {
            string s = (b ? player2 + " WIN" : player1 + " WIN");
            gout.load_font(fontFileName, 50);
            _winner = new TextBox(this, _window_width / 2 - gout.twidth(s) / 2, _window_height / 4, s,
                                  fontFileName, 50, white, black);
            /*
            s = "New Game";
            gout.load_font(fontFileName, 30);
            _restart = new Button(this, _window_width / 2 - gout.twidth(s) / 2, _window_height / 2,
                                  gout.twidth(s) + 10, 40, s, [=](){
                        for (int i = 0; i < 10; i++) {
                            for (int j = 0; j < 10; j++) {
                                _plr1f[i][j]->absReset();
                                _plr2f[i][j]->absReset();
                            }
                        }
                        for (int i = 0; i < 15; i++) {
                            _plr1s[i]->absReset();
                            _plr2s[i]->absReset();
                        }
                }, fontFileName, 30, green, black);
            */
            vector<Widget*> v5menu = {_winner/*, _restart*/};
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v5menu,
                                           [=](){
                gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);
            }, [](){}, [](){}, [](){}));
        }
    }
};

int main() {
    Torpedo torpedo;
    torpedo.event_loop();
    return 0;
}