//
// Created by Gianluca Pane on 5/15/21.
//

#ifndef CPP_Y_COMBINATOR_HPP
#define CPP_Y_COMBINATOR_HPP


#include <utility>
#include <functional>

using namespace std;

template<class Fun>
class y_combinator_result {
    Fun fun_;
public:
    template<class T>
    explicit y_combinator_result(T &&fun): fun_(forward<T>(fun)) {}

    template<class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(ref(*this), forward<Args>(args)...);
    }
};

template<class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<decay_t<Fun>>(forward<Fun>(fun));
}

#endif //CPP_Y_COMBINATOR_HPP
