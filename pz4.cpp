#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// Базовый класс T1
class T1 {
protected:
    string id; // Идентификатор объекта
    int state;  // Состояние объекта

public:
    T1(const string& id, int state) : id(id), state(state) {}

    // Вывод состояния объекта
    virtual void show() const {
        cout << "ID: " << id << ", State: " << state << endl;
    }

    // Изменение состояния объекта
    void setState(int newState) {
        state = newState;
    }

    virtual ~T1() = default; // Виртуальный деструктор
};

// Класс T2, наследник T1
class T2 : public T1 {
private:
    int additionalState; // Дополнительное состояние

public:
    T2(const string& id, int state, int additionalState)
        : T1(id, state), additionalState(additionalState) {}

    // Вывод состояния объекта (переопределение метода)
    void show() const override {
        cout << "ID: " << id << ", State: " << state
            << ", Additional State: " << additionalState << endl;
    }

    // Изменение дополнительного состояния
    void setAdditionalState(int newAdditionalState) {
        additionalState = newAdditionalState;
    }
};

// Класс Factory для управления объектами
class Factory {
private:
    vector<unique_ptr<T1>> objects; // Вектор для хранения объектов

public:
    // Создание объекта типа T1
    void createT1(const string& id, int state) {
        objects.push_back(make_unique<T1>(id, state));
        cout << "Created T1 object with ID: " << id << endl;
    }

    // Создание объекта типа T2
    void createT2(const string& id, int state, int additionalState) {
        objects.push_back(make_unique<T2>(id, state, additionalState));
        cout << "Created T2 object with ID: " << id << endl;
    }

    // Удаление объекта по ID
    void deleteObject(const string& id) {
        auto it = find_if(objects.begin(), objects.end(),
            [&id](const unique_ptr<T1>& obj) { return obj->getId() == id; });

        if (it != objects.end()) {
            cout << "Deleted object with ID: " << id << endl;
            objects.erase(it);
        }
        else {
            cout << "Object with ID " << id << " not found!" << endl;
        }
    }

    // Вывод всех объектов
    void showAllObjects() const {
        if (objects.empty()) {
            cout << "No objects found!" << endl;
        }
        else {
            for (const auto& obj : objects) {
                obj->show();
            }
        }
    }
};

// Функция для отображения меню
void showMenu() {
    cout << "\nMenu:\n"
        << "1. Create T1 object\n"
        << "2. Create T2 object\n"
        << "3. Delete object\n"
        << "4. Show all objects\n"
        << "5. Exit\n"
        << "Choose an option: ";
}

int main() {
    Factory factory;
    int choice;
    string id;
    int state, additionalState;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: // Создание объекта T1
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter state: ";
            cin >> state;
            factory.createT1(id, state);
            break;

        case 2: // Создание объекта T2
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter state: ";
            cin >> state;
            cout << "Enter additional state: ";
            cin >> additionalState;
            factory.createT2(id, state, additionalState);
            break;

        case 3: // Удаление объекта
            cout << "Enter ID to delete: ";
            cin >> id;
            factory.deleteObject(id);
            break;

        case 4: // Вывод всех объектов
            factory.showAllObjects();
            break;

        case 5: // Выход
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Try again." << endl;
            break;
        }
    }

    return 0;
}