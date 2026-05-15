using namespace std;
template<typename T>
struct LinkedList {
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int _size;
    LinkedList() : head(nullptr), tail(nullptr), _size(0) {}
    void clear() {
        if(!head) return;
        while(head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        _size = 0;
    }
    void insertFront(T val) {
        Node* tmp = new Node(val);
        if(!head) {
            head = tail = tmp;
        } else {
            tmp->next = head;
            head = tmp;
        }
        _size++;
    }
    void insertBack(T val) {
        Node* tmp = new Node(val);
        if(!head) {
            head = tail = tmp;
        } else {
            tail->next = tmp;
            tail = tmp;
        }
        _size++;
    }
    void remove(T val) {
        Node* tmp = head;
        if(!tmp) return;
        if(tmp->data == val) {
            head = tmp->next;
            if(!head) tail = nullptr;
            delete tmp;
            _size--;
            return;
        }
        while(tmp->next) {
            if(tmp->next->data == val) {
                Node* p = tmp->next;
                tmp->next = p->next;
                _size--;
                delete p;
                if(!tmp->next) tail = tmp;
            } else tmp = tmp->next;
        }
    }
    void removeAt(int index) {
        if(index < 0 || index >= _size) return;
        if(index == 0) {
            Node* tmp = head;
            head = head->next;
            if(!head) tail = nullptr;
            _size--;
            delete tmp;
            return;
        } 
        Node* p = head;
        for(int i = 0; i < index - 1; i++) {
            p = p->next;
        }
        Node* delNode = p->next;
        if(!delNode->next) {
            tail = p;
            delete delNode;
            _size--;
            return;
        }
        p->next = delNode->next;
        delete delNode;
        _size--;
        return;
    }
    bool find(T val) {
        Node* tmp = head;
        while(tmp) {
            if(tmp->data == val) return true;
            tmp = tmp->next;
        }
        return false;
    }
    int size() {
        return _size;
    }
};