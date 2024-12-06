#pragma once

template <typename T>
struct Node {
    T value;
    Node *next;
    Node(int value, Node* next = nullptr);
};

template <typename T>
Node<T>::Node(int value, Node<T>* next) {
        this->value = value;
        this->next = next;
}
