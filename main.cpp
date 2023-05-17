#include "application.hpp"
#include "widgets.hpp"
#include "playfield.hpp"
#include "button.hpp"
#include "textbox.hpp"
#include "textinput.hpp"

using namespace genv;
using namespace std;

const string fontFileName = "/Users/levente/Desktop/ITK_graphicslib-master/LiberationSans-Regular.ttf";
const color white(255, 255, 255);
const color black(0, 0, 0);
const color green(0, 255, 0);
const color red(255, 0, 0);

class Torpedo : public Application {
    int _status;
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
public:
    Torpedo() : Application(genv::color(255, 255, 255), 1000, 550), _status(0) {
        gout.open(_window_width, _window_height);
        gout.load_font(fontFileName, 20);
        string tmpname;

        // welcome window
        {
        tmpname = "Start Placing Ships";
        beginning = new Button(this, _window_width / 2 - gout.twidth(tmpname) / 2, _window_height / 2,
                               gout.twidth(tmpname) + 10,gout.cascent() + gout.cdescent() + 10, tmpname,
                               [=](){ this->_status = 1;}, fontFileName, 20, green, white);

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
                this->_status = 2;
            } else {
                plr1t->changeSign(true);
            }
        }, fontFileName, 15, green, white);
        vector<Widget*> v2menu = {plr1t, plr1, plr1ok};
        _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, v2menu,
                                       [=](){
            gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height);
        }, [=](){
            if (plr1->getText() != "") {
                plr1t->changeSign(false);
            }
        }));
        }
        // play window
        {
        _menus.push_back(new PlayField(this, 0, 0, _window_width, _window_height, vector<Widget*>(),
                [=](){
                    gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height)
                         << move_to(10, 100) << color(0, 255, 0) << box(400, 400);
            }, [](){}));
        }

        _menus[0]->print(true);
        gout << refresh;
    }
    void action(genv::event ev) override {
        _menus[_status]->handle(ev);
    }
};

int main() {
    Torpedo torpedo;
    torpedo.event_loop();
    return 0;
}
