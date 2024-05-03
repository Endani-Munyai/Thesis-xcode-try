//
//  diagnostic.c
//  Thesis xcode try
//
//  Created by Endani Munyai
//

#include "diagnostic.h"

long memoryProduct(p_Product p)
{
	long size;
	size = sizeof(struct Product);
	return size;
}

long memoryInventory (p_Inventory p)
{
	long size;
	size = sizeof(struct Inventory) + (p->number_different_products-1) * sizeof(p_Product);
	for (int i=0; i<p->number_different_products; i++) size = size + memoryProduct(p->products[i]);
	return size;
}

long memoryPurchase (p_Purchase p)
{
	long size;
	size = sizeof(struct Purchase) + (p->number_different_products-1) * sizeof(p_Purchase);
	for (int i=0; i<p->number_different_products;i++) size = size + memoryProduct(p->products[i]);
	return size;
}

long memoryLedger (p_Ledger p)
{
	long size;
	size = sizeof(struct Ledger) + (p->number_purchases-1) * sizeof(p_Purchase);
	for (int i=0; i<p->number_purchases;i++) size = size + memoryPurchase(p->purchases[i]);
	return size;
}


void createstruct(int input,
				  p_Inventory p,
				  p_Ledger q)
{
	p_Inventory* a = &p;
	p_Ledger* b = &q;
	*a = generateInventory(input);
	*b = generateLedger(p, input);
	printf("\nMemory taken: %ld\n",memoryInventory(p) + memoryLedger(q));
}

void populatestruct(p_Inventory p,
					p_Ledger q,
					p_Inventory r)
{
	struct Inventory** a = &r;
	populateInventory(p);
	populateLedger(p, q, p->number_different_products);
	*a = generateOutgoingInventory(q);
}

void displaystruct(p_Inventory p,
				   p_Ledger q)
{
	printf("Total inventory\n");
	displayInventory(p);
	printf("Outgoing Ledger\n");
	displayLedger(q);
}

void displaystructs(p_Inventory p,
				   p_Ledger q,
				   p_Inventory r)
{
	printf("Total inventory\n");
	displayInventory(p);
	printf("Outgoing Ledger\n");
	displayLedger(q);
	printf("Outgoing inventory\n");
	displayInventory(r);
}

void destroystruct (p_Inventory p,
					p_Ledger q,
					p_Inventory r )
{
	printf("Memory freedom functions\n");
	p = destroyInventory(p);
	q = destroyLedger(q);
	r = destroyInventory(r);
}
