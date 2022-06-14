#include <ctime>
#include <iostream>
#include <list>

using namespace std;

class Man;
class Department;
class Employee;
class IdCard;
class Room;
class PastPosition;

class Man {
   protected:
    string name;
    string surname;

   public:
    string getName() {
        return name;
    }

    string getSurname() {
        return surname;
    }

    void SetName(string newName) {
        name = newName;
    }

    void SetSurname(string newSurname) {
        surname = newSurname;
    }
};

class IdCard {
   private:
    time_t dateExpire;
    int number;

   public:
    IdCard(int n) {
        number = n;
    }
    bool operator==(const IdCard& obj) const {
        return number == obj.number;
    }
    void setNumber(int newNumber) {
        number = newNumber;
    }
    int getNumber() {
        return number;
    }
    void setDateExpire(time_t newDate) {
        dateExpire = newDate;
    }
    time_t getDateExpire() {
        return dateExpire;
    }
};

class Room {
   private:
    int number;

   public:
    Room(int n) {
        number = n;
    }
    bool operator==(const Room& obj) const {
        return number == obj.number;
    }
    void setNumber(int newNumber) {
        number = newNumber;
    }
    int getNumber() {
        return number;
    }
};

class PastPosition {
   private:
    string name;
    Department* department;

   public:
    PastPosition(string position, Department* dep) {
        name = position;
        department = dep;
    }
    ~PastPosition() {
        // cout << "\033[31mPastPosition destructor\033[0m" << endl;
    }
    bool operator==(const PastPosition& obj) const {
        return name == obj.name;
    }
    void setName(string newName) {
        name = newName;
    }
    string getName() {
        return name;
    }
    void setDepartment(Department* d) {
        department = d;
    }
    Department* getDepartment() {
        return department;
    }
};

class Employee : public Man {
   private:
    string position;
    IdCard iCard = 0;
    list<Room*> room;
    Department* department;
    list<PastPosition*> pastPosition;

   public:
    Employee(string n, string s, string p) {
        name = n;
        surname = s;
        position = p;
    };
    ~Employee() {
        // cout << "\033[31m" << name << " | " << position << " Employee destructor\033[0m" << endl;
        for (auto& element : pastPosition) delete element;
        for (auto& element : room) delete element;
    }
    bool operator==(const Employee& obj) const {
        if (iCard == obj.iCard) {
            return true;
        } else {
            return false;
        }
    }
    void setPosition(string newProfession) {
        PastPosition* pastPosition = new PastPosition(getPosition(), getDepartment());
        setPastPosition(pastPosition);
        position = newProfession;
    }
    string getPosition() {
        return position;
    }
    void setIdCard(IdCard c) {
        iCard = c;
    }
    IdCard getIdCard() {
        return iCard;
    }
    void setRoom(Room* newRoom) {
        room.push_back(newRoom);
    }
    list<Room*> getRoom() {
        return room;
    }
    void deleteRoom(Room* r) {
        room.remove(r);
    }
    void setDepartment(Department* d) {
        department = d;
    }
    Department* getDepartment() {
        return department;
    }
    void setPastPosition(PastPosition* p) {
        pastPosition.push_back(p);
    }
    list<PastPosition*> getPastPosition() {
        return pastPosition;
    }
    void deletePastPosition(PastPosition* p) {
        pastPosition.remove(p);
    }
};

class Unit {
   public:
    virtual ~Unit() {}
    virtual int getPersonCount() = 0;
};

class Department : public virtual Unit {
   private:
    string name;
    list<Employee*> employees;

   public:
    Department(string n) {
        name = n;
    }
    void setName(string newName) {
        name = newName;
    }
    string getName() {
        return name;
    }
    void addEmployee(Employee* newEmployee) {
        employees.push_back(newEmployee);
        newEmployee->setDepartment(this);
    }
    list<Employee*> getEmployees() {
        return employees;
    }
    void removeEmployee(Employee* e) {
        employees.remove(e);
    }
    int getPersonCount() {
        return getEmployees().size();
    }
};

class Menu {
   private:
    int i = 0;

   public:
    void showEmployees(list<Employee*> employees) {
        cout << "Список сотрудников: " << endl;
        for (auto& element : employees) cout << element->getName() << " - " << element->getPosition() << endl;
    }
};

int main(int argc, char const* argv[]) {
    setlocale(0, "");

    Employee sysEngineer = Employee("Жора", "Кустов", "Управделами");
    sysEngineer.setPosition("Инженер");

    Employee director = Employee("Федор", "Дубов", "Директор");

    IdCard card = IdCard(123);
    card.setDateExpire(1451509200);
    sysEngineer.setIdCard(card);

    Room room101 = Room(101);
    Room room321 = Room(321);
    sysEngineer.setRoom(&room101);
    sysEngineer.setRoom(&room321);

    Department programmersDepartment = Department("Программисты");
    programmersDepartment.addEmployee(&sysEngineer);

    sysEngineer.setPosition("Сторож");

    cout << sysEngineer.getName() << " работает в должности " << sysEngineer.getPosition() << endl;

    char buf[100];
    time_t date = sysEngineer.getIdCard().getDateExpire();
    struct tm* p = localtime(&date);
    strftime(buf, 100, "%Y-%m-%d", p);

    cout << "Удостоверение действительно до " << buf << endl;
    cout << "Может находиться в помещениях: ";

    for (auto& element : sysEngineer.getRoom()) cout << (*element).getNumber() << " ";
    cout << endl;

    cout << "Относится к отделу: " << sysEngineer.getDepartment()->getName() << endl;

    cout << "В отделе "
         << sysEngineer.getDepartment()->getName()
         << " работает "
         << sysEngineer.getDepartment()->getPersonCount()
         << " человек."
         << endl;

    cout << "В прошлом работал как: ";
    for (auto& pastpos : sysEngineer.getPastPosition()) cout << pastpos->getName() << " ";
    cout << endl;

    Menu menu = Menu();
    list<Employee*> employees;
    employees.push_back(&sysEngineer);
    employees.push_back(&director);
    menu.showEmployees(employees);
    return 0;
}
