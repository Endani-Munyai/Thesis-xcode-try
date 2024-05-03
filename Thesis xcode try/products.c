//
//  products.c
//  Thesis xcode try
//
//  Created by Endani Munyai
//

#include "products.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

#define small_n (11)
#define medium_n (23)
#define large_n (37)

/* Structures */



/* Functions */

void displayProduct(p_Product p)
{
	if (p==NULL)
	{
		printf("Pointer does not exist\n");
		return;
	}
	printf("Product ID:\t%d \n Product count:\t%d",p->ID,p->ID);
	return;
}

/* Inventory functions*/

p_Inventory generateInventory (int products)
{
	if (products<1)
	{
		printf("\nInventory failed to create due to invalid (i.e. less than 1) number of products\n");
		return NULL;
	}
	p_Inventory p_stock;
	int temp = sizeof(struct Inventory) + sizeof(struct Product *) * (products - 1);
	p_stock = malloc(temp);
	p_stock->number_different_products = products;
	
	for (int i=0; i<products; i++)
	{
		p_stock->products[i]= malloc(sizeof(struct Product));
		p_stock->products[i]->ID = i;
		p_stock->products[i]->Count = 0;
	}
	return p_stock;
}

void populateInventory (p_Inventory p)
{
	clock_t start = clock();
	if (p == 0x0)
	{
		printf("Inventory failed to populate due to null inventory pointer\n");
		return;
	}
	int a,
	b,
	c;
	int temp=0;
	clock_t finish = (clock()-start);
	srand((int) time(0)+(int) finish);
	for (int i=0; i<p->number_different_products; i++)
	{
		do {
			a = rand() % small_n;
			b = rand() % medium_n;
			c = rand() % large_n;
			temp = (a + b + c) * 10;
		} while (temp<1);
		p->products[i]->Count = temp + rand()%10;
	}
	p->ID=0;
	return;
}

p_Inventory destroyInventory (p_Inventory p)
{
	if (p == 0x0) return NULL;
	for (int i = 0; i < p->number_different_products; i++)
	{
		free(p->products[i]);
		p->products[i]=0x0;
	}
	free(p);
	return NULL;
}

void displayInventory (p_Inventory p)
{
	if (p==NULL)
	{
		printf("Display Inventory failed due to null pointer\n");
		return;
	}
	if (p->ID==0) printf("\nInventory Product ID:\t");
	else if (p->ID==1) printf("\nOutgoing Inventory Product ID:\t\t");
	else printf("\nUser %d purchase Inventory Product ID:\t", p->ID);
	for (int i=0; i< p->number_different_products; i++)
		printf("%d\t",p->products[i]->ID);
	if (p->ID==0) printf("\nInventory Product Count:\t");
	else if (p->ID==1) printf("\nOutgoing Inventory Product Count:\t");
	else printf("\nUser %d purchase Inventory Product Count:\t", p->ID);
	for (int i=0; i< p->number_different_products; i++)
		printf("%d\t",p->products[i]->Count);
	printf("\n");
	return;
}

/* Purchase functions*/

p_Purchase generatePurchase (p_Inventory stock)
{
	if (stock==NULL)
	{
		printf("\nPurchase failed to create due to null pointer to inventory");
		return NULL;
	}
	p_Purchase p;
	
	int number_different_products = stock->number_different_products;
	p = malloc(sizeof(struct Purchase)+ (sizeof(struct Product *) * (number_different_products-1)));
	for (int i=0; i<stock->number_different_products; i++)
	{
		p->products[i]= malloc(sizeof(struct Product));
	}
	return p;
};

void populatePurchase (p_Inventory stock,
					   p_Purchase p)
{
	if (p == 0x0 || stock == 0x0)
	{
		printf("\nPurchase failed to populate due to null pointer to inventory or purchase");
		return ;
	}
	clock_t start = clock();
	clock_t finish = (clock()-start);
	srand((int) time(0)+(int) finish);
	int a = rand();
	int b = 0;
	
	for (int i = 0; i<stock->number_different_products; i++)
	{
		p->products[i]->ID = i;
		if (a/7) 	b = a % small_n;
		else if 	(a/11) b = a % medium_n;
		else if 	(a/13) b = a % large_n;
		else 	b = rand()%10;
		if (b > stock->products[i]->Count) b = stock->products[i]->Count;
		p->products[i]->Count = b;
		a = rand();
	}
	p->number_different_products = stock->number_different_products;
	return;
}

p_Purchase destroyPurchase (p_Purchase p)
{
	for (int i = 0; i < p->number_different_products; i++)
	{
		free(p->products[i]);
	}
	free(p);
	return NULL;
}

void displayPurchase (p_Purchase p)
{
	if (p==NULL)
	{
		printf("Display Purchase failed due to null pointer\n");
		return;
	}
	printf("\nPurchase Product ID:\t\t");
	for (int i=0; i< p->number_different_products; i++)
		printf("%d\t",p->products[i]->ID);
	printf("\nPurchase Product Count:\t");
	for (int i=0; i< p->number_different_products; i++)
		printf("%d\t",p->products[i]->Count);
	printf("\n");
	return;
}

/* Ledger functions*/

int stockremaining(p_Inventory stock,
				   p_Ledger ledger)
{
	if (stock==0x0 || ledger==0x0)
	{
		printf("One of the pointers does not exist");
		return -1;
	}
	int a = stock->number_different_products;
	for (int i = 0; i<a; i++)
	{
		if (stock->products[i]->Count == 0)
			return 0;
	}
	
	return 1;
}

p_Ledger generateLedger (p_Inventory stock,
						 int number_purchases)
{
	if (stock==0x0)
	{
		printf("Ledger failed to create due to null stock pointer\n");
		return NULL;
	}
	while (number_purchases<1)
	{
		printf("Enter a number for purchases greater than 0\n");
		scanf("%d",&number_purchases);
	}
	p_Ledger p;
	int temp = sizeof(struct Ledger) + sizeof(struct Purchase *) * (number_purchases - 1);
	p = malloc(temp);
	p->number_different_products=stock->number_different_products;
	p->number_purchases=number_purchases;
	for (int i=0; i<number_purchases; i++)
	{
		p->purchases[i] = generatePurchase(stock);
		p->purchases[i]->number_different_products = stock->number_different_products;
	}
	return p;
}

void populateLedger (p_Inventory stock,
					 p_Ledger p,
					 int ID)
{
	if (p == 0x0 || stock == 0x0)
	{
		printf("Ledger failed to populate due to null pointer to inventory or ledger");
		return;
	}
	for (int i = 0; i<p->number_purchases; i++) populatePurchase(stock, p->purchases[i]);
	p->ID=ID;
	return;
}

p_Inventory generateOutgoingInventory (p_Ledger ledger)
{
	if (ledger == 0x0)
	{
		printf("Outgoing Inventory failed to create due to null ledger pointer\n");
		return NULL;
	}
	p_Inventory p = generateInventory(ledger->number_different_products);
	p->ID = ledger->ID;
	int totals[ledger->number_different_products];
	for (int i=0; i<p->number_different_products;i++)
	{
		totals[i] = 0;
	}
	for (int i=0; i<ledger->number_purchases; i++)
	{
		for (int j=0; j<ledger->number_different_products; j++)
		{
			totals[j]= totals[j] + ledger->purchases[i]->products[j]->Count;
		}
	}
	for (int i=0; i<p->number_different_products;i++)
	{
		p->products[i]->ID = ledger->purchases[0]->products[i]->ID;
		p->products[i]->Count = totals[i];
	}
	return p;
}

p_Ledger destroyLedger (p_Ledger p)
{
	if (p==0x0)
	{
		return NULL;
	}
	for (int i = 0; i < p->number_purchases; i++)
	{
		destroyPurchase(p->purchases[i]);
	}
	free(p);
	return NULL;
}

void displayLedger (p_Ledger p)
{
	if (p==NULL)
	{
		printf("Display Ledger failed due to null pointer\n");
		return;
	}
	for (int i=0; i<p->number_purchases; i++)
	{
		printf("Purchase number:\t\t\t%d/%d",i+1,p->number_purchases);
		displayPurchase(p->purchases[i]);
		printf("\n");
	}
	return;
}

/* Doesn't work but may be mined for ideas later
 int totals[stock->number_different_products];
 for (int j=0;j<p->number_different_products;j++)
 {
 totals[j]=p->purchases[i]->products[j]->Count + p->Outgone->products[j]->Count;
 p->Outgone->products[j]->Count = totals [j] ;
 }
 
 
 int integerLengthCheck (int num)
 {
 int temp = num;
 int i=0;
 while (temp/10)
 {
 temp = temp/10;
 i++;
 }
 return i;
 }
 void displayInventory (p_Inventory p)
 {
 if (p==NULL)
 {
 printf("pointer does not exist");
 return;
 }
 
 char *number_buffer, *old_buffer, *new_buffer;
 int temp =  0;
 
 char a[13]="\nProduct ID:\t";
 for (int i=0; i< p->number_different_products; i++)
 {
 // convert number to string
 temp = p->products[i]->ID;
 number_buffer=malloc(sizeof (char) * integerLengthCheck(p->number_different_products));
 sprintf(number_buffer,"%d",temp);
 temp = (int) strlen(number_buffer);
 // concatanate new string from old string + number
 // path 1: first run
 switch (i) {
 case 0:
 new_buffer = malloc(sizeof(char) * (temp));
 sprintf(new_buffer, "%s\t",number_buffer);
 break;
 // path 2: second+ run
 default:
 old_buffer = new_buffer;
 free(new_buffer);
 new_buffer = malloc(sizeof(char) * (temp + strlen(old_buffer)));
 sprintf(new_buffer, "%s%s\t",old_buffer,number_buffer);
 free(old_buffer);
 break;
 }
 free(number_buffer);
 }
 char* b;
 temp = (int) strlen(new_buffer);
 b = malloc(sizeof(char) * temp);
 sprintf(b, "%s", new_buffer);
 free(new_buffer);
 
 char c[16] = "\nProduct Count:\t";
 for (int i=0; i< p->number_different_products; i++)
 {
 // convert number to string
 temp = p->products[i]->Count;
 number_buffer=malloc(sizeof (char) * integerLengthCheck(p->number_different_products));
 sprintf(number_buffer,"%d",temp);
 // concatanate new string from old string + number
 temp = (int) strlen(number_buffer);
 old_buffer = new_buffer;
 new_buffer = malloc(sizeof(char) * (temp + strlen(&old_buffer)));
 sprintf(new_buffer, "%s%s\t",old_buffer,number_buffer);
 free(number_buffer);
 free(old_buffer);
 }
 char d;
 temp = strlen(new_buffer);
 d = malloc(sizeof(char) * temp);
 sprintf(d, "%s", new_buffer);
 free(new_buffer);
 
 temp = (int) strlen(a) + (int) strlen(b) + (int) strlen(c) + (int) strlen(d);
 char buffer[temp];
 sprintf(buffer,"%s%s%s%s", a, b, c, d);
 printf("%s", buffer);
 return;
 }
 
 */



