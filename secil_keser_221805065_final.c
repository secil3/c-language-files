#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_products 100 // Maximum number of products that can be stored

// Define a struct to hold product information
struct Product {
    int id;
    char name[50];
    char unit[50];
    int quantity;
};

// Function describing
void addProducts(struct Product *products, int *num_products);
void updateProducts(struct Product *products, int num_products);
void searchProducts(struct Product *products, int num_products);
void incProducts(struct Product *products, int num_products);
void decProducts(struct Product *products, int num_products);
void listProducts(struct Product *products, int num_products);
void addProductToFile(struct Product *products, int *num_products, const char *filename);

int main() {
    struct Product products[MAX_products]; // Array of products
    int num_products = 0; // Number of products currently in the array
    FILE *fptr; // Pointer to file
    char filename[] = "products.txt"; // Name of file containing product information
    char line[200]; // Buffer for reading each line of the file
    char *token; // Pointer to token within line
    int choice;
    
    // Open file for reading
    fptr = fopen(filename, "r"); 
    if (fptr == NULL) {
        printf("error: could not open file %s\n", filename);
    }
    else {
        printf("file open successful      %s\n",filename);
        
        // Read each line of file, parse product information, and store in array
        while (fgets(line, sizeof(line), fptr) != NULL) {
            token = strtok(line, ",");
            products[num_products].id = atoi(token);
            token = strtok(NULL, ",");
            strcpy(products[num_products].name, token);
            token = strtok(NULL, ",");
            strcpy(products[num_products].unit, token);
            token = strtok(NULL, ",");
            products[num_products].quantity = atoi(token);
            (num_products)++;
        }
        
        // write products to the file
    	fputs("100,Oil,5kg,25\n",fptr);
        fputs("101,Milk,1kg,30\n",fptr);
        fputs("102,Milk,200ml,50\n",fptr);
        fputs("103,Egg,10 pieces,24\n",fptr);
        fputs("104,Cottage Cheese, 200 gr,15\n",fptr);
        fputs("200,Lavender Liquid Soap,1 kg, 10\n",fptr);
        fputs("201,Rose Liquid Soap,1kg, 12\n",fptr);
        fputs("202,Dalin Shampoo, 400gr, 8\n",fptr);
        fputs("203,Dalin Shampoo, 600gr, 12\n",fptr);
        fputs("204,Omo Washing Powder, 7kg,26\n",fptr);
        fputs("205,Finish Dishwasher Detergent,78 pieces, 18\n",fptr);
        
        fclose(fptr);
    }

//   menu and choosing the number
    do {
        printf("\nMenu:\n1. Add a new product\n2. Update a product\n");
        printf("3. Search for a product with name\n");
        printf("4. Increase quantity of a product\n");
        printf("5. Decrease quantity of a product\n");
        printf("6. List all product\n7. Exit\n");

        printf("enter your choice (1-7): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProducts(products, &num_products);
                break;
            case 2:
                updateProducts(products, num_products);
              break;
            case 3:
                searchProducts(products, num_products);
                break;
            case 4:
                incProducts(products, num_products);
             break;
            case 5:
                decProducts(products, num_products);
               break;
            case 6:
                listProducts(products, num_products);
               break;
            case 7:
                printf("quitting...\n");
                break;
            default:
                printf("invalid choice. please try again.\n");
                break;
        }
    } while (choice != 7);

    return 0;
}

// open file for append, add to the file
void addProductToFile(struct Product *products, int *num_products, const char *filename) {
    FILE *fptr = fopen(filename, "a");
    if (fptr == NULL) {
        printf("error: could not open file for writing\n");
        return;
    }
  else{
     fprintf(fptr,"%d,%s,%s,%d\n",products[*num_products].id, products[*num_products].name, products[*num_products].unit, products[*num_products].quantity);
     fclose(fptr);
   }
}

//adding products to the file
void addProducts(struct Product *products, int *num_products) { 
    if (*num_products >= MAX_products) {
        printf("product list is full!\n");
   }

    printf("enter new product id: ");
    scanf("%d", &products[*num_products].id);
    printf("enter name of the new product: ");
    scanf("%s", &products[*num_products].name);
    printf("enter the unit of new product: ");
    scanf("%s", &products[*num_products].unit);
    printf("enter the quantity of new product: ");
    scanf("%d", &products[*num_products].quantity);
    
    //add product to the file
    addProductToFile(products,num_products,"a7products.txt");
    (*num_products)++;

    printf("\nproduct added successfully.\n");
}

//updating products 
void updateProducts(struct Product *products, int num_products) {
    int id;
    printf("enter product number to update: ");
    scanf("%d", &id);

    int i;
    for (i = 0; i < num_products; i++) {
        if (products[i].id == id) {
            printf("Product found. Which field would you like to update?\n");
            printf("1. Id\n2. Name\n3. Unit\n4. Quantity\n");
            int choice;
            printf("enter your choice (1-4): ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    printf("enter new product id: ");
                    scanf("%d", &products[i].id);
                    printf("new id: %d\n", products[i].id);
                    break;
                case 2:
                    printf("enter new product name: ");
                    scanf("%s", products[i].name);
                    printf("new name: %s\n", products[i].name);
                    break;
                case 3:
                    printf("enter new unit: ");
                    scanf("%s", products[i].unit);
                    printf("new unit: %s\n", products[i].unit);
                    break;
                case 4:
                    printf("enter new quantity: ");
                    scanf("%d", &products[i].quantity);
                    printf("new quantity: %d\n", products[i].quantity);
                    break;
                default:
                    printf("invalid choice. please try again.\n");
                    break;
            }
            return;
        }
    }
    printf("product with id %d not found.\n", id);
}

//searching the products
void searchProducts(struct Product *products, int num_products) {
    char name[50];
    printf("enter name of the product: ");
    scanf("%s", name);

    int i;
    printf("products matching %s:\n", name);
    int found = 0;
    for (i = 0; i < num_products; i++) {
        if (strcmp(products[i].name, name) == 0) {
            printf("%d\t%s\t%s\t%d\n", products[i].id, products[i].name, products[i].unit, products[i].quantity);
            found = 1;
        }
    }
    if (!found) {
        printf("no product found with the name %s.\n", name);
    }
}

// increase quantity of a product
void incProducts(struct Product *products, int num_products) {
    int id, quantity;
    printf("enter product number (id) to update: ");
    scanf("%d", &id);
    printf("enter the increment quantity: ");
    scanf("%d", &quantity);

    int i;
    for (i = 0; i < num_products; i++) {
        if (products[i].id == id) {
            products[i].quantity += quantity;
            printf("new quantity of %s: %d\n", products[i].name, products[i].quantity);
            return;
        }
    }
    printf("product with id %d not found.\n", id);
}

// decrease quantity of a product
void decProducts(struct Product *products, int num_products) {
    int id, quantity;
    printf("enter product number to update: ");
    scanf("%d", &id);
    printf("enter the decrement quantity: ");
    scanf("%d", &quantity);

    int i;
    for (i = 0; i < num_products; i++) {
        if (products[i].id == id) {
            if (products[i].quantity >= quantity) {
                products[i].quantity -= quantity;
                printf("new quantity of %s: %d\n", products[i].name, products[i].quantity);
            } else {
                printf("error: quantity to decrease is greater than available quantity.\n");
            }
            return;
        }
    }
    printf("product with id %d not found.\n", id);
}

//list all products with an append version
void listProducts(struct Product *products, int num_products) {
    printf("\n\tID\t\t\t\tNAME\t\t\t UNIT\t\t\t QUANTITY\n");
    int i;
    for (i = 0; i < num_products; i++) {
        printf("%10d%34s%25s%25d\n", products[i].id, products[i].name, products[i].unit, products[i].quantity);
    }
}

