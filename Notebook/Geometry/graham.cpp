struct point{
    int x,y;
    point() {}
    point(int X, int Y):x(X), y(Y) {}
};

point pivot;

inline int distsqr(const point &a, const point &b){
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

inline double dist(const point &a, const point &b){
    return sqrt(distsqr(a, b));
}

inline int cross(const point &a, const point &b, const point &c){
    return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}

bool angleCmp(const point &self, const point &that){
    int t = cross(pivot, that, self);
    if(t < 0) return true;
    if(t == 0) return (distsqr(pivot, self) < distsqr(pivot, that));
    return false;
}

vector<point> graham(vector<point> p){
    for(int i = 0; i < p.size(); ++i){
        if(p[i].y < p[0].y || (p[i].y == p[0].y && p[i].x < p[0].x))
        swap(p[0], p[i]);
    }
    pivot = p[0];
    sort(p.begin(), p.end(), angleCmp);

    vector<point> chull(p.begin(),p.begin() + 3);

    for(int i = 3; i < p.size(); ++i){
        while(chull.size() >= 2 && cross(chull[chull.size()-2],chull[chull.size()-1],p[i]) <= 0)
            chull.erase(chull.end() - 1);
        chull.push_back(p[i]);
    }

    return chull;
}
