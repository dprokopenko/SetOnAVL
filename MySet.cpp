#include <bits/stdc++.h>

template <typename T>
struct Node {
    Node<T>* left;
    Node<T>* right;
    T value;
    int height;
    int sizeTree;
    typename std::list<T>::const_iterator iteratorNode;
    Node(const T& valueInit)
        :
        left(nullptr),
        right(nullptr),
        value(valueInit),
        height(1),
        sizeTree(1) {
    }
};

template <typename T>
int heightTree(Node<T>* vertex) {
    if (vertex) {
        return vertex->height;
    } else {
        return 0;
    }
}

template <typename T>
int sizeTree(Node<T>* vertex) {
    if (vertex) {
        return vertex->sizeTree;
    } else {
        return 0;
    }
}

template <typename T>
int diffTree(Node<T>* vertex) {
    return heightTree(vertex->left) - heightTree(vertex->right);
}

template <typename T>
void updateHeight(Node<T>* vertex) {
    vertex->height = std::max(heightTree(vertex->left), heightTree(vertex->right)) + 1;
    vertex->sizeTree = sizeTree(vertex->left) + sizeTree(vertex->right) + 1;
}

template <typename T>
Node<T>* rotateRight(Node<T>* vertex) {
    Node<T>* tmp = vertex->left;
    vertex->left = tmp->right;
    tmp->right = vertex;
    updateHeight(vertex);
    updateHeight(tmp);
    return tmp;
}

template <typename T>
Node<T>* rotateLeft(Node<T>* vertex) {
    Node<T>* tmp = vertex->right;
    vertex->right = tmp->left;
    tmp->left = vertex;
    updateHeight(vertex);
    updateHeight(tmp);
    return tmp;
}

template <typename T>
Node<T>* balanceTree(Node<T>* vertex) {
    int diff = diffTree(vertex);
    if (diff == -2) {
        if (diffTree(vertex->right) <= 0) {
            return rotateLeft(vertex);
        } else {
            vertex->right = rotateRight(vertex->right);
            return rotateLeft(vertex);
        }
    } else if (diff == 2) {
        if (diffTree(vertex->left) >= 0) {
            return rotateRight(vertex);
        } else {
            vertex->left = rotateLeft(vertex->left);
            return rotateRight(vertex);
        }
    }
    updateHeight(vertex);
    return vertex;
}

template <typename T>
Node<T>* insertTree(Node<T>* root, const T& value, Node<T>* vertex) {
    if (!root) {
        return vertex;
    } else if (!(root->value < value) && !(value < root->value)) {
        return root;
    } else {
        if (value < root->value) {
            root->left = insertTree(root->left, value, vertex);
        } else {
            root->right = insertTree(root->right, value, vertex);
        }
        return balanceTree(root);
    }
}

template <typename T>
Node<T>* getMin(Node<T>* root) {
    if (!root->left) {
        return root;
    } else {
        return getMin(root->left);
    }
}

template <typename T>
Node<T>* eraseMin(Node<T>* root) {
    if (!root->left) {
        return root->right;
    } else {
        root->left = eraseMin(root->left);
        return balanceTree(root);
    }
}

template <typename T>
Node<T>* eraseTree(Node<T>* root, const T& value, std::list<T>* pointerList) {
    if (!root) {
        return nullptr;
    } else if (value < root->value) {
        root->left = eraseTree(root->left, value, pointerList);
        return balanceTree(root);
    } else if (root->value < value) {
        root->right = eraseTree(root->right, value, pointerList);
        return balanceTree(root);
    } else {
        pointerList->erase(root->iteratorNode);
        if (!root->right) {
            Node<T>* left = root->left;
            delete root;
            return left;
        }
        Node<T>* minRight = getMin(root->right);
        minRight->right = eraseMin(root->right);
        minRight->left = root->left;
        delete root;
        return balanceTree(minRight);
    }
}

template <typename T>
bool existTree(Node<T>* root, const T& value) {
    if (!root) {
        return false;
    } else if (!(root->value < value) && !(value < root->value)) {
        return true;
    } else if (value < root->value) {
        return existTree(root->left, value);
    } else {
        return existTree(root->right, value);
    }
}

template <typename T>
std::string checkTree(Node<T>* root) {
    if (!root) {
        return "Good!";
    } else {
        if (std::abs(diffTree(root)) > 1) {
            return "Bad!";
        }
        if (checkTree(root->left) == "Good!" && checkTree(root->right) == "Good!") {
            return "Good!";
        } else {
            return "Bad!";
        }
    }
}

template <typename T>
void deleteTree(Node<T>* root) {
    if (root) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

template <typename T>
typename std::list<T>::const_iterator lowerElement(Node<T>* root, const T& value, std::list<T>* pointerList) {
    if (!root) {
        return pointerList->end();
    } else if (!(root->value < value) && !(value < root->value)) {
        return root->iteratorNode;
    } else if (value < root->value) {
        typename std::list<T>::const_iterator iter = lowerElement(root->left, value, pointerList);
        if (iter == pointerList->end()) {
            return root->iteratorNode;
        } else {
            return iter;
        }
    } else {
        return lowerElement(root->right, value, pointerList);
    }
}

template <typename T>
typename std::list<T>::const_iterator findTree(Node<T>* root, const T& value, std::list<T>* pointerList) {
    typename std::list<T>::const_iterator iter = lowerElement(root, value, pointerList);
    if (iter == pointerList->end() || (!(*iter < value) && !(value < *iter))) {
        return iter;
    } else {
        return pointerList->end();
    }
}

template <typename T>
Node<T>* insertTree(Node<T>* root, const T& value, std::list<T>* pointerList) {
    typename std::list<T>::const_iterator iter = lowerElement(root, value, pointerList);
    if (iter != pointerList->end() && (!(*iter < value) && !(value < *iter))) {
        return root;
    } else {
        Node<T>* vertex = new Node<T>(value);
        vertex->iteratorNode = pointerList->insert(iter, value);
        return insertTree(root, value, vertex);
    }
}

template <typename T>
Node<T>* CopyTree(Node<T>* root) {
    if (!root) {
        return root;
    } else {
        Node<T>* newRoot = new Node<T>(root->value);
        newRoot->left = CopyTree(root->left);
        newRoot->right = CopyTree(root->right);
        updateHeight(newRoot);
        return newRoot;
    }
}

template <typename T>
std::list<T>* CopyList(std::list<T>* List) {
    std::list<T>* newList = new std::list<T>();
    for (auto& value : *List) {
        newList->push_back(value);
    }
    return newList;
}

template <typename T>
typename std::list<T>::const_iterator RankTree(Node<T>* root, std::list<T>* List, typename std::list<T>::const_iterator iterDest) {
    if (!root) {
        return List->end();
    } else {
        typename std::list<T>::const_iterator iter = RankTree(root->left, List, iterDest);
        if (iter == List->end()) {
            if (iterDest == List->end()) {
                iter = List->begin();
            } else {
                iter = ++iterDest;
            }
        } else {
            ++iter;
        }
        root->iteratorNode = iter;
        if (!root->right) {
            return iter;
        } else {
            return RankTree(root->right, List, iter);
        }
    }
}

template <typename T>
class Set {
private:
    Node<T>* root;
    std::list<T>* elemList;
public:
    Set()
        :
        root(nullptr),
        elemList(new std::list<T>()) {
    }
    template <typename Iterator>
    Set(Iterator First, Iterator Last) : root(nullptr), elemList(new std::list<T>()) {
        while (First != Last) {
            root = insertTree(root, *First, elemList);
            ++First;
        }
    }
    Set(std::initializer_list<T> elems) : root(nullptr), elemList(new std::list<T>()) {
        for (auto& item : elems) {
            root = insertTree(root, item, elemList);
        }
    }
    ~Set() {
        deleteTree(root);
        delete elemList;
    }
    void insert(const T& value) {
        root = insertTree(root, value, elemList);
    }
    void erase(const T& value) {
        root = eraseTree(root, value, elemList);
    }
    bool exist(const T& value) const {
        return existTree(root, value);
    }
    bool empty() const {
        if (!root) {
            return true;
        } else {
            return false;
        }
    }
    int size() const {
        return sizeTree(root);
    }
    typename std::list<T>::const_iterator lower_bound(const T& value) const {
        return lowerElement(root, value, elemList);
    }
    typename std::list<T>::const_iterator find(const T& value) const {
        return findTree(root, value, elemList);
    }
    typename std::list<T>::const_iterator begin() const {
        return elemList->begin();
    }
    typename std::list<T>::const_iterator end() const {
        return elemList->end();
    }
    Set(const Set& other) {
        root = CopyTree(other.root);
        elemList = CopyList(other.elemList);
        RankTree(root, elemList, elemList->end());
    }
    Set& operator=(const Set& other) {
        if (this == &other) {
            return *this;
        } else {
            deleteTree(root);
            delete elemList;
            root = CopyTree(other.root);
            elemList = CopyList(other.elemList);
            RankTree(root, elemList, elemList->end());
            return *this;
        }
    }
    typedef typename std::list<T>::const_iterator iterator;
};

