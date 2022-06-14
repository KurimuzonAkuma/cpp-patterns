#include <iostream>

using namespace std;

class Pizza {
   private:
    string name, pieces_shape, topping;

   public:
    virtual void prepare() { cout << "Подготавливаем все необходимые ингридиенты: " << get_topping() << endl; };
    virtual void bake() { cout << "Выпекаем пиццу" << endl; };
    virtual void cut() { cout << "Нарезаем пиццу на кусочки. Форма кусков: " << get_pieces_shape() << endl; };
    virtual void box() { cout << "Упаковываем пиццу!" << endl; };

    Pizza(string name, string pieces_shape, string topping) {
        this->name = name;
        this->pieces_shape = pieces_shape;
        this->topping = topping;
    }

    string get_name() { return name; }

    string get_topping() { return topping; }

    string get_pieces_shape() { return pieces_shape; }
};

class ChicagoStyleCheesePizza : public Pizza {
   public:
    ChicagoStyleCheesePizza() : Pizza(
                                    "Чикагская сырная пицца",
                                    "Треугольник",
                                    "толстое тесто, чеснок, репчатый лук, копченая грудинка, сыр моцарелла, базилик") {}
};

class ChicagoStylePepperoniPizza : public Pizza {
   public:
    ChicagoStylePepperoniPizza() : Pizza("Чикагская пицца с пепперони", "Треугольник",
                                         "толстое тесто, томатная паста, помидор, красный лук, сыр моцарелла, пепперони") {}
};

class NYStyleCheesePizza : public Pizza {
   public:
    NYStyleCheesePizza() : Pizza("Нью Йоркская сырная пицца", "Квадрат",
                                 "тонкое тесто, протернтые томаты, базилик, пармезан, моцарелла, лук, чеснок") {}
};

class NYStylePepperoniPizza : public Pizza {
   public:
    NYStylePepperoniPizza() : Pizza("Нью Йоркская пицца с пепперони", "Квадрат",
                                    "тонкое тесто, соленый огурец, пармезан, помидоры, пепперони, маслины, томатная паста") {}
};

class PizzaStore {
   public:
    virtual Pizza* createPizza(string type) = 0;
    Pizza* orderPizza(string type) {
        Pizza* pizza = createPizza(type);
        if (!pizza) {
            cout << "К сожалению у нас нет такой пиццы!" << endl;
            return 0;
        }

        cout << "Готовим пиццу: " << pizza->get_name() << endl;
        pizza->prepare();
        pizza->bake();
        pizza->cut();
        pizza->box();

        cout << endl;

        return pizza;
    }
};

class NYPizzaStore : public PizzaStore {
    Pizza* createPizza(string item) {
        if (item == "cheese") {
            return new NYStyleCheesePizza();
        } else if (item == "pepperoni") {
            return new NYStylePepperoniPizza();
        }

        return 0;
    }
};

class ChicagoPizzaStore : public PizzaStore {
    Pizza* createPizza(string item) {
        if (item == "cheese") {
            return new ChicagoStyleCheesePizza();
        } else if (item == "pepperoni") {
            return new ChicagoStylePepperoniPizza();
        }

        return 0;
    }
};

int main(int argc, char const* argv[]) {
    setlocale(0, "");

    PizzaStore* nyStore = new NYPizzaStore();
    PizzaStore* chicagoStore = new ChicagoPizzaStore();
    Pizza* pizza = nyStore->orderPizza("cheese");
    pizza = chicagoStore->orderPizza("cheese");
    pizza = nyStore->orderPizza("pepperoni");
    pizza = chicagoStore->orderPizza("pepperoni");

    pizza = chicagoStore->orderPizza("somepizza");
    return 0;
}
