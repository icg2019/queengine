#include <bits/stdc++.h>
#include "../include/point_utils.hpp"

using namespace std;

int main(){
    pair<float, float> point = { 1.0, 0.0 };

    pair<float, float> rotated = rotate_point({0.0, 0.0}, acos(-1)/2.0, point);

    cout << rotated.first << " " << rotated.second;

    return 0;
}