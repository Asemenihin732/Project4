#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <math.h>
#include <time.h>

float M_PI = 3.14159265358979323846;
// Base abstract class for 3D curves
class Curve3D {
public:
    virtual double getRadius() const = 0;
    virtual double getTangent() const = 0;
    virtual double getPoint(double t) const = 0;
    virtual double getDerivative(double t) const = 0;
};

// Derived class for circles
class Circle : public Curve3D {
private:
    double radius;
public:
    Circle(double radius) : radius(radius) {}

    double getRadius() const override {
        return radius;
    }

    double getTangent() const override {
        return 2 * M_PI * radius;
    }

    double getPoint(double t) const override {
        double x = radius * cos(t);
        double y = radius * sin(t);
        return sqrt(x * x + y * y);
    }

    double getDerivative(double t) const override {
        return cos(t);
    }
};

// Derived class for ellipses
class Ellipse : public Curve3D {
private:
    double majorAxis;
    double minorAxis;
public:
    Ellipse(double majorAxis, double minorAxis) : majorAxis(majorAxis), minorAxis(minorAxis) {}

    double getRadius() const override {
        return 0.5 * (majorAxis + minorAxis);
    }

    double getTangent() const override {
        return 2 * M_PI * sqrt((majorAxis * majorAxis + minorAxis * minorAxis) / 2);
    }

    double getPoint(double t) const override {
        double x = majorAxis * cos(t);
        double y = minorAxis * sin(t);
        return sqrt(x * x + y * y);
    }

    double getDerivative(double t) const override {
        return cos(t);
    }
};

// Derived class for 3D helixes
class Helix : public Curve3D {
private:
    double radius;
    double pitch;
public:
    Helix(double radius, double pitch) : radius(radius), pitch(pitch) {}

    double getRadius() const override {
        return radius;
    }

    double getTangent() const override {
        return 2 * M_PI * radius;
    }

    double getPoint(double t) const override {
        double x = radius * cos(t);
        double y = radius * sin(t);
        double z = pitch * t;
        return sqrt(x * x + y * y + z * z);
    }

    double getDerivative(double t) const override {
        return cos(t);
    }
};

int main() {
    // Populate container with random objects of different curves
    std::vector<Curve3D*> curves;
    srand(time(NULL));
    int count_for_populate_container = rand()%15+1;
    printf("ccc: %d", count_for_populate_container);
    for (int i = 1; i <= count_for_populate_container; i++) {
        if(i==1 || i==2 || i==3 || i==4 || i==5)
            curves.push_back(new Circle(rand() % 15 + 1));
        if (i == 6 || i == 7 || i == 8 || i == 9 || i == 10)
            curves.push_back(new Ellipse(rand() % 15+1, rand() % 15+1));
        if (i == 11 || i == 12 || i ==13 || i == 14 || i == 15)
            curves.push_back(new Helix(rand() % 15+1, rand() % 15+1));
    }

    // Print coordinates of points and derivatives of all curves at t=PI/4
    double t = M_PI / 4;
    for (const auto& curve : curves) {
        std::cout << "Curve Type: " << typeid(*curve).name() << std::endl;
        std::cout << "Point at t=PI/4: " << curve->getPoint(t) << std::endl;
        std::cout << "Derivative at t=PI/4: " << curve->getDerivative(t) << std::endl;
        std::cout << std::endl;
    }

    // Populate second container with circles from the first container
    std::vector<Circle*> circles;
    for (auto curve : curves) {
        if (typeid(*curve) == typeid(Circle)) {
            circles.push_back(static_cast<Circle*>(curve));
        }
    }

    // Sort the second container in ascending order of circle's radii
    std::sort(circles.begin(), circles.end(), [](const Circle* c1, const Circle* c2) {
        return c1->getRadius() < c2->getRadius();
        });

    // Compute the total sum of radii of all curves in the second container
    double totalSum = 0.0;
    for (const auto& circle : circles) {
        totalSum += circle->getRadius();
    }

    std::cout << "Total sum of radii: " << totalSum << std::endl;

    // Clean up memory
    for (auto curve : curves) {
        delete curve;
    }

        curves.clear();

    return 0;
}
