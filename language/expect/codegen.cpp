#include <cmath>

class Point {
public:
    int x;
    int y;

    // Constructor
    Point(int x_val, int y_val) : x(x_val), y(y_val) {}

    // Calculate the distance between two points
    double distance(const Point& other) const {
        int x_diff = x - other.x;
        int y_diff = y - other.y;
        return std::sqrt(x_diff * x_diff + y_diff * y_diff);
    }

    // Calculate the distance from the origin
    double distance_from_origin() const {
        return this->distance(Point(0, 0));
    }

    // Translate the point by dx and dy
    void translate(int dx, int dy) {
        x += dx;
        y += dy;
    }
};

// Add two integers
int add_int(int a, int b) {
    return a + b;
}

// Add two points
Point add_point(const Point& a, const Point& b) {
    return Point(a.x + b.x, a.y + b.y);
}

// Main function
double main_point() {
    Point p1(1, 2);
    Point p2(4, 6);
    Point p3 = add_point(p1, p2);
    p3.translate(1, 1);
    return p3.distance_from_origin();
}
