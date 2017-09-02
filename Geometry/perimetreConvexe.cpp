#include <bits/stdc++.h>
using namespace std;

typedef long long Int;
const int oo = 1e9;
const Int OO = 1e18;

struct Point {
    int x, y;
};

int nbPoints;
const int MAX_NB_POINTS = 1e4;
Point points[MAX_NB_POINTS];
vector<Point> enveloppe;
int tailleEnveloppe;

Point pivot = {-1, -1};

bool trierCoord(Point a, Point b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

Int x3, x2, y3, y2, det;
bool trierPolaire(Point a, Point b) {
    x3 = (Int)a.x - pivot.x;
    y3 = (Int)a.y - pivot.y;
    x2 = (Int)b.x - pivot.x;
    y2 = (Int)b.y - pivot.y;
    det = (Int)x3 * y2 - y3 * x2;
    return det > 0;
}

Int dx, dy;
Int dist(Point a, Point b) {
    dx = (Int)a.x - b.x, dy = (Int)a.y - b.y;
    return dx * dx + dy * dy;
}

bool gauche(Point p, Point q, Point r) {
    return (Int)((Int)q.x - p.x) * ((Int)r.y - p.y) -
           ((Int)q.y - p.y) * ((Int)r.x - p.x) > 0;
}

void trouverEnveloppeConvexe() {
    sort(points, points+nbPoints, trierCoord);
    pivot = points[0];
    sort(points+1, points+nbPoints, trierPolaire);
    for(int i = 0; i < 3; i++) enveloppe.push_back(points[i]);
    Point p;
    for(int i = 3; i < nbPoints; i++) {
        p = enveloppe.back();
        enveloppe.pop_back();
        while(!gauche(enveloppe.back(), p, points[i])) {
            p = enveloppe.back();
            enveloppe.pop_back();
        }
        enveloppe.push_back(p);
        enveloppe.push_back(points[i]);
    }
    tailleEnveloppe = (int)enveloppe.size();
}

double calcPerimetre() {
    double perimetre = 0.0;
    for(int i = 0; i < tailleEnveloppe; i++) {
        Point p = enveloppe[i];
        Point q = enveloppe[(i+1)%tailleEnveloppe];
        Int cote = dist(p, q);
        perimetre += sqrt(cote);
    }
    return perimetre;
}

int main()
{
    scanf("%d", &nbPoints);
    for(int i = 0; i < nbPoints; i++)
        scanf("%d%d", &points[i].x, &points[i].y);

    if(nbPoints == 1) {
        printf("0");
        return 0;
    }

    if(nbPoints == 2) {
        printf("%.0lf", 2 * sqrt(dist(points[0], points[1])));
        return 0;
    }

    trouverEnveloppeConvexe();

    printf("%.0lf", calcPerimetre());
}
