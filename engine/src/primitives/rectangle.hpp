#include <bits/stdc++.h>
#include "primitive.hpp"
#include <glm/glm.hpp>


class Rectangle {
    public:
        Primitive primitive;
        Rectangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d);
        Rectangle(glm::vec2 a, glm::vec2 b);
        Rectangle(double width, double height);
};
