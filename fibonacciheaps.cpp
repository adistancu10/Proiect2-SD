#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int value;
    int degree;
    Node* parent;
    Node* child;
    Node* left;
    Node* right;
    bool mark;

    Node(int value) {
        this->value = value;
        degree = 0;
        parent = nullptr;
        child = nullptr;
        left = this;
        right = this;
        mark = false;
    }
};

class FibonacciHeap {
    private:
        Node* minNode;
        int size;

        void consolidate() {
            vector<Node*> Table(size, nullptr);
            Node* current = minNode;
            int numRoots = 0;
            while (numRoots < size) {
                Node* next = current->right;
                int degree = current->degree;
                while (Table[degree] != nullptr) {
                    Node* other = Table[degree];
                    if (current->value > other->value) {
                        swap(current, other);
                    }
                    link(other, current);
                    Table[degree] = nullptr;
                    degree++;
                }
                Table[degree] = current;
                current = next;
                numRoots++;
            }

            minNode = nullptr;
            for (int i = 0; i < size; i++) {
                if (Table[i] != nullptr) {
                    if (minNode == nullptr) {
                        minNode = Table[i];
                    }
                    else {
                        link(Table[i], minNode);
                        if (Table[i]->value < minNode->value) {
                            minNode = Table[i];
                        }
                    }
                }
            }
        }

        void link(Node* child, Node* parent) {
            child->left->right = child->right;
            child->right->left = child->left;

            child->parent = parent;

            if (parent->child == nullptr) {
                parent->child = child;
                child->left = child;
                child->right = child;
            }
            else {
                child->left = parent->child;
                child->right = parent->child->right;
                parent->child->right = child;
                child->right->left = child;
            }

            parent->degree++;
            child->mark = false;
        }

    public:
        FibonacciHeap() {
            minNode = nullptr;
            size = 0;
        }

        bool isEmpty() {
            return size == 0;
        }

        int getSize() {
            return size;
        }

        void insert(int value) {
            Node* newNode = new Node(value);
            if (minNode == nullptr) {
                minNode = newNode;
            }
            else {
                link(newNode, minNode);
                if (newNode->value < minNode->value) {
                    minNode = newNode;
                }
            }
            size++;
        }

        int getMin() {
            return minNode->value;
        }

        int extractMin()
        {
            Node* z = minNode;
            int minValue = z->value;

            if (z->child != nullptr) {
                Node* child = z->child;
                do {
                    Node* next = child->right;
                    link(child, minNode);
                    child = next;
                } while (child != z->child);
            }

            z->left->right = z->right;
            z->right->left = z->left;

            if (z == z->right)
                minNode = nullptr;
            else
            {
            minNode = z->right;
            consolidate();
            }

        size--;
        delete z;

        return minValue;
            }


    void printTree(Node* node) {
    cout << node->value << " ";
    if (node->child != nullptr) {
        Node* child = node->child;
        do {
            printTree(child);
            child = child->right;
        } while (child != node->child);
    }
}

void printHeap() {
    if (minNode == nullptr) {
        cout << "Heap-ul este gol!" << endl;
        return;
    }

    cout << "Elementele din heap sunt: ";
    Node* current = minNode;
    do {
        printTree(current);
        current = current->right;
    } while (current != minNode);

    while(current != minNode)
    {
        printTree(current);
        current = current->right;
    }
    cout << endl;
}
};

int main()
{
    FibonacciHeap heap;
    heap.insert(5);
    heap.insert(3);
    heap.insert(7);
    heap.insert(1);
    heap.insert(8);
    heap.insert(9);
    heap.insert(10);
    heap.insert(11);
    heap.insert(12);

    heap.printHeap();

    int min = heap.extractMin();
    cout << "Minimul din heap este: " << min << endl;

    cout<<"Nr de elemente este : "<<heap.getSize();

    return 0;
}
