#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
    double x, y;
    Point(double _x = 0, double _y = 0) : x(_x), y(_y) {}
};

struct Edge {
    Point a, b;
    Edge(Point _a, Point _b) : a(_a), b(_b) {}

    bool hasSameEndpoints(const Edge& other) const {
        bool matchNormal = (a.x == other.a.x && a.y == other.a.y && b.x == other.b.x && b.y == other.b.y);
        bool matchFlipped = (a.x == other.b.x && a.y == other.b.y && b.x == other.a.x && b.y == other.a.y);
        return matchNormal || matchFlipped;
    }
};

struct Triangle {
    Point p1, p2, p3;
    Triangle(Point _p1, Point _p2, Point _p3) : p1(_p1), p2(_p2), p3(_p3) {}
    
    bool isPointInsideCircle(Point p) const {
        double x1 = p1.x, y1 = p1.y;
        double x2 = p2.x, y2 = p2.y;
        double x3 = p3.x, y3 = p3.y;

        double commonDiv = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
        double centerX = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / commonDiv;
        double centerY = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / commonDiv;
        
        double rSquared = pow(x1 - centerX, 2) + pow(y1 - centerY, 2);
        double distToCenterSq = pow(p.x - centerX, 2) + pow(p.y - centerY, 2);
        
        return distToCenterSq < rSquared;
    }
};

vector<Triangle> constructDelaunay(vector<Point> inputCoords) {
    Point root1(-5000, -5000);
    Point root2(5000, -5000);
    Point root3(0, 5000);
    
    vector<Triangle> mesh;
    mesh.push_back(Triangle(root1, root2, root3));

    for (const auto& currentPt : inputCoords) {
        vector<Triangle> invalidTris;

        for (const auto& tri : mesh) {
            if (tri.isPointInsideCircle(currentPt)) {
                invalidTris.push_back(tri);
            }
        }

        vector<Edge> boundary;
        for (size_t i = 0; i < invalidTris.size(); ++i) {
            Triangle t = invalidTris[i];
            Edge sideList[3] = { Edge(t.p1, t.p2), Edge(t.p2, t.p3), Edge(t.p3, t.p1) };

            for (int e = 0; e < 3; e++) {
                bool isInternal = false;
                for (size_t j = 0; j < invalidTris.size(); j++) {
                    if (i == j) continue;
                    Triangle other = invalidTris[j];
                    Edge otherSides[3] = { Edge(other.p1, other.p2), Edge(other.p2, other.p3), Edge(other.p3, other.p1) };
                    for (int k = 0; k < 3; k++) {
                        if (sideList[e].hasSameEndpoints(otherSides[k])) isInternal = true;
                    }
                }
                if (!isInternal) boundary.push_back(sideList[e]);
            }
        }

        vector<Triangle> updatedMesh;
        for (const auto& tri : mesh) {
            bool toDelete = false;
            for (const auto& bad : invalidTris) {
                if (tri.p1.x == bad.p1.x && tri.p1.y == bad.p1.y && tri.p2.x == bad.p2.x) {
                    toDelete = true;
                    break;
                }
            }
            if (!toDelete) updatedMesh.push_back(tri);
        }
        mesh = updatedMesh;

        for (const auto& edge : boundary) {
            mesh.push_back(Triangle(edge.a, edge.b, currentPt));
        }
    }

    vector<Triangle> output;
    Point superVertices[3] = { root1, root2, root3 };
    
    for (const auto& tri : mesh) {
        bool usesSuper = false;
        for (int i = 0; i < 3; i++) {
            if ((tri.p1.x == superVertices[i].x && tri.p1.y == superVertices[i].y) ||
                (tri.p2.x == superVertices[i].x && tri.p2.y == superVertices[i].y) ||
                (tri.p3.x == superVertices[i].x && tri.p3.y == superVertices[i].y)) {
                usesSuper = true;
            }
        }
        if (!usesSuper) output.push_back(tri);
    }

    return output;
}

int main() {
    
    vector<Point> dataSet = {
        {20.5, 30.0}, {100.0, 5.5}, {50.2, 90.1}, {10.0, 10.0}, {60.0, 60.0}
    };

    vector<Triangle> finalMesh = constructDelaunay(dataSet);

    
    int counter = 1;
    for (const auto& t : finalMesh) {
        cout << "Triangle " << counter++ << " Points: "
             << "[" << t.p1.x << "," << t.p1.y << "] "
             << "[" << t.p2.x << "," << t.p2.y << "] "
             << "[" << t.p3.x << "," << t.p3.y << "]\n";
    }

    return 0;
}