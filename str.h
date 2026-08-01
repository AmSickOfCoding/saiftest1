#ifndef STR_H
#define STR_H
typedef struct {
    char name[50];
    int code;
    double price;
} Product;
typedef struct Node {
    Product data;
    struct Node *next;
} Node;

// Function declarations
void print_product(const Product *p);
void update_price(Product *p, double new_price);


// ==========================================
// QUESTION 2 DECLARATIONS
// ==========================================
void read_product_input(Product *p);
Product* find_most_expensive(Product *inventory, int count);
void print_inventory(const Product *inventory, int count);

// ==========================================
// QUESTION 3 DECLARATIONS
// ==========================================
typedef struct Node {
    Product data;
    struct Node *next;
} Node;

void append_node(Node **head, Product p);
void traverse_and_print_list(const Node *head);
void free_list(Node *head);
// ==========================================
// BONUS DECLARATION 
// ==========================================
void delete_node_by_code(Node **head, int code);
#endif // STR_H