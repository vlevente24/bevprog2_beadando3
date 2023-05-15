#include "application.hpp"

using namespace genv;
using namespace std;

class Torpedo : public Application {

public:
    Torpedo() : Application(genv::color(255, 255, 255), 1000, 700) {
        gout.open(_window_width, _window_height);
        printBackground();
        gout << genv::refresh;
    }
    void action(std::string) override {}
    void printBackground() {
        gout << move_to(0, 0) << _bckgrnd_clr << box(_window_width, _window_height)
             << move_to(10, 10) << color(0, 0, 0) << box(_window_width - 20, _window_height - 20);
    }
};

int main() {
    Torpedo torpedo;
    torpedo.event_loop();
    return 0;
}
