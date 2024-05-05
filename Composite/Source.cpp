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
    Component* root = new Composite("����");

    Composite* reception = new Composite("��������");
    reception->Add(new Leaf("������ ���� ��������� � ������ �����", 500));
    Composite* journalTable = new Composite("���������� ������");
    journalTable->Add(new Leaf("10-20 �������� ���� ������������� ���", 200));
    reception->Add(journalTable);

    reception->Add(new Leaf("������ �����", 1000));
    Composite* secretaryDesk = new Composite("���� ���������");

    Composite* computer = new Composite("���������");
    computer->Add(new Leaf("����� ������� �������� ������ �������� �����", 1500));
    secretaryDesk->Add(computer);

    secretaryDesk->Add(new Leaf("������� ��������������", 300));
    reception->Add(secretaryDesk);
    reception->Add(new Leaf("����� � ������ � �������� �����", 700));
    root->Add(reception);

    Composite* classroom1 = new Composite("��������� 1");
    classroom1->Add(new Leaf("10 ������", 1000));

    classroom1->Add(new Leaf("�����", 300));
    Composite* teacherDesk1 = new Composite("���� �������");
    teacherDesk1->Add(new Leaf("���������", 2000));

    classroom1->Add(teacherDesk1);
    classroom1->Add(new Leaf("������� ������� �����������", 100));
    root->Add(classroom1);

    Composite* classroom2 = new Composite("��������� 2");
    classroom2->Add(new Leaf("20 ������", 2000));

    Composite* blackTables = new Composite("����� ������� �����");
    blackTables->Add(new Leaf("����� ���������� � ���� ��� ����", 1500));
    classroom2->Add(blackTables);

    classroom2->Add(new Leaf("�����", 300));
    classroom2->Add(new Leaf("������ �����", 1000));
    root->Add(classroom2);

    Composite* computerRoom = new Composite("������������ ���������");
    computerRoom->Add(new Leaf("10 ������������ ������", 5000));

    Composite* computers = new Composite("��������� �� ������ �����");

    computers->Add(new Leaf("��������� 2.2���", 3000));
    computers->Add(new Leaf("��������� �� 80��", 1000));
    computers->Add(new Leaf("����������� ������ 1024��", 1500));
    computerRoom->Add(computers);

    computerRoom->Add(new Leaf("������� ����� ������� �����", 200));
    computerRoom->Add(new Leaf("�����", 300));
    computerRoom->Add(new Leaf("����� ������������ ��������", 50));
    root->Add(computerRoom);

    Composite* diningRoom = new Composite("��������");
    diningRoom->Add(new Leaf("�������� �������", 700));

    Composite* table = new Composite("����");
    table->Add(new Leaf("4 �����", 200));

    diningRoom->Add(table);
    diningRoom->Add(new Leaf("�����������", 1000));
    diningRoom->Add(new Leaf("����������", 500));

    root->Add(diningRoom);

    root->Display(1);
    cout << "��������� ��������� ���� ��������� �����: $" << root->GetCost() << endl;

    delete root;
    system("pause");
    return 0;
}
