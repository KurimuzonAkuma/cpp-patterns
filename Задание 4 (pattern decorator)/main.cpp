#include <iostream>

using namespace std;

class Beverage {
   public:
    string description = "Неизвестный напиток";

    virtual string getDescription() { return description; }
    virtual double cost() = 0;
};

class DarkRoast : public Beverage {
   public:
    DarkRoast() { description = "Обжаренный кофе"; }
    double cost() { return 150; }
};

class HouseBlend : public Beverage {
   public:
    HouseBlend() { description = "ХаусБлэнд кофе"; }
    double cost() { return 160; }
};

class Decaf : public Beverage {
   public:
    Decaf() { description = "Кофе без кофеина"; }
    double cost() { return 130; }
};

class Espresso : public Beverage {
   public:
    Espresso() { description = "Эспрессо"; }
    double cost() { return 120; }
};

class CondimentDecorator : public Beverage {
   public:
    Beverage* beverage;
    virtual string getDescription() = 0;
    virtual double cost() = 0;
};

class Milk : public CondimentDecorator {
   public:
    Milk(Beverage* beverage) {
        this->beverage = beverage;
    }

    string getDescription() {
        return beverage->getDescription() + " с молоком";
    }
    double cost() {
        return 15 + beverage->cost();
    }
};

class Mocha : public CondimentDecorator {
   public:
    Mocha(Beverage* beverage) {
        this->beverage = beverage;
    }

    string getDescription() {
        return beverage->getDescription() + " с мокко";
    }
    double cost() {
        return 25 + beverage->cost();
    }
};

class Whip : public CondimentDecorator {
   public:
    Whip(Beverage* beverage) {
        this->beverage = beverage;
    }

    string getDescription() {
        return beverage->getDescription() + " со сливками";
    }
    double cost() {
        return 30 + beverage->cost();
    }
};

int main(int argc, char const* argv[]) {
    setlocale(0, "");
    Beverage* beverage2 = new DarkRoast();
    beverage2 = new Mocha(beverage2);
    beverage2 = new Mocha(beverage2);
    beverage2 = new Whip(beverage2);

    cout << beverage2->getDescription() << ": " << beverage2->cost() << "руб." << endl;
    return 0;
}
