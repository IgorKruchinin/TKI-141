#pragma once

template <typename T>
struct Node {
    T value;
    Node *next;
    Node(int value, Node* next = nullptr) {
        this->value = value;
        this->next = next;
    }
};
