#include <stdio.h>
//Max size of the cart array
#define MAX_CART_SIZE 10
//Max size of the inventory array
#define INVENTORY_SIZE 12
//New datatype, struct Cart, creates empty arrays with max sizes included, intergers, and floats.
struct Cart
{
    int    size;
    int    quantity [MAX_CART_SIZE];
    int    item     [MAX_CART_SIZE];
    float  price    [MAX_CART_SIZE];
    float  totalPrice;
};
//Prototypes of functions
void displayCart( struct Cart* pShoppingCart );
void addCart( struct Cart* pShoppingCart, int item[], float price[] );
void removeCart( struct Cart* pShoppingCart );
void checkout( struct Cart* pShoppingCart );
void displayShop( int n, int item[], float price[] );
void printTitle(void);
int getMenuChoice(void);
void clearScreen(int n);
void printGoodbye(void);
void findPrice( int n, int item[], float price[] );
int search( int n, int data[], int key );
int readInventory( char filename[], int item[], float price[] );
void writeCart( char filename[], struct Cart *pCart );
//Main function that calls upon other existing functions
int main(void)
{
    int counter = 1, menuOptions;
    //strings for filenames
    char inventory[] = "inventory.dat", cart[] = "cart.dat";
   
    //Array for customers cart using new data type, with the size of the array starting at zero
    struct Cart customersCart = {0};
   
    //Array for prices
    float price[INVENTORY_SIZE];
   
    //Array for items
    int item[INVENTORY_SIZE];
    readInventory( inventory, item, price );
   
    //Title function
    printTitle();
   
    //Counter is used to enable the menu choices to be printed again
    //for some options but not for others
    while(counter == 1)
    {
       
        //Menu function set as interger
        menuOptions = getMenuChoice();
       
        //Process user's choice
        switch(menuOptions)
        {
            case 1:
               
                //Shop display function
                displayShop( INVENTORY_SIZE, item, price ); counter = 1; break;
            case 2:
               
                //Price finding function
                findPrice( INVENTORY_SIZE, item, price ); counter = 1; break;
            case 3:
               
                //Displays Cart of the array with the new data type
                displayCart( &customersCart ); counter = 1; break;
            case 4:
               
                //Add's items to the cart to the array with the new data type
                addCart( &customersCart, item, price ); counter = 1; break;
            case 5:
               
                //Removes all items from cart, and resets array size to zero
                removeCart( &customersCart ); counter = 1; break;
            case 6:
               
                //Adds all price values in the array to get a total price
                checkout( &customersCart ); writeCart( cart, &customersCart ); counter = 1; break;
            case 7:
               
                //Specified number of new blank lines
                clearScreen(20); counter = 1; break;
            case 8:
               
                //Goodbye function
                printGoodbye(); counter = 2;
        }
    }
    return 0;
}
/*
    Name of Function: printTitle
    Purpose of Function: Displays the title
    Parameters: void
    Return: void
*/
void printTitle(void)
{
    printf("+-----------------------------------+\n");
    printf("|  Welcome to Ilan's Grocery Store  |\n");
    printf("+-----------------------------------+\n");
}
/*
    Name of Function: getMenuChoice
    Purpose of Function: Displays menu choices
    Parameters: void
    Return: returns the value the user inputs
*/
int getMenuChoice(void)
{
    int menuNumber;
    printf("What do you want to do?\n\n");
    printf("1 - What's in the shop?\n"
           "2 - What's the price of an item?\n"
           "3 - What's in my cart?\n"
           "4 - Add an item to my cart\n"
           "5 - Remove my cart\n"
           "6 - Check out\n"
           "7 - Clear screen\n"
           "8 - Leave the Shop\n\n");
   
    //Ask user for menu choice
    printf("Enter your choice ==> ");
    scanf("%d",&menuNumber);
    while(menuNumber < 1 || menuNumber > 8)
    {   
        //Error message until valid answer is provided
        printf("\n*** That choice is not valid ***\n\n");
        printf("Enter your choice ==> ");
        scanf("%d",&menuNumber);
    }
    return menuNumber;
}
/*
    Name of Function: clearScreen
    Purpose of Function: Determines how many new lines to print
    Parameters: int n //specifies how many newlines to print
    Return: void
*/
void clearScreen(int n)
{
    while(n > 0)
    {
        printf("\n");
        n--;
    }       
}
/*
    Name of Function: printGoodbye
    Purpose of Function: Displays thank you message
    Parameters: void
    Return: void
*/
void printGoodbye(void)
{
    printf("\nThank you for shopping at Ilan Zar's Grocery Store\n\n");
}
/*
    Name of Function: displayShop
    Purpose of Function: Displays item's SKU number and price
    Parameters: int n //specifies the size of the array.
                int item[] //item array. float price[] //price array 
    Return: void
*/
void displayShop( int n, int item[], float price[] )
{
   
    //int k, works as counter and holds the array index value for each item and price
    int k;
    printf("\n=== Inventory ===\n"
           "Item        Price\n"
           "----        -----\n");
        //allows to increment the array index value by one each time
    for(k = 0; k < n; k++)
        //prints the value of the item and price according to its location in the array index
        printf("%d%13.2f\n", item[k], price[k]);      
    printf( "=================\n\n");
}
/*
    Name of Function: findPrice
    Purpose of Function: Determines price of item's number
    Parameters: int n //specifies the size of the array. int item[]
                //item array. float price[] //price array.
    Return: void
*/
void findPrice( int n, int item[], float price[] )
{
    int itemNumber;
    printf("\nPlease input the number of the item ==> ");
    scanf("%d", &itemNumber);
    int itemLocation = search( INVENTORY_SIZE, item, itemNumber );
    if(itemLocation != -1)
        printf("\n%d's price is $%.2f\n\n", itemNumber, price[itemLocation]);
    else
        //Error message if item does not exist
        printf("\n%d is not found! Please try again.\n\n", itemNumber);
}   
/*
    Name of Function: search
    Purpose of Function: Function for determining if item number entered exists,
                         and the associated array index of the number
    Parameters: int n //specifies the size of the array. int item[] //item array.
                float price[] //price array.
    Return: returns either the array item index number of the item being scanned, or
            -1 to represent that the value input was invalid.
*/
int search( int n, int data[], int key )
{
    int i;
   
    //checks all possible values within the designated array
    for(i = 0; i < n; i++)
    {
        if(key == data[i])
            return i;
    }
    return -1;
}
/*
    Name of Function: addCart
    Purpose of Function: adds items to the cart, and adds to existing items.
    Parameters: *pShoppingCart //pointer that has a new datatype from the struct.
                int item[] //item array. float price[] //price array.
    Return: void
*/
void addCart( struct Cart* pShoppingCart, int item[], float price[] )
{
   
    //itemSkuNumber represents the input value of the item number provided by the user
    //itemQuantity represents the input value of the quantity provided by the user
    int itemNumber, itemQuantity;
   
    //Asks user for item number
    printf("\nPlease enter the number of the item: ");
    scanf("%d" , &itemNumber);
   
    //itemLocation represents the return value of the search function
    int itemLocation = search( INVENTORY_SIZE, item, itemNumber );
   
    //If the value is not -1 it indicates the value exists within the item array
    if(itemLocation != -1)
    {
       
        //Ask user for quantity of item
        printf("\nPlease enter the quantity of the item: ");
        scanf("%d", &itemQuantity);
       
        //itemExists represents the return value of the search function, as to
        //whether or not the item number exists in the cart
        int itemExists = search( MAX_CART_SIZE, pShoppingCart->item, itemNumber );
        if(itemExists == -1)
        {
       
        //Overwrites new item, quantity, and price values if item does not already exist in the cart
        pShoppingCart->quantity[pShoppingCart->size] = itemQuantity;
        pShoppingCart->item[pShoppingCart->size] = item[itemLocation];
        pShoppingCart->price[pShoppingCart->size] = price[itemLocation]*itemQuantity;
       
        //increment the size of the array by 1 each time the user inputs a valid value
        pShoppingCart->size++;
        } 
        else
        {
           
            //Overwrites values of quantity and price by adding to the existing values
            pShoppingCart->quantity[itemExists] += itemQuantity;
            pShoppingCart->price[itemExists] = price[itemLocation]*pShoppingCart->quantity[itemExists];
        }
       
        //confirmation message
        printf("\n%d of %d has been successfully added to your cart\n\n", itemQuantity, itemNumber);
    }
    else
       
        //Error message
        printf("\nIm sorry, that's not a valid item number\n\n");
}
 /*
    Name of Function: displayCart
    Purpose of Function: prints current items in the cart
    Parameters: *pShoppingCart //pointer that has a new datatype from the struct.
    Return: void
*/
void displayCart( struct Cart* pShoppingCart )
{
   
    //i refers to the array index value. n refers to the current size of the array
    int i, n = pShoppingCart->size;
   
    //if the current size of the array is not 0 then this displays the current items in the shop
    if(pShoppingCart->size != 0)
    {   
        printf("\n=====  Cart  =====\n"
               "Qty   Item   Price\n"
               "---   ----   -----\n");
   
    //displays each item in the array, by changing the array index by 1 each time through
    for(i = 0; i < n; i++)
        printf("%3d%7d%8.2f\n", pShoppingCart->quantity[i], pShoppingCart->item[i], pShoppingCart->price[i]);
    printf("==================\n\n");
    }
   
    //Two print carts due to the carts being slightly different in the instructions
   
    //if the current size of the array is 0 then there is nothing in the cart
    else
    {   
        printf("\n=====   Cart  =====\n"
               "---    empty    ---\n"
               "===================\n\n");
    }
}
/*
    Name of Function: removeCart
    Purpose of Function: removes the items from the cart by setting the array size value to zero
    Parameters: *pShoppingCart //pointer that has a new datatype from the struct.
    Return: void
*/
void removeCart( struct Cart* pShoppingCart )
{
    int i;
    char confirmation;
   
    //prints error message if array size is already zero
    if(pShoppingCart->size == 0)
        printf("\nYour cart is already empty\n\n");
   
    //resets value of size to zero
    else if(pShoppingCart->size != 0)
    {   
       
        //prints confirmation message if array size is not zero
        printf("\nAre you sure?\n\nY or N: ");
        scanf("%s", &confirmation);
        if(confirmation == 'Y' || confirmation == 'y')
        {
            pShoppingCart->size = 0;
            printf("\ncart is successfully removed\n\n");
        }
        else
            printf("\n");
    }
}
/*
    Name of Function: checkout
    Purpose of Function: displays the total price of the items in the cart
    Parameters: *pShoppingCart //pointer that has a new datatype from the struct.
    Return: void
*/
void checkout( struct Cart* pShoppingCart )
{
   
    //'i' refers to the array index value. 'n' refers to the current size of the array
    int i, n = pShoppingCart->size;
   
    //Adds prices of each item, multiplied by each quantity according to the array item index.
    for(i = 0; i < n; i++)
        pShoppingCart->totalPrice = pShoppingCart->totalPrice + pShoppingCart->price[i];
   
    //prints the total price of items in the cart
    printf("\nYour total comes to $%.2f\n\n", pShoppingCart->totalPrice);
}
/*
    Name of Function: reaInventory
    Purpose of Function: reads data from the file, and sends it to the
                         item and price arrays
    Parameters: char filename[] //specifies name of file you want to read from
                int item[] //item array. float price[] //price array.
    Return: void
*/
int readInventory( char filename[], int item[], float price[] )
{
   
    //File pointer declaration
    FILE *inventory;
    int n;
   
    //Opens file to read
    if( (inventory = fopen( filename, "r")) != NULL )
    {   
       
        //Reads and sends data to item and price arrays
        for( n = 0; n < INVENTORY_SIZE; n++ )
        {
            fscanf(inventory, "%d", &item[n]);
            fscanf(inventory, "%f", &price[n]);
        }
       
        //Closes file
        fclose(inventory);
            return 1;
    }
    else

        //If the file did not open successfully
        return 0;
}   
/*
    Name of Function: writeCart
    Purpose of Function: writes data of current cart to a file
    Parameters: char filename[] //specifies name of file you want to write to
                int item[] //item array. float price[] //price array.
    Return: void
*/
void writeCart( char filename[], struct Cart *pCart )
{
   
    //File pointer declaration
    FILE *wCart;
    int n;
   
    //Opens file to write
    wCart = fopen( filename, "w" );
    if( pCart->size == 0 )
    {
        fprintf( wCart, "=====   Cart  =====\n"
                        "---    empty    ---\n"
                        "===================\n" );
    }
    else
    {
        fprintf( wCart, "=====  Cart  =====\n"
                        "Qty   Item   Price\n"
                        "---   ----   -----\n" );
       
        //n specifies the index value of each array
        for( n = 0; n < pCart->size; n++ )
            fprintf( wCart, "%2d%8d%8.2f\n", pCart->quantity[n], pCart->item[n], pCart->price[n] );
        fprintf( wCart, "==================\n" );
        fprintf( wCart, "T O T A L%9.2f\n", pCart->totalPrice );
        fprintf( wCart, "==================\n" );
    }
}
