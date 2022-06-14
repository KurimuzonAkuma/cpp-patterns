#include <iostream>

using namespace std;

class IFlyBehavior {
    public:
        virtual ~IFlyBehavior() {}
        virtual void fly() = 0;
};

class FlyWithWings : public IFlyBehavior {
    public:
        void fly() override {
            cout << "Лечу!" << endl;
        }
};

class FlyNoWay : public IFlyBehavior {
    public:
        void fly() override {}
};

class IQuackBehavior {
    public:
        virtual ~IQuackBehavior() {}
        virtual void quack() = 0;
};

class Quack : public IQuackBehavior {
    public:
        void quack() override {
            cout << "Кря!" << endl;
        }
};

class Squeak : public IQuackBehavior {
    public:
        void quack() override {
            cout << "Квя-квя!" << endl;
        }
};

class MuteQuack : public IQuackBehavior {
    public:
        void quack() override {}
};

class Duck : public IFlyBehavior, IQuackBehavior {
    public:
        FlyWithWings *fly_behavior;
        Quack *quack_behavior;
        Duck() {
            fly_behavior = new FlyWithWings();
            quack_behavior = new Quack();
        }
        ~Duck() {
            delete fly_behavior;
            delete quack_behavior;
        }

        void swim() {
            cout << "Плыву!" << endl;
        }

        virtual void display() = 0;

        void quack() override {
            quack_behavior->quack();
        }

        void fly() override {
            fly_behavior->fly();
        }
};

class MallardDuck : public Duck {
    public:
        MallardDuck() {
            quack_behavior = new Quack();
            fly_behavior = new FlyWithWings();
        }
        ~MallardDuck() {
            delete quack_behavior;
            delete fly_behavior;
        }

        void display() override {
            cout << "Кряква!" << endl;
        }
};

class RedheadDuck : public Duck {
    public:
        void display() override {
            cout << "Красноголовая утка!" << endl;
        }
};

class DecoyDuck : public Duck {
    public:
        MuteQuack *quack_behavior;
        FlyNoWay *fly_behavior;
        DecoyDuck() {
            quack_behavior = new MuteQuack();
            fly_behavior = new FlyNoWay();
        }
        ~DecoyDuck() {
            delete quack_behavior;
            delete fly_behavior;
        }
        void display() override {
            cout << "Деревянная утка!" << endl;
        }
        void quack() override {
            quack_behavior->quack();
        }
        void fly() override {
            fly_behavior->fly();
        }
};

class RubberDuck : public Duck {
    public:
        Squeak *quack_behavior;
        FlyNoWay *fly_behavior;
        RubberDuck() {
            quack_behavior = new Squeak();
            fly_behavior = new FlyNoWay();
        }
        ~RubberDuck() {
            delete quack_behavior;
            delete fly_behavior;
        }
        void display() override {
            cout << "Резиновая утка!" << endl;
        }
        void quack() override {
            quack_behavior->quack();
        }
        void fly() override {
            fly_behavior->fly();
        }
};

int main(int argc, char const* argv[]) {
    setlocale(0, "");

    Duck *rd = new RubberDuck;
    rd->display();
    rd->quack();
    rd->fly();
    rd->swim();

    cout << endl;

    Duck *rhd = new RedheadDuck;
    rhd->display();
    rhd->quack();
    rhd->fly();
    rhd->swim();

    cout << endl;

    Duck *dd = new DecoyDuck;
    dd->display();
    dd->quack();
    dd->fly();
    dd->swim();
    return 0;
}
