#ifndef IS_SUBSET
#define IS_SUBSET

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool isSubset(vector<string> subVec, vector<string> mainVec) {

    sort(subVec.begin(), subVec.end());
    sort(mainVec.begin(), mainVec.end());

    // Verificar si todos los elementos de subVec están en mainVec
    return includes(mainVec.begin(), mainVec.end(), subVec.begin(), subVec.end());
}

#endif