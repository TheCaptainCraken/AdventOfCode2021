#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedLists.h"

struct node_s {
    int val;
    struct node_s* next;
};

int FindMax(Node* head) {
    Node* current = head;
    int max = current->val;
    current = current->next;
    while (current != NULL) {
        if (max < current->val) {
            max = current->val;
        }
        current = current->next;
    }

    return max;
}

Node* CreateNode(int val) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Allocation error while creating a node.\n");
        return NULL;
    }
    new_node->val = val;
    new_node->next = NULL;
}

int GetListLength(Node* head) {
    Node* current = head;
    int length = 0;
    while (current != NULL) {
        current = current->next;
        length++;
    }
    return length;
}

bool Append(Node** head_pointer, int val) {
    int length = GetListLength(*head_pointer);
    if (length == 0) {
        *head_pointer = CreateNode(val);
        if (*head_pointer == NULL) { return false; }
        else { return true; }
    }
    else {
        Node* new_node = CreateNode(val);
        if (new_node == NULL) { return false; }
        Node* current = *head_pointer;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
        return true;
    }
}

void PrintList(Node* head, const char* separator) {
    Node* current = head;
    if (current == NULL) { return; }
    while (current->next != NULL) {
        printf("%d%s", current->val, separator);
        current = current->next;
    }
    printf("%d\n", current->val);
}

bool Push(Node** head_pointer, int val) {
    if (*head_pointer == NULL) {
        *head_pointer = CreateNode(val);
        if (*head_pointer == NULL) { return false; }
        else { return true; }
    }

    Node* new_node = CreateNode(val);
    if (new_node == NULL) { return false; }
    new_node->next = *head_pointer;
    *head_pointer = new_node;
    return true;
}

int* ListToArray(Node* head, int* length) {
    *length = GetListLength(head);
    int* array = (int*)malloc(sizeof(int) * *length);
    if (array == NULL) { return NULL; }

    Node* current = head;

    for (int i = 0; current != NULL; i++, current = current->next) {
        *(array + i) = current->val;
    }

    return array;
}

int Pop(Node** head_pointer) {
    if (*head_pointer == NULL) { printf("Popping from an empty list!\n"); return -1; }
    Node* tmp = *head_pointer;
    *head_pointer = (*head_pointer)->next;
    int return_val = tmp->val;
    free(tmp);
    return return_val;
}

int BackPop(Node** head_pointer) {
    if (*head_pointer == NULL) { printf("Backpopping from an empty list!\n"); return -1; }

    Node* current = *head_pointer;
    while (current->next->next != NULL) {
        current = current->next;
    }

    int return_val = current->next->val;
    free(current->next);
    current->next = NULL;
    return return_val;
}

int FindFromIndex(Node* head, int index) {
    Node* current = head;

    for (int i = 0; i < index; i++) {
        if (current == NULL) {
            printf("Invalid index!\n");
            return -1;
        }
        else {
            current = current->next;
        }
    }

    return current->val;
}

bool DeleteFromIndex(Node** head_pointer, int index) {
    if (index == 0) {
        if (*head_pointer == NULL) { return false; }
        Pop(head_pointer);
        return true;
    }
    Node* current = *head_pointer;

    for (int i = 0; i < index - 1; i++) {
        current = current->next;
        if (current == NULL) { return false; }
    }
    if (current->next != NULL) {
        if (current->next->next != NULL) {
            Node* tmp = current->next;
            current->next = current->next->next;
            free(tmp);
        }
        else {
            free(current->next);
        }
        return true;
    }
    else {
        return false;
    }
}

void DeleteList(Node** head_pointer) {
    while (head_pointer != NULL) {
        BackPop(head_pointer);
    }
}

int Part2(int a) {
    int sum = 0;
    for (int i = 1; i <= a; i++) {
        sum += i;
    }
    return sum;
}

int CalcFuel(Node* head, int pos) {
    Node* current = head;

    int fuel = 0;

    while (current != NULL) {
        int tmp = pos - current->val;
        if (tmp < 0) { tmp *= -1; }
        fuel += Part2(tmp);
        current = current->next;
    }

    return fuel;
}