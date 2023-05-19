#include "application.hpp"
#include "widgets.hpp"
#include "playfield.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "textinput.hpp"
#include "gamemaster.hpp"
#include "field.hpp"
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
    int * _status;
    string player1, player2;
    vector<PlayField*> _menus;
    TextBox * title;
    Button * beginning;
    TextBox * plr1t;
    TextInput * plr1;
    Button * plr1ok;
    TextBox * plr2t;
    TextInput * plr2;
    Button * plr2ok;
    canvas * _nfld;
    canvas * _cfld;
    canvas * _icfld;
    Field * fld1;
    Bomb * _bomb;
    vector<vector<Field*>> _plr1f;
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
                                   [=](){*_status = 1;}, fontFileName, 20, green, white);

            tmpname = "Torpedo";
            gout.load_font(fontFileName, 50);
            title = new TextBox(this, _window_width / 2 - gout.twidth(tmpname) / 2, _window_height / 4, tmpname,
                                fontFileName, 50, white, black);
            vector<Widget*> v1menu = {title, beginning};

            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v1menu,
                                           [=](){gout << move_to(0, 0) << _bckgrnd_clr
                                           << box(_window_width, _window_height);}, [](){}));
        }
        // 1st player options window
        {
            gout.load_font(fontFileName, 15);
            tmpname = "Player 1 name:";
            plr1t = new TextBox(this, _window_width * 3 / 5, 40, tmpname, fontFileName, 15,
                                red, white);
            plr1 = new TextInput(this, _window_width * 3 / 5, 60, 200, 25);
            tmpname = "NEXT Player";
            plr1ok = new Button(this, _window_width * 3 / 5 + 250, 50, gout.twidth(tmpname) + 10, 40, tmpname,
                                [=](){
                if (plr1->getText() != "") {
                    this->player1 = plr1->getText();
                    *_status = 2;
                } else {
                    plr1t->changeSign(true);
                }
            }, fontFileName, 15, green, white);
            vector<Widget*> v2menu = {plr1t, plr1, plr1ok};
            _plr1f = vector<vector<Field*>>(10, vector<Field*>(10));
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    _plr1f[i][j] = new Field(this, 30 + i * 40, 110 + j * 40, 40, _nfld, _icfld, _cfld,
                                             false,[=](int x, int y){GM->fieldClick(x, y);});
                    v2menu.push_back(_plr1f[i][j]);
                }
            }
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v2menu,
                                           [=](){
                gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);
                gout << move_to(20, 100) << color(255, 255, 220) << box(_window_width - 40, 420);

            }, [=](){
                if (plr1->getText() != "") {
                    plr1t->changeSign(false);
                }
            }));
            }
        // play window
        {
            fld1 = new Field(this, 100, 400, 40, _nfld, _nfld, _nfld, false,
                             [=](int x, int y){GM->fieldClick(x, y);});
            _bomb = new Bomb(this);
            vector<Widget*> v4menu = {fld1, _bomb};
            _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v4menu,
                    [=](){
                        gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height)
                             << move_to(10, 100) << color(0, 255, 0) << box(400, 400);
                }, [](){}));
        }


        GM = new GameMaster(_status, [=](int x, int y){_bomb->PlayBombA(x, y); changeFocus();});
        _menus[0]->print(true);
        gout << refresh;
    }
    void action(genv::event ev) override {
        _menus[*_status]->handle(ev);
    }
    void changeFocus() {
        _menus[*_status]->changeFocus();
    }
};

int main() {
    Torpedo torpedo;
    torpedo.event_loop();
    return 0;
}