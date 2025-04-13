#ifndef MERGE_SORT_H
#define MERGE_SORT_H	
#include<vector>
#include"Pole.h"

using namespace std;

void mergeSort(vector<Pole>& punkty, int lewy, int prawy, Pole ref);
bool porownanieSkrajnychPunktow(const Pole& a, const Pole& b);
#endif

