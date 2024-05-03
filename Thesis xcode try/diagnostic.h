//
//  diagnostic.h
//  Thesis xcode try
//
//  Created by Endani Munyai
//

#ifndef diagnostic_h
#define diagnostic_h

#include <stdio.h>
#include "products.h"
long memoryProduct(p_Product p);
long memoryInventory (p_Inventory p);
long memoryPurchase (p_Purchase p);
long memoryLedger (p_Ledger p);

void createstruct(int input,
				  p_Inventory p,
				  p_Ledger q);
void populatestruct(p_Inventory p,
					p_Ledger q,
					p_Inventory r);
void displaystruct(p_Inventory p,
				   p_Ledger q);
void displaystructs(p_Inventory p,
				   p_Ledger q,
				   p_Inventory r);
void destroystruct (p_Inventory p,
					p_Ledger q,
					p_Inventory r );

#endif /* diagnostic_h */
