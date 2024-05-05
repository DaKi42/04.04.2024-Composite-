#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Component {
protected:
    string name;
public:
    Component(string name) : name(name) {}

    virtual void Add(Component* c) {}
    virtual void Remove(Component* c) {}
    virtual void Display(int depth) = 0;
    virtual double GetCost() = 0;
    virtual ~Component() {}
};

class Composite : public Component {
    vector<Component*> components;
public:
    Composite(string name) : Component(name) {}

    void Add(Component* component) override {
        components.push_back(component);
    }
    void Remove(Component* component) override {
        auto iter = find(components.begin(), components.end(), component);
        if (iter != components.end())
            components.erase(iter);
    }
    void Display(int depth) override {
        string indentation(depth * 3, ' ');
        cout << indentation << name << endl;

        for (Component* component : components) {
            component->Display(depth + 1);
        }
    }
    double GetCost() override {
        double totalCost = 0.0;
        for (Component* component : components) {
            totalCost += component->GetCost();
        }
        return totalCost;
    }
    ~Composite() {
        for (Component* component : components) {
            delete component;
        }
    }
};

class Leaf : public Component {
    double cost;
public:
    Leaf(string name, double cost) : Component(name), cost(cost) {}

    void Display(int depth) override {
        string indentation(depth * 3, ' ');
        cout << indentation << name << endl;
    }
    double GetCost() override {
        return cost;
    }
};

int main() {
    setlocale(LC_ALL, "Ru");
    Component* root = new Composite("Офис");

    Composite* reception = new Composite("Приемная");
    reception->Add(new Leaf("Должна быть выполнена в теплых тонах", 500));
    Composite* journalTable = new Composite("Журнальный столик");
    journalTable->Add(new Leaf("10-20 журналов типа «компьютерный мир»", 200));
    reception->Add(journalTable);

    reception->Add(new Leaf("Мягкий диван", 1000));
    Composite* secretaryDesk = new Composite("Стол секретаря");

    Composite* computer = new Composite("Компьютер");
    computer->Add(new Leaf("Важно наличие большого объема жесткого диска", 1500));
    secretaryDesk->Add(computer);

    secretaryDesk->Add(new Leaf("Офисный инструментарий", 300));
    reception->Add(secretaryDesk);
    reception->Add(new Leaf("Кулер с теплой и холодной водой", 700));
    root->Add(reception);

    Composite* classroom1 = new Composite("Аудитория 1");
    classroom1->Add(new Leaf("10 столов", 1000));

    classroom1->Add(new Leaf("Доска", 300));
    Composite* teacherDesk1 = new Composite("Стол учителя");
    teacherDesk1->Add(new Leaf("Компьютер", 2000));

    classroom1->Add(teacherDesk1);
    classroom1->Add(new Leaf("Плакаты великих математиков", 100));
    root->Add(classroom1);

    Composite* classroom2 = new Composite("Аудитория 2");
    classroom2->Add(new Leaf("20 столов", 2000));

    Composite* blackTables = new Composite("Столы черного цвета");
    blackTables->Add(new Leaf("Столы выставлены в овал или круг", 1500));
    classroom2->Add(blackTables);

    classroom2->Add(new Leaf("Доска", 300));
    classroom2->Add(new Leaf("Мягкий диван", 1000));
    root->Add(classroom2);

    Composite* computerRoom = new Composite("Компьютерная аудитория");
    computerRoom->Add(new Leaf("10 компьютерных столов", 5000));

    Composite* computers = new Composite("Компьютер на каждом столе");

    computers->Add(new Leaf("Процессор 2.2ГРц", 3000));
    computers->Add(new Leaf("Винчестер на 80ГБ", 1000));
    computers->Add(new Leaf("Оперативная память 1024МБ", 1500));
    computerRoom->Add(computers);

    computerRoom->Add(new Leaf("Розетка возле каждого стола", 200));
    computerRoom->Add(new Leaf("Доска", 300));
    computerRoom->Add(new Leaf("Набор разноцветных маркеров", 50));
    root->Add(computerRoom);

    Composite* diningRoom = new Composite("Столовая");
    diningRoom->Add(new Leaf("Кофейный автомат", 700));

    Composite* table = new Composite("Стол");
    table->Add(new Leaf("4 стула", 200));

    diningRoom->Add(table);
    diningRoom->Add(new Leaf("Холодильник", 1000));
    diningRoom->Add(new Leaf("Умывальник", 500));

    root->Add(diningRoom);

    root->Display(1);
    cout << "Суммарная стоимость всех предметов офиса: $" << root->GetCost() << endl;

    delete root;
    system("pause");
    return 0;
}
