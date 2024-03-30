#include <iostream>

void f() {
    throw 1;
}

struct A{
    A(){};
    A(const A&) {
        std::cout << "copy A\n";
    }
};
struct B : public A {
    B(){};
    B(const B&){
        std::cout << "copy?";
    }
};

void g(){
    throw B();
}

int main() {
    try {
        f();
    } catch(double x) {
        std::cout << "caught double" << std::endl;
    } catch(long long x) {
        std::cout << "caught ll" << std::endl;
    } catch(unsigned int x) {
        std::cout << "caught unsigned int" << std::endl;
    } catch(int x) {
        std::cout << "caught int" << std::endl;
    }

    try{
        g();
    } catch (A a ) {  // lvalue
        std::cout << "caught what" << std::endl;
        // throw a & throw --- что полетит в зависимости от варианта? (1. Родитель 2. Ребёнок)
        // если тут прокинем, то нижний catch не сработает
        // это не switch
        // но идут по порядку при проверке
    } catch (A& a ) {  // lvalue
        std::cout << "caught A" << std::endl;
    }
    return 0;
}
