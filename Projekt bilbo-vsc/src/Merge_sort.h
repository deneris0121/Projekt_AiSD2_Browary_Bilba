#ifndef MERGE_SORT_H
#define MERGE_SORT_H	
#include<vector>
#include"Wezel.h"

using namespace std;

void mergeSort(vector<Wezel>& punkty, int lewy, int prawy, Wezel ref);
bool porownanieSkrajnychPunktow(const Wezel& a, const Wezel& b);
#endif

