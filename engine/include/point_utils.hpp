#include <bits/stdc++.h>

std::pair<float, float> rotate_point(std::pair<float, float> pivot, float angle, std::pair<float, float> point){
    double EPS = 1e-4;

    float angle_sin = sin(angle);
    float angle_cos = cos(angle);

    point.first -= pivot.first;
    point.second -= pivot.second;

    std::pair<float, float> rotated_point;

    rotated_point.first = point.first * angle_cos - point.second * angle_sin;
    rotated_point.second = point.first * angle_sin + point.second * angle_cos;

    rotated_point.first += pivot.first;
    rotated_point.second += pivot.second;

    fabs(rotated_point.first) < EPS ? rotated_point.first = 0.0 : rotated_point.first = rotated_point.first;
    fabs(rotated_point.second) < EPS ? rotated_point.second = 0.0 : rotated_point.second = rotated_point.second;

    return rotated_point;
}