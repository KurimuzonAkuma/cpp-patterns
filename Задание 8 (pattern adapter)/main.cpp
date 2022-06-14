#include <iostream>

using namespace std;

class Duck {
   public:
    virtual void quack(){};
    virtual void fly(){};
};

class MallardDuck : public Duck {
   public:
    void quack() { cout << "Quack" << endl; }
    void fly() { cout << "I'm flying" << endl; }
};

class Turkey {
   public:
    virtual void gobble(){};
    virtual void fly(){};
};

class WildTurkey : public Turkey {
   public:
    void gobble() { cout << "Gobble gobble" << endl; }
    void fly() { cout << "I'm flying a short distance" << endl; }
};

class TurkeyAdapter : public Duck {
   private:
    Turkey *turkey;

   public:
    TurkeyAdapter(Turkey *turkey) { this->turkey = turkey; }
    void quack() { turkey->gobble(); }
    void fly() {
        for (int i = 0; i < 5; i++) turkey->fly();
    }
};

class TurkeyAdapterClass : public Duck, private WildTurkey {
   public:
    TurkeyAdapterClass() {}
    void quack() { WildTurkey::gobble(); }
    void fly() {
        for (int i = 0; i < 5; i++) WildTurkey::fly();
    }
};

int main(int argc, char const* argv[]) {
    Duck *duck = new MallardDuck;
    Turkey *turkey = new WildTurkey;
    Duck *turkeyAdapter = new TurkeyAdapter(turkey);
    cout << "The Turkey says..." << endl;
    turkey->gobble();
    turkey->fly();
    cout << endl
         << "The Duck says..." << endl;
    duck->fly();
    duck->quack();
    cout << endl
         << "The TurkeyAdapter says..." << endl;
    turkeyAdapter->fly();
    turkeyAdapter->quack();

    cout << endl
         << "The turkeyAdapterClass says..." << endl;
    Duck *turkeyAdapterClass = new TurkeyAdapterClass;
    turkeyAdapterClass->fly();
    turkeyAdapterClass->quack();
}
