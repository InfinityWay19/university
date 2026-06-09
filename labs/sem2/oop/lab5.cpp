#include <iostream>
#include <cmath>

class Triangle;
class Circle;

struct Point {
    double x, y;
};

class Circle {
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    friend double getArea(const Circle& c);
    friend void checkFitting(const Circle& c, const Triangle& t);
};

class Triangle {
private:
    Point p1, p2, p3;

    double sideLength(Point a, Point b) const {
        return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
    }

public:
    Triangle(Point a, Point b, Point c) : p1(a), p2(b), p3(c) {}

    friend double getArea(const Triangle& t);
    friend void checkFitting(const Circle& c, const Triangle& t);
};

// реализация дружественных функций
double getArea(const Circle& c) {
    return M_PI * c.radius * c.radius;
}

double getArea(const Triangle& t) {
    double a = t.sideLength(t.p1, t.p2);
    double b = t.sideLength(t.p2, t.p3);
    double sideC = t.sideLength(t.p3, t.p1);

    double p = (a + b + sideC) / 2.0; 
    return std::sqrt(p * (p - a) * (p - b) * (p - sideC)); 
}

void checkFitting(const Circle& c, const Triangle& t) {
    double a = t.sideLength(t.p1, t.p2);
    double b = t.sideLength(t.p2, t.p3);
    double sideC = t.sideLength(t.p3, t.p1);

    double S = getArea(t);
    double p = (a + b + sideC) / 2.0;

    double r_inscribed = S / p;
    double R_circumscribed = (a * b * sideC) / (4.0 * S);
    double epsilon = 0.001; 

    std::cout << "\n--- Результаты проверки геометрии ---" << std::endl;
    std::cout << "Радиус круга: " << c.radius << std::endl;
    std::cout << "Требуемый радиус вписанной окружности: " << r_inscribed << std::endl;
    std::cout << "Требуемый радиус описанной окружности: " << R_circumscribed << std::endl;

    if (std::abs(c.radius - r_inscribed) < epsilon) {
        std::cout << "Итог: Данный круг можно ВПИСАТЬ в этот triangle." << std::endl;
    } 
    else if (std::abs(c.radius - R_circumscribed) < epsilon) {
        std::cout << "Итог: Данный круг можно ОПИСАТЬ около этого треугольника." << std::endl;
    } 
    else {
        std::cout << "Итог: Круг не является ни вписанным, ни описанным." << std::endl;
    }
}

int main() {
    std::cout << "=== Задача 5: Круг и Треугольник ===" << std::endl;

    Point a = {0.0, 0.0};
    Point b = {4.0, 0.0};
    Point comp = {0.0, 3.0}; 
    Triangle myTriangle(a, b, comp);
    Circle myCircle(1.0); // радиус 1 как раз впишется в этот треугольник

    std::cout << "Площадь круга: " << getArea(myCircle) << std::endl;
    std::cout << "Площадь треугольника: " << getArea(myTriangle) << std::endl;

    checkFitting(myCircle, myTriangle);

    return 0;
}