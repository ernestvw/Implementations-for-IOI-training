struct Point {
	int x, y;
	Point operator - (Point b){
		return (Point){x - b.x, y - b.y};
	}
	int croix(Point b){
		return x * b.y - y * b.x;
	}
	double dist(Point b){
		return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y));
	}
	double norme(){
		return sqrt(x*x+y*y);
	}
};

int nbPoints;
const int MAX_NB_POINTS = 300001;
Point points[MAX_NB_POINTS];
vector<Point> enveloppe;
int tailleEnveloppe;

Point pivot = {-1, -1};

bool trierCoord(Point a, Point b){
	return a.y == b.y ? a.x < b.x : a.y < b.y;
}

int x3, y3, x2, y2, det;
bool trierPolaire(Point a, Point b){
	Point A = a - pivot;
	Point B = b - pivot;
	return A.croix(B) > 0;
}

bool gauche(Point p, Point q, Point r){
	return (q.x-p.x)*(r.y-p.y)-(q.y-p.y)*(r.x-p.x)>0;
}

double distSegPt(Point A, Point B, Point P){
	Point AB=B-A;
	Point AP=P-A;
	double prdt=(double)AB.croix(AP);
	return prdt/AB.norme();
}

void graham(){
	sort(points, points+nbPoints, trierCoord);
	pivot=points[0];
	sort(points+1, points+nbPoints, trierPolaire);
	for(int i=0;i<3;i++) enveloppe.push_back(points[i]);
	Point p;
	for(int i=3;i<nbPoints;i++){
		p=enveloppe.back();
		enveloppe.pop_back();
		while(!gauche(enveloppe.back(), p, points[i])){
			p=enveloppe.back();
			enveloppe.pop_back();
		}
		enveloppe.push_back(p);
		enveloppe.push_back(points[i]);
	}
	tailleEnveloppe=enveloppe.size();
}
