#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::string;

template <class T>
class ListNode {
public:
    ListNode() = default;
    explicit ListNode(T value) {
        this->prev = nullptr;
        this->value = value;
        this->next = nullptr;
    }
    ListNode(ListNode* prev, T value, ListNode* next) {
        this->prev = prev;
        this->value = value;
        this->next = next;
    }
    void setNext(ListNode* _next) {
        this->next = _next;
    }
    void setPrev(ListNode* _prev) {
        this->prev = _prev;
    }
    void setValue(T _value) {
        this->value = _value;
    }
    ListNode* getNext() {
        return this->next;
    }
    ListNode* getPrev() {
        return this->prev;
    }
    T getValue() {
        return this->value;
    }
private:
    T value;
    ListNode* prev;
    ListNode* next;
};

template <class T>
class GoblinPriorityQueue {
public:
    GoblinPriorityQueue() {
        head = nullptr;
        middle = nullptr;
        tail = nullptr;
        size = 0;
    }
    void pushBack(T value) {
        if (size == 0) {
            // Инициализируем список
            init(value);
        } else {
            // Вставляем новый элемент между tail->getPrev() и tail
            insertNode(value, tail->getPrev(), tail);
        }
    }
    void insertMiddle(T value) {
        if (size == 0) {
            // Инициализируем список
            init(value);
        } else {
            // Вставляем новый элемент между  middle и middle->getNext()
            insertNode(value, middle, middle->getNext());
        }
    }
    T popFront() {
        return removeNode(head->getNext());
    }
    void print() {
        cout << "Queue: ";
        ListNode<T>* current = head->getNext();
        while (current != tail) {
            cout << current->getValue() << " ";
            current = current->getNext();
        }
        cout << "\n";
    }
private:
    size_t size;

    ListNode<T>* head;
    ListNode<T>* middle;
    ListNode<T>* tail;


    void init(T value) {
        // head нужен, чтобы указывать на начало списка, сам ничего не содержит
        // tail нужен, чтобы указывать на конец списка, сам ничего не содержит
        // middle нужен, чтобы указывать на центр списка, сам ничего не содержит

        ListNode<T>* listNode = new ListNode<T>(value);
        size = 1;

        // В общем случае
        // head <-> 1 <-> 2 <-> ... <-> middle <-> ... <-> n - 1 <-> n <-> tail
        head = new ListNode<T>(nullptr, -128, listNode);
        middle = listNode;
        tail = new ListNode<T>(listNode, 127, nullptr);

        // В данном случае
        // head -> 1 <- tail
        listNode->setPrev(head);
        listNode->setNext(tail);
    }

    // Создает новый элемент и вставляет его между prevNode и nextNode
    void insertNode(T value, ListNode<T>* prevNode, ListNode<T>* nextNode) {
        // Создаем новый элемент
        auto* newNode = new ListNode<T>(value);

        // Указываем друг на друга prevNode <-> newNode
        prevNode->setNext(newNode);
        newNode->setPrev(prevNode);

        // Указываем друг на друга newNode <-> nextNode
        newNode->setNext(nextNode);
        nextNode->setPrev(newNode);

        // Увеличиваем size на 1
        size++;

        // Смещаем указатель на центр, если это необходимо
        if (size % 2 == 1) {
            middle = middle->getNext();
        }
    }

    // Удаляет элемент по указателю на него и возвращает его значение
    T removeNode(ListNode<T>* node) {
        ListNode<T>* nodePrev = node->getPrev();
        ListNode<T>* nodeNext = node->getNext();

        // Удаляем указатели на данную ноду из соседей
        // Было: nodePrev <-> node <-> nodeNext
        // Стало: nodePrev <-> nodeNext
        if (nodePrev != nullptr) {
            nodePrev->setNext(nodeNext);
        }
        if (nodeNext != nullptr) {
            nodeNext->setPrev(nodePrev);
        }

        // Уменьшаем size на 1
        size--;

        // Смещаем указатель на центр, если необходимо
        if (size % 2 == 1) {
            if (middle->getNext() != tail) {
                middle = middle->getNext();
            }
        }

        // Запоминаем значение ноды и удаляем ее из памяти
        T nodeValue = node->getValue();
        delete node;

        // Возвращаем значение этой ноды
        return nodeValue;
    }
};

int main() {
    // Ввод данных
    int requestsCount;
    cin >> requestsCount;

    // Создание структуры приоритетной гоблинской очереди
    GoblinPriorityQueue<int> q = GoblinPriorityQueue<int>();
    char requestType;
    int goblinID;

    // Цикл ввода данных и совершения операций с очередью
    for (int i = 0; i < requestsCount; i++) {
        cin >> requestType;
        if (requestType == '-') {
            int value = q.popFront();
            cout << value << "\n";
        } else {
            cin >> goblinID;
            if (requestType == '+') {
                q.pushBack(goblinID);
            } else if (requestType == '*') {
                q.insertMiddle(goblinID);
            }
        }
    }
}

//int main() {
//    // Testing
//    GoblinPriorityQueue<int> q = GoblinPriorityQueue<int>();
//    char requestType;
//    int goblinID;
//    while (true) {
//        cin >> requestType;
//        if (requestType == '-') {
//            int value = q.popFront();
//            cout << value << "\n";
//        } else {
//            if (requestType == '=') {
//                break;
//            }
//            cin >> goblinID;
//            if (requestType == '+') {
//                q.pushBack(goblinID);
//            } else if (requestType == '*') {
//                q.insertMiddle(goblinID);
//            }
//        }
//        q.print();
//    }
//}

// Regular test
//14
//* 1
//* 2
//* 3
//+ 4
//+ 5
//-
//* 6
//-
//* 7
//-
//-
//-
//-
//-
