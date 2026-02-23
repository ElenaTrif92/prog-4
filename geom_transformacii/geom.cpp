#include <bits/stdc++.h>

using namespace std;

struct Tocka {
    double x, y, z;
    Tocka(double x = 0, double y = 0, double z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

struct Kvadrat {
    Tocka t1, t2, t3, t4;
    Kvadrat(Tocka t1, Tocka t2, Tocka t3, Tocka t4) {
        this->t1 = t1;
        this->t2 = t2;
        this->t3 = t3;
        this->t4 = t4;
    }
};

void pecatiKvadrat(const string& naslov, const Kvadrat& k) {
    cout << "--- " << naslov << " ---" << endl;
    cout << fixed << setprecision(2);
    cout << "T1: (" << k.t1.x << ", " << k.t1.y << ", " << k.t1.z << ")" << endl;
    cout << "T2: (" << k.t2.x << ", " << k.t2.y << ", " << k.t2.z << ")" << endl;
    cout << "T3: (" << k.t3.x << ", " << k.t3.y << ", " << k.t3.z << ")" << endl;
    cout << "T4: (" << k.t4.x << ", " << k.t4.y << ", " << k.t4.z << ")" << endl;
    cout << "---------------------------" << endl << endl;
}

void pomestiDesno(Kvadrat &k) {
    k.t1.x += 2.0;
    k.t2.x += 2.0;
    k.t3.x += 2.0;
    k.t4.x += 2.0;
}

void rotiraj45(Kvadrat &k) {
    double kut = 45.0 * M_PI / 180.0;
    double s = sin(kut);
    double c = cos(kut);

   
    double cx = (k.t1.x + k.t2.x + k.t3.x + k.t4.x) / 4.0;
    double cy = (k.t1.y + k.t2.y + k.t3.y + k.t4.y) / 4.0;

    
    double x1 = k.t1.x - cx; double y1 = k.t1.y - cy;
    k.t1.x = x1 * c - y1 * s + cx;
    k.t1.y = x1 * s + y1 * c + cy;

    
    double x2 = k.t2.x - cx; double y2 = k.t2.y - cy;
    k.t2.x = x2 * c - y2 * s + cx;
    k.t2.y = x2 * s + y2 * c + cy;


    double x3 = k.t3.x - cx; double y3 = k.t3.y - cy;
    k.t3.x = x3 * c - y3 * s + cx;
    k.t3.y = x3 * s + y3 * c + cy;

    double x4 = k.t4.x - cx; double y4 = k.t4.y - cy;
    k.t4.x = x4 * c - y4 * s + cx;
    k.t4.y = x4 * s + y4 * c + cy;
}

void homotetija(Kvadrat &k) {
    double faktor = 2.0;
    double cx = (k.t1.x + k.t2.x + k.t3.x + k.t4.x) / 4.0;
    double cy = (k.t1.y + k.t2.y + k.t3.y + k.t4.y) / 4.0;
    double cz = (k.t1.z + k.t2.z + k.t3.z + k.t4.z) / 4.0;

    k.t1.x = cx + (k.t1.x - cx) * faktor; k.t1.y = cy + (k.t1.y - cy) * faktor; k.t1.z = cz + (k.t1.z - cz) * faktor;
    k.t2.x = cx + (k.t2.x - cx) * faktor; k.t2.y = cy + (k.t2.y - cy) * faktor; k.t2.z = cz + (k.t2.z - cz) * faktor;
    k.t3.x = cx + (k.t3.x - cx) * faktor; k.t3.y = cy + (k.t3.y - cy) * faktor; k.t3.z = cz + (k.t3.z - cz) * faktor;
    k.t4.x = cx + (k.t4.x - cx) * faktor; k.t4.y = cy + (k.t4.y - cy) * faktor; k.t4.z = cz + (k.t4.z - cz) * faktor;
}

int main() {
    ifstream file("file.txt");
    string line;
    vector<Tocka> vertices;

    if (file.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            string prefix;
            ss >> prefix;
            if (prefix == "v") {
                double x, y, z;
                ss >> x >> y >> z;
                vertices.push_back(Tocka(x, y, z));
            }
        }
        file.close();
    }

   
    if (vertices.size() >= 4) {
        Kvadrat mojKvadrat(vertices[0], vertices[1], vertices[2], vertices[3]);
        
        pecatiKvadrat("Pocetok", mojKvadrat);

        pomestiDesno(mojKvadrat);
        pecatiKvadrat("Translacija desno za 2", mojKvadrat);

        rotiraj45(mojKvadrat);
        pecatiKvadrat("rotacija za 45", mojKvadrat);

        homotetija(mojKvadrat);
        pecatiKvadrat("Skaliranje pati 2", mojKvadrat);

        ofstream outFile("output.txt");
        if (outFile.is_open()) {
            outFile << "v " << mojKvadrat.t1.x << " " << mojKvadrat.t1.y << " " << mojKvadrat.t1.z << endl;
            outFile << "v " << mojKvadrat.t2.x << " " << mojKvadrat.t2.y << " " << mojKvadrat.t2.z << endl;
            outFile << "v " << mojKvadrat.t3.x << " " << mojKvadrat.t3.y << " " << mojKvadrat.t3.z << endl;
            outFile << "v " << mojKvadrat.t4.x << " " << mojKvadrat.t4.y << " " << mojKvadrat.t4.z << endl;
            outFile.close();
            cout << "rezultati zapisani vo output.txt " << endl;
        }
    }
    else {
        cout << "Greska" << endl;
    }

    return 0;
}