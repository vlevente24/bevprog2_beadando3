#ifndef LIST_HPP_INCLUDE
#define LIST_HPP_INCLUDE

#include "/Users/levente/Desktop/ITK_graphicslib-master/graphics.hpp"
#include "widgets.hpp"
#include <vector>
#include <string>

using namespace std;

class List : public Widget {
    vector<string> _sv;
    vector<genv::canvas*> _v;
    string _value;
    int _y_down_max, _y_down, _index, _shift, _valuei;
    void print_btn(bool) const;
    void print_box() const;
    int calc_index(int);
public:
    List(Application*, int x, int y, int w, int h, int max_y_down, vector<string> items);
    ~List();
    void print(bool) const override;
    void handle(genv::event) override;
    void reset() override;
    bool is_selected(int, int) override;
    string getValue() const;
    int getSelected() const;
    void update(vector<string> items);
};

#endif