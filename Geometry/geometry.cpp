//this file might contain all kinds of cool geometry stuff
//...in the future

//|-------- |---------| |---------| |
//|         |         | |         | |
//|         |         | |         | |
//|         |         | |         | |
//|-------- |---------| |---------| |-------
#include <iostream>

using namespace std;

typedef pair<int, int> v;
#define x first
#define y second
typedef pair<int, int> p;

int ccw(v v1, v v2){
	//clockwise/counterclockwise test, 1=clockwise, -1 counterclockwise, 0 equal
	int s = ((v1.x*v2.y)-(v1.y*v2.x));
	if(s>0)
		return -1;
	else if(s<0)
		return 1;
	else
		return 0;
}

int ccw(p a, p b, p c){
	v v1 = {b.x-a.x, b.y-a.y};
	v v2 = {c.x-b.x, c.y-b.y};
	return ccw(v1, v2);
}

bool intersect(p a, p b, p c, p d){
	//given the four endpoints of two lines
	if((ccw(a, b, c)!=ccw(a, b, d))&&(ccw(c, d, a)!=ccw(c, d, b))){
		//if the turns abc and abd have opposite direction, and so do cda and cdb
		return 1;
	} else {
		return 0;
	}
}

int main(){
	p a = {0, 0}, b = {1, 0}, c = {1, 1};
	cout << ccw(a, b, c) << endl;
	p d = {0, 1};
	cout << intersect(a, c, b, d) << endl; //if the two lines are in a crossed formation
	cout << intersect(a, b, c, d) << endl; //parallel formation
	return 0;
}
