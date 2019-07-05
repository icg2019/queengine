#include <bits/stdc++.h>

std::pair<float, float> rotate_point(std::pair<float, float> pivot, float angle, std::pair<float, float> point){
    float angle_sin = sin(angle);
    float angle_cos = cos(angle);

    point.first -= pivot.first;
    point.second -= pivot.second;

    std::pair<float, float> rotated_point;

    rotated_point.first = point.first * angle_cos - point.second * angle_sin;
    rotated_point.second = point.first * angle_sin + point.second * angle_cos;

    rotated_point.first += pivot.first;
    rotated_point.second += pivot.second;

    return rotated_point;
}