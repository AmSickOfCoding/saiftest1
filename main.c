#include <stdio.h>
#include <stdlib.h>
#include "str.h"

int main(void) {
    // 1. Create two products
    Product p1 = {"Laptop", 1001, 899.99};
    Product p2 = {"Wireless Mouse", 1002, 25.50};

    // 2. Print initial records
    printf("=== Initial Product Records ===\n");
    print_product(&p1);
    print_product(&p2);

    // 3. Update the price of product 1
    printf("Updating price of %s from $%.2f to $799.99...\n\n", p1.name, p1.price);
    update_price(&p1, 799.99);

    // 4. Print updated record to verify the price change
    printf("=== Updated Record ===\n");
    print_product(&p1);
    // ==========================================
    // QUESTION 2: Build a Dynamic Inventory
    // ==========================================
    printf("\n==========================================\n");
    printf("QUESTION 2: Build a Dynamic Inventory\n");
    printf("==========================================\n");

    int count = 0;
    printf("How many products do you want to enter? ");
    scanf("%d", &count);

    if (count <= 0) {
        printf("Invalid number of products.\n");
        return 0;
    }

    // Allocate memory using malloc with sizeof(*inventory)
    Product *inventory = malloc(count * sizeof(*inventory));

    // Check if allocation returned NULL
    if (inventory == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Read all product records
    printf("\n--- Enter Details for %d Products ---\n", count);
    for (int i = 0; i < count; i++) {
        printf("Product #%d:\n", i + 1);
        read_product_input(&inventory[i]);
    }

    // Print the most expensive product
    Product *expensive = find_most_expensive(inventory, count);
    if (expensive != NULL) {
        printf("=== Most Expensive Product ===\n");
        print_product(expensive);
    }

    // Use realloc to add one more product
    printf("--- Adding One More Product using realloc ---\n");
    int new_count = count + 1;
    Product *temp = realloc(inventory, new_count * sizeof(*inventory));

    if (temp == NULL) {
        printf("Reallocation failed!\n");
        free(inventory);
        inventory = NULL;
        return 1;
    }
    inventory = temp;

    // Read details for the newly added product
    printf("Enter details for the new product:\n");
    read_product_input(&inventory[new_count - 1]);

    // Print updated inventory
    printf("=== Updated Inventory (%d Items) ===\n", new_count);
    print_inventory(inventory, new_count);

    // Release memory and set pointer to NULL
    free(inventory);
    inventory = NULL;

    // ==========================================
    // QUESTION 3: Turn Records into a Linked List
    // ==========================================
    printf("\n==========================================\n");
    printf("QUESTION 3: Turn Records into a Linked List\n");
    printf("==========================================\n");

    Node *head = NULL;

    // Define 3 product records
    Product item1 = {"Mechanical Keyboard", 3001, 129.99};
    Product item2 = {"Gaming Monitor", 3002, 349.50};
    Product item3 = {"USB-C Hub", 3003, 45.00};

    // Add at least three nodes using malloc
    append_node(&head, item1);
    append_node(&head, item2);
    append_node(&head, item3);

    // Traverse the list and print every product
    printf("=== Traversing Linked List ===\n");
    traverse_and_print_list(head);

    // Free every node correctly by saving next before freeing current
    free_list(head);
    head = NULL;

    printf("Linked list memory successfully freed.\n");
    // ==========================================
    // BONUS: Standalone Deletion Demo
    // ==========================================
    printf("\n==========================================\n");
    printf("BONUS: Standalone Product Removal\n");
    printf("==========================================\n");

    Node *bonus_head = NULL;

    // Create a fresh independent list for the bonus
    append_node(&bonus_head, (Product){"Tablet", 4001, 299.99});
    append_node(&bonus_head, (Product){"Headphones", 4002, 89.99});
    append_node(&bonus_head, (Product){"Smartwatch", 4003, 199.99});

    printf("=== Initial Bonus Linked List ===\n");
    traverse_and_print_list(bonus_head);

    int code_to_delete;
    printf("Enter product code to remove: ");
    scanf("%d", &code_to_delete);

    delete_node_by_code(&bonus_head, code_to_delete);

    printf("=== Bonus List After Deletion ===\n");
    traverse_and_print_list(bonus_head);

    // Free remaining list nodes
    free_list(bonus_head);
    bonus_head = NULL;

    return 0;
}

