#include <stdio.h>
#include <stdlib.h>

enum body {HEAD, UBDY, HAND, LEG_, FOOT};
#define NUMOFITEMS 13

int count = 0;

void dressItem(int part, char *name) {

	static const char *BODY_STRING[] = { "kafa ", "govde", "el   ", "bacak", "ayak " };

	
	if (/*?*/) {

		printf("%2d. \t\t\t\t\t--> Saglik calisanlarina sonsuz tesekkurler!..\n", /*?*/);
	}
	printf("%2d. (%s) %s ", /*?*/, BODY_STRING[/*?*/], /*?*/);
	if (/*?*/) {

		printf("\t--> Goreve hazirim!\n");
	}
	else if (/*?*/) {

		printf("\t--> Kalan oge sayisi: %2d\n", /*?*/);
	}
	else {

		printf("\n");
	}
	
}

void funcHEAD(void p) {

	dressItem(/*?*/, "YuzDezenfektani          ");
	dressItem(/*?*/, "SaglikMaskesi            ");
	dressItem(/*?*/, "Bone                     ");
	dressItem(/*?*/, "KoruyucuPlastikYuzMaskesi");
}

void funcUBDY(void p) {

	dressItem(/*?*/, "Atlet                    ");
	dressItem(/*?*/, "Gomlek                   ");
	dressItem(/*?*/, "Tulum                    ");
}

void funcHAND(void p) {

	dressItem(/*?*/, "ElDezenfektani           ");	
	dressItem(/*?*/, "Eldiven                  ");
}

void funcLEG_(void p) {

	dressItem(/*?*/, "Pantolon                 ");
	dressItem(/*?*/, "Kemer                    ");
}

void funcFOOT(void p) {

	dressItem(/*?*/, "Corap                    ");
	dressItem(/*?*/, "Ayakkabi                 ");
}

int main(int argc, char *argv[]) {
	
	return 0;
}