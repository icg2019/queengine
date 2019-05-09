#include <bits/stdc++.h>
#include <gl/glm.hpp>
#include "primitive.hpp"

class Rectangle {
    public:
        Primitive primitive;
        Rectangle::Rectangle(glm::vec2 a, glm::vec2 b, glm::vec2 c, glm::vec2 d);
        Rectangle::Rectangle(glm::vec2 a, glm::vec2 b);
        Rectangle::Rectangle(double width, double height);
}
