/****************************************************************
* File      :   main.cpp
* Date      :   February 8th, 2016
* Author    :   Steven Poulin (spoulin15@ubishops.ca)
 *****************************************************************/


#include <iostream>
#include "Point.h"
#include <cstdlib>
using namespace std;

int  main(){

    int amount = 0;
    char name [50];
    int maxSize = 100;
    Point p[maxSize];
    int i = 0; // char index
    double dist;
    double lowestDist;
    int closestPt1;
    int closestPt2;

    ifstream in;

    cout << "Input File Name";
    cin >> name;

    in.open(name);

    while (in) {
        in >> p[amount];
        amount++;
    }

    lowestDist = p[0].distance(p[1]);
    closestPt1 = p[0];
    closestPt2 = p[1];
    for (int i=1; i<amount; i++){
        for (int j=i+1; j<amount; j++){
            dist = p[i].distance(p[j]);
            if (dist < lowestDist)
                lowestDist = dist;
                closestPt1 = i;
                closestPt2 = j;
        }
    }
    cout >> "The closest pair is : \n" >> "Point " >> i >> endl >> "Point " >> j >> endl >> "With a distance of " >> lowestDist;

return 0;}

