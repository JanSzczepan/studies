#include <iostream>
#include <regex>
#include <cmath>

using namespace std;

struct Point {
    double x = 0;
    double y = 0;
};

struct Triangle {
    Point a;
    Point b;
    Point c;
    Point centerOfGravity;
    double side1 = 0;
    double side2 = 0;
    double side3 = 0;
    double circuit = 0;
    double area = 0;
    double circumscribedCircleRadius = 0;
};

bool isValidName(const string &name) {
    regex pattern("[A-Z][a-z]{2,}");
    return regex_match(name, pattern);
}

string getName(const string &prompt) {
    string name;

    while (true) {
        cout << prompt;
        cin >> name;
        if (!isValidName(name)) {
            cout << "Enter valid name!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    return name;
}

void welcomeUser() {
    string name = getName("Name: ");
    cout << "Welcome, " << name << "!" << endl;
}

double getNumber(const string &prompt) {
    double number;

    while (true) {
        cout << prompt;

        cin >> number;
        if (cin.fail()) {
            cout << "Enter valid number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else break;
    }

    return number;
}

Point getPoint(const string &prompt) {
    cout << prompt << endl;
    double x = getNumber("X: ");
    double y = getNumber("Y: ");
    return {x, y};
}

double calculateDistance(const Point &a, const Point &b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

bool isValidTriangle(const Point &a, const Point &b, const Point &c) {
    auto side1 = calculateDistance(a, b);
    auto side2 = calculateDistance(a, c);
    auto side3 = calculateDistance(b, c);

    return (side1 + side2 > side3 && side2 + side3 > side1 && side3 + side1 > side2);
}

Triangle getTriangleCoordinates() {
    while (true) {
        auto a = getPoint("Enter the coordinates of vertex A: ");
        auto b = getPoint("Enter the coordinates of vertex B: ");
        auto c = getPoint("Enter the coordinates of vertex C: ");

        if (isValidTriangle(a, b, c)) {
            return {a, b, c};
        } else {
            cout << "Enter valid coordinates!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double calculateTriangleCircuit(const Triangle &triangle) {
    return triangle.side1 + triangle.side2 + triangle.side3;
}


double calculateTriangleArea(const Triangle &triangle) {
    double s = triangle.circuit / 2;
    return sqrt(s * (s - triangle.side1) * (s - triangle.side2) * (s - triangle.side3));
}

Point calculateTriangleCenterOfGravity(const Triangle &triangle) {
    double x = (triangle.a.x + triangle.b.x + triangle.c.x) / 3;
    double y = (triangle.a.y + triangle.b.y + triangle.c.y) / 3;
    return {x, y};
}

double calculateCircumscribedCircleRadius(const Triangle &triangle) {
    return (triangle.side1 * triangle.side2 * triangle.side3) / (4 * triangle.area);
}

Triangle getTriangle() {
    auto triangle = getTriangleCoordinates();
    triangle.side1 = calculateDistance(triangle.a, triangle.b);
    triangle.side2 = calculateDistance(triangle.a, triangle.c);
    triangle.side3 = calculateDistance(triangle.b, triangle.c);
    triangle.circuit = calculateTriangleCircuit(triangle);
    triangle.area = calculateTriangleArea(triangle);
    triangle.centerOfGravity = calculateTriangleCenterOfGravity(triangle);
    triangle.circumscribedCircleRadius = calculateCircumscribedCircleRadius(triangle);

    return triangle;
}

void printTriangleData() {
    auto triangle = getTriangle();
    cout << "Triangle data:" << endl;
    cout << "Circuit: " << triangle.circuit << endl;
    cout << "Area: " << triangle.area << endl;
    cout << "Coordinates of the triangle's center of gravity: "
         << "(" << triangle.centerOfGravity.x << ", " << triangle.centerOfGravity.y << ")" << endl;
    cout << "Radius of the circle circumscribed by the triangle: " << triangle.circumscribedCircleRadius << endl;
}

int main() {
    welcomeUser();
    printTriangleData();

    return 0;
}
