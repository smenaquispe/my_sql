#ifndef FIND_POSITIONS
#define FIND_POSITIONS

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<int> findPositions(vector<string> subVec, vector<string> mainVec) {
    vector<int> positions;
    for (int i = 0; i < subVec.size(); i++) {
        auto it = find(mainVec.begin(), mainVec.end(), subVec[i]);
        if (it != mainVec.end()) {
            positions.push_back(distance(mainVec.begin(), it));
        }
    }
    return positions;
}


#endif