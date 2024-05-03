//
//  main.c
//  Thesis xcode try
//
//  Created by Endani Munyai
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "products.h"
#include "diagnostic.h" 

int main(int argc, const char * argv[]) {
	clock_t start = clock();
	int input = 10;
	printf("\nMemory taken: %ld",sizeof(int));
	do
	{
		clock_t cycle = clock();
		printf("\nInput number:\t%d",input);
		printf("\nInventory functions");
		p_Inventory p, r;
		p_Ledger q;
		p = generateInventory(input);
		q = generateLedger(p, input);
		populateInventory(p);
		populateLedger(p, q, input);
		r=generateOutgoingInventory(q);
		printf("\nFinal display\n");
		displaystructs(p, q, r);
		printf("\nFinal display for Input number:\t%d\n",input);
		cycle = clock() - cycle;
		printf("\nClock cycles taken:\t\t\t%ld",cycle);
		printf("\nApproximate time taken:\t\t%f\n",(double) cycle/CLOCKS_PER_SEC);
		if (input>32) input = -1; // default is 4096
		else
		{
			double i= input *1.1;
			input = i;
		};
	} while (input != -1);
	clock_t finish = (clock()-start);
	printf("\nClock speed:\t\t\t\t%i",CLOCKS_PER_SEC);
	printf("\nClock cycles taken:\t\t\t%ld",finish);
	printf("\nAproximate time taken:\t\t%f\n",(double) finish/CLOCKS_PER_SEC);
	return input;
}
