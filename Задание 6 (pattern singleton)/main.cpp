#include <iostream>
#include <thread>

using namespace std;

class Boiler {
   private:
    bool empty = true, boiled = false;

    Boiler() {}
    Boiler(const Boiler&);
    Boiler& operator=(Boiler&);

   public:
    static Boiler& getBoiler() {
        static Boiler boiler;
        return boiler;
    }

    void fill() {
        if (isEmpty()) {
            empty = false;

            cout << "Заполнил нагреватель!" << endl;
        } else {
            cout << "Нагреватель полон!" << endl;
        }
    }

    void boil() {
        if (!isEmpty() && !isBoiled()) {
            boiled = true;
            cout << "Начал нагрев!" << endl;
        } else {
            cout << "Нагреватель пуст или уже нагрет!" << endl;
        }
    }

    void drain() {
        if (!isEmpty() && isBoiled()) {
            empty = true;
            cout << "Вылил содержимое!" << endl;
        } else {
            cout << "Нагреватель пуст или не нагрет!" << endl;
        }
    }

    bool isEmpty() { return empty; }
    bool isBoiled() { return boiled; }
};

int main(int argc, char const* argv[]) {
    setlocale(0, "");

    Boiler& boiler1 = Boiler::getBoiler();
    Boiler& boiler2 = Boiler::getBoiler();

    cout << &boiler1 << endl;
    cout << &boiler2 << endl;

    boiler1.fill();
    boiler2.boil();
    boiler1.drain();
}
