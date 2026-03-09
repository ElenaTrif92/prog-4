#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <cstdio>
using namespace std;

struct Vector {
    double x, y, z;
};

struct Matrix3x3 {
    double m[3][3] = {0};
   
    Vector multiply(Vector v) {
        return {
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
        };
    }
};


Matrix3x3 matMultip(Matrix3x3 A, Matrix3x3 B) {
    Matrix3x3 C;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            for (int k=0; k<3; k++)
                C.m[i][j]+= A.m[i][k]*B.m[k][j];
    return C;
}

int main() {
    ifstream inputFile("monkey.obj");
    ofstream outputFile("result.obj");
    string line;

    if (!inputFile.is_open()) return 1;

    const double PI = 3.141592653589793;
    double rx = 45.0 * PI / 180.0;
    double ry = 27.0 * PI / 180.0;
    double rz = 10.0 * PI / 180.0;

    Matrix3x3 RotX = {{{1, 0, 0}, {0, cos(rx), -sin(rx)}, {0, sin(rx), cos(rx)}}};  
    Matrix3x3 RotY = {{{cos(ry), 0, sin(ry)}, {0, 1, 0}, {-sin(ry), 0, cos(ry)}}};
    Matrix3x3 RotZ = {{{cos(rz), -sin(rz), 0}, {sin(rz), cos(rz), 0}, {0, 0, 1}}};
   
    Matrix3x3 Scale = {{{1.5, 0, 0}, {0, -1.0, 0}, {0, 0, 1.0}}}; //scale po -1 y oska, upsidedown

    Matrix3x3 Matricata = matMultip(Scale, matMultip(RotZ, matMultip(RotY, RotX)));

    while (getline(inputFile, line)) {
        if (line.size() > 2 && line[0] == 'v' && line[1] == ' ') {
            
            Vector v;
       
            if (sscanf(line.c_str(), "v %lf %lf %lf", &v.x, &v.y, &v.z) == 3) {
                
                Vector newV = Matricata.multiply(v);
                
                outputFile << "v " << fixed << setprecision(4) << newV.x << " " << newV.y << " " << newV.z << "\n";
            }
            
        } 
        else outputFile << line << "\n";
    }

    inputFile.close();
    outputFile.close();
    return 0;
}