#include <iostream>

struct S {
    S() {};

    S(const S&) {
        std::cout << "copy" << std::endl;
    }

    ~S() {
        std::cout << "destruct" << std::endl;
    }
};

void f() {
    S s;
    throw s;
}
/*  1
int main() {
    try{
        f();
    } catch(S s) {  // &
        std::cout << "caught\n";
    }
    return 0;
}
*/

void g() {
    try{
        f();
    } catch(S &s) {  // &
        std::cout << "caught\n";
        throw s; // throw
    }
}

int main() {
    try{
        g();
    } catch (S & s) {
        std::cout <<  "caught in main\n";
    }

    return 0;
}
