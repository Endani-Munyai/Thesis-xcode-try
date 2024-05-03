//
//  products.h
//  Thesis xcode try
//
//  Created by Endani Munyai
//

#ifndef products_h
#define products_h

#include <stdio.h>
typedef struct Product *p_Product;
typedef struct Purchase *p_Purchase;
typedef struct Ledger *p_Ledger;
typedef struct Inventory *p_Inventory;

struct Product
{
	int Count;
	int ID;
};

struct Purchase
{
	int number_different_products;
	p_Product products[1];
};

// outgoing products
struct Ledger
{
	int ID; // =0 for total ledger, >0 for users
	int number_purchases;
	int number_different_products;
	p_Purchase purchases[1];
};

// floating stock/inventory
struct Inventory
{
	int ID; // 0 when its the stock inventory, -1 when its the total outgoing inventory, equal to user id otherwise
	int number_different_products;
	p_Product products[1];
};

struct Product;
struct Purchase;
struct Ledger;
struct Inventory;

void displayProduct(p_Product p);
long memoryProduct(p_Product p);

/* Inventory functions*/
p_Inventory generateInventory (int products);
void populateInventory (p_Inventory p);
p_Inventory destroyInventory (p_Inventory p);
void displayInventory (p_Inventory p);
long memoryInventory (p_Inventory p);

/* Purchase functions*/
p_Purchase generatePurchase (p_Inventory stock);
void populatePurchase (p_Inventory stock,
					   p_Purchase p);
p_Purchase destroyPurchase (p_Purchase p);
void displayPurchase (p_Purchase p);
long memoryPurchase (p_Purchase p);

/* Ledger functions*/
int stockremaining(p_Inventory stock,
				   p_Ledger ledger);
p_Ledger generateLedger (p_Inventory stock,
						 int number_purchases);
void populateLedger (p_Inventory stock,
					 p_Ledger p,
					 int ID);
p_Inventory generateOutgoingInventory (p_Ledger ledger);
p_Ledger destroyLedger (p_Ledger p);
void displayLedger (p_Ledger p);
long memoryLedger (p_Ledger p);



#endif /* products_h */
