#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// STRUCTURE DEFINITIONS
// ==========================================

// Base Product Struct
typedef struct {
    char name[50];
    int code;
    double price;
} Product;

// Node Struct for Linked List
typedef struct Node {
    Product data;
    struct Node *next;
} Node;

// ==========================================
// FUNCTION DECLARATIONS
// ==========================================

// Question 1 Functions
void print_product(const Product *p);
void update_price(Product *p, double new_price);

// Question 2 Functions
void read_product_input(Product *p);
const Product* find_most_expensive(const Product *inventory, int count);
void print_inventory(const Product *inventory, int count);

// Question 3 Functions
void append_node(Node **head, Product p);
void traverse_and_print_list(const Node *head);
void free_list(Node *head);

// Bonus Function
void delete_node_by_code(Node **head, int code);

// ==========================================
// MAIN 
// ==========================================



    // ------------------------------------------
    // QUESTION 2: Dynamic Inventory
    // ------------------------------------------
    printf("\n==========================================\n");
    printf("QUESTION 2: Build a Dynamic Inventory\n");
    printf("==========================================\n");

    int count = 0;
    printf("How many products do you want to enter? ");
    if (scanf("%d", &count) != 1 || count <= 0) {
        printf("Invalid count entered. Skipping Question 2.\n");
    } else {

        Product *inventory = malloc((size_t)count * sizeof(*inventory));


        if (inventory == NULL) {
            printf("Error: Memory allocation failed!\n");
            return 1;
        }


        printf("\n--- Enter Details for %d Products ---\n", count);
        for (int i = 0; i < count; i++) {
            printf("Product #%d:\n", i + 1);
            read_product_input(&inventory[i]);
        }


        const Product *expensive = find_most_expensive(inventory, count);
        if (expensive != NULL) {
            printf("=== Most Expensive Product ===\n");
            print_product(expensive);
        }


        printf("--- Adding One More Product using realloc ---\n");
        int new_count = count + 1;
        Product *temp = realloc(inventory, (size_t)new_count * sizeof(*inventory));

        if (temp == NULL) {
            printf("Error: Memory reallocation failed!\n");
            free(inventory);
            inventory = NULL;
            return 1;
        }
        inventory = temp;


        printf("Enter details for the new product:\n");
        read_product_input(&inventory[new_count - 1]);


        printf("=== Updated Dynamic Inventory (%d Items) ===\n", new_count);
        print_inventory(inventory, new_count);


        free(inventory);
        inventory = NULL;
    }


    // ------------------------------------------
    // QUESTION 3: Linked List Implementation
    // ------------------------------------------
    printf("\n==========================================\n");
    printf("QUESTION 3: Turn Records into a Linked List\n");
    printf("==========================================\n");
    Node *head = NULL;

    Product item1 = {"Mechanical Keyboard", 3001, 129.99};
    Product item2 = {"Gaming Monitor", 3002, 349.50};
    Product item3 = {"USB-C Hub", 3003, 45.00};
    append_node(&head, item1);
    append_node(&head, item2);
    append_node(&head, item3);
    printf("=== Traversing Linked List ===\n");
    traverse_and_print_list(head);


    // ------------------------------------------
    // BONUS: Remove a Product from Linked List
    // ------------------------------------------
    printf("\n==========================================\n");
    printf("BONUS: Think Outside the Box (Remove Node)\n");
    printf("==========================================\n");

    int code_to_delete = 0;
    printf("Enter a product code to remove from the linked list: ");
    if (scanf("%d", &code_to_delete) == 1) {
        delete_node_by_code(&head, code_to_delete);

        printf("=== Linked List After Deletion ===\n");
        traverse_and_print_list(head);
    }

    
    free_list(head);
    head = NULL;

    printf("All linked list memory freed successfully.\n");

    return 0;
}

// ==========================================
// FUNCTION IMPLEMENTATIONS
// ==========================================

// Question 1: Print product details
void print_product(const Product *p) {
    if (p == NULL) return;
    printf("Product Name : %s\n", p->name);
    printf("Product Code : %d\n", p->code);
    printf("Price        : $%.2f\n\n", p->price);
}

// Question 1: Change product price using pointer & -> operator
void update_price(Product *p, double new_price) {
    if (p != NULL) {
        p->price = new_price;
    }
}

// Question 2: Read product input safely
void read_product_input(Product *p) {
    if (p == NULL) return;
    printf("Enter product name: ");
    scanf(" %49[^\n]", p->name);
    printf("Enter product code: ");
    scanf("%d", &p->code);
    printf("Enter price: ");
    scanf("%lf", &p->price);
    printf("\n");
}

// Question 2: Find the most expensive product
const Product* find_most_expensive(const Product *inventory, int count) {
    if (inventory == NULL || count <= 0) return NULL;

    const Product *most_expensive = &inventory[0];
    for (int i = 1; i < count; i++) {
        if (inventory[i].price > most_expensive->price) {
            most_expensive = &inventory[i];
        }
    }
    return most_expensive;
}

// Question 2: Print dynamic array inventory
void print_inventory(const Product *inventory, int count) {
    if (inventory == NULL) return;
    for (int i = 0; i < count; i++) {
        printf("Product #%d:\n", i + 1);
        print_product(&inventory[i]);
    }
}

// Question 3: Append node to linked list using malloc
void append_node(Node **head, Product p) {
    Node *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed for new node!\n");
        return;
    }
    new_node->data = p;
    new_node->next = NULL; // Last node points to NULL

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

// Question 3: Traverse list and print every product
void traverse_and_print_list(const Node *head) {
    const Node *current = head;
    int index = 1;
    while (current != NULL) {
        printf("--- Linked List Node #%d ---\n", index++);
        print_product(&(current->data));
        current = current->next;
    }
}

// Question 3: Free every node by saving 'next' before freeing current
void free_list(Node *head) {
    Node *current = head;
    Node *next_node = NULL;

    while (current != NULL) {
        next_node = current->next; 
        free(current);             
        current = next_node;       
    }
}

// Bonus: Delete a node matching product code
void delete_node_by_code(Node **head, int code) {
    if (head == NULL || *head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    Node *temp = *head;
    Node *prev = NULL;

    // Case 1: Head node matches code
    if (temp != NULL && temp->data.code == code) {
        *head = temp->next;
        free(temp);
        printf("Product code %d successfully removed.\n\n", code);
        return;
    }

    // Case 2: Search middle/tail for matching code
    while (temp != NULL && temp->data.code != code) {
        prev = temp;
        temp = temp->next;
    }

    // Case 3: Code not found
    if (temp == NULL) {
        printf("Product code %d not found in the list.\n\n", code);
        return;
    }

    // Reconnect pointers and free deleted node
    prev->next = temp->next;
    free(temp);
    printf("Product code %d successfully removed.\n\n", code);
}