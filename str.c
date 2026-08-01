#include <stdio.h>
#include <stdlib.h>
#include "str.h"

// Function to print a product's details
void print_product(const Product *p) {
    printf("Product Name : %s\n", p->name);
    printf("Product Code : %d\n", p->code);
    printf("Price        : $%.2f\n\n", p->price);
}

// Function to modify product price using a pointer and the -> operator
void update_price(Product *p, double new_price) {
    p->price = new_price;
}

// ==========================================
// QUESTION 2 FUNCTIONS
// ==========================================

// Helper function to read a single product from user input
void read_product_input(Product *p) {
    printf("Enter product name: ");
    scanf(" %49[^\n]", p->name);
    printf("Enter product code: ");
    scanf("%d", &p->code);
    printf("Enter price: ");
    scanf("%lf", &p->price);
    printf("\n");
}

// Function to find the most expensive product
Product* find_most_expensive(Product *inventory, int count) {
    if (inventory == NULL || count <= 0) return NULL;

    Product *most_expensive = &inventory[0];
    for (int i = 1; i < count; i++) {
        if (inventory[i].price > most_expensive->price) {
            most_expensive = &inventory[i];
        }
    }
    return most_expensive;
}

// Function to print all products in inventory
void print_inventory(const Product *inventory, int count) {
    for (int i = 0; i < count; i++) {
        printf("Product #%d:\n", i + 1);
        print_product(&inventory[i]);
    }
}
// ==========================================
// QUESTION 3 FUNCTIONS
// ==========================================

// Add node using malloc and set last node's next pointer to NULL
void append_node(Node **head, Product p) {
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        printf("Memory allocation failed for new node!\n");
        return;
    }
    new_node->data = p;
    new_node->next = NULL; // Ensure last node points to NULL

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// Traverse the linked list and print every product
void traverse_and_print_list(const Node *head) {
    const Node *current = head;
    int index = 1;
    while (current != NULL) {
        printf("--- Linked List Node #%d ---\n", index++);
        print_product(&(current->data));
        current = current->next;
    }
}

// Free every node correctly by saving 'next' before freeing current
void free_list(Node *head) {
    Node *current = head;
    Node *next_node = NULL;

    while (current != NULL) {
        next_node = current->next; // Save next pointer before freeing
        free(current);             // Free current node
        current = next_node;       // Advance to next
    }
}
// ==========================================
// BONUS FUNCTION: Delete Node by Code
// ==========================================
void delete_node_by_code(Node **head, int code) {
    if (*head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    Node *temp = *head;
    Node *prev = NULL;

    // Head node matches code
    if (temp != NULL && temp->data.code == code) {
        *head = temp->next;
        free(temp);
        printf("Product with code %d deleted successfully.\n\n", code);
        return;
    }

    // Search middle/tail for matching code
    while (temp != NULL && temp->data.code != code) {
        prev = temp;
        temp = temp->next;
    }

    // Code not found
    if (temp == NULL) {
        printf("Product with code %d not found in the list.\n\n", code);
        return;
    }

    // Unlink and free
    prev->next = temp->next;
    free(temp);
    printf("Product with code %d deleted successfully.\n\n", code);
}