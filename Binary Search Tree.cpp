#include <iostream>
#include <stack>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
struct node {
    T item;
    node<T>* left = NULL;
    node<T>* right = NULL;
};

template <typename T>
class BST {
private:
    node<T>* head;
public:
    BST() {
        head = NULL;
    }

    ~BST() {
        // 중위 순회하면서 동적으로 할당한 모든 node들을 제거
        stack<node<T>*> s;
        node<T>* cur = head;

        while (cur != NULL || !s.empty()) {
            while (cur != NULL) {
                s.push(cur);
                cur = cur->left;
            }
            cur = s.top(); s.pop();
            node<T>* tmp = cur->right;
            delete cur;
            cur = tmp;
        }
    }

    void insert(T& item) {
        // 새로운 item 삽입
        if (head == NULL) { // head가 비어 있다면 새로 동적할당 후, 리턴
            head = new node<T>;
            head->item = item;
            return;
        }

        // head에서부터 item이 삽입될 위치 탐색
        // cur의 자식이 모두 NULL인 경우(=leaf 노드에 도달한 경우), 그 자식 중 한 곳에 item이 새로운 leaf노드로 추가되어야 함.
        node<T>* cur = head;
        while (true) {
            if (item < (cur->item)) {
                if (cur->left != NULL) cur = cur->left;
                else {
                    cur->left = new node<T>;
                    cur->left->item = item;
                    return;
                }
            }
            else {
                if (cur->right != NULL) cur = cur->right;
                else {
                    cur->right = new node<T>;
                    cur->right->item = item;
                    return;
                }
            }
        }
    }

    // 중위 순회 코드
    // 재귀적으로는 왼쪽서브트리순회 -> 자기자신 방문 -> 오른쪽서브트리순회
    // 이를 반복문으로 짜야하므로, 스택에 경로를 저장하면서 왼쪽자식으로 최대한 깊게 들어간 뒤,
    // 자기 자신 방문 후, 오른쪽 서브트리를 방문하는 식으로 구현
    void inorder() {
        stack<node<T>*> s;
        node<T>* cur = head;

        while (cur != NULL || !s.empty()) {
            // 최대한 왼쪽으로 이동
            while (cur != NULL) {
                s.push(cur);
                cur = cur->left;
            }

            // 자기 자신 노드 방문
            cur = s.top(); s.pop();
            cout << cur->item << " ";

            // 오른쪽 서브트리 방문
            // 자기 자신 노드가 위에서 이미 pop 되었으므로, 
            // 오른쪽 서브트리 순회 후에는 스택이 비어있거나 오른쪽 서브트리의 할아버지 노드로 올라가게 됨.
            cur = cur->right;
        }

        cout << "\n";
    }
};

int main() {
    string input;
    while (true) {
        getline(cin, input);
        if (input == ".") return 0;
        
        stringstream ss;
        ss.str(input);

        BST<int> tree;
        while (true) {
            int cur; ss >> cur;
            if (ss.fail()) break;
            tree.insert(cur);
        }

        tree.inorder();
    }
}

//2016125039 오상훈