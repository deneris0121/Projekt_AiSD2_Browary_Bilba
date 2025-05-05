#ifndef CALOSC_H
#define CALOSC_H
#include <vector>
#include <fstream>
#include "Pole.h"
using namespace std;
int uruchomProgram();
vector<Pole> polaICwiartkizPliku(std::istream& in, int iloscp);
#endif