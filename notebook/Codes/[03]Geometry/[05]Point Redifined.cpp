namespace geo {
    #define x real()
    #define y imag()
    #define setx(i) real(i)
    #define sety(i) imag(i)
    typedef complex<double> point;
    typedef point vec2;

    double dist(point a, point b) { return abs(b-a); }
    double dot(vec2 a, vec2 b) { return (conj(a) * b).x; }
    double cross(vec2 a, vec2 b) { return (conj(a) * b).y; }
    vec2 rotate90(vec2 a) { return point(-a.y, a.x); }
    double area(vec2 a, vec2 b) { return abs(cross(a,b)); }
    // double area(point a, point b, point c) { return area( getVec2(a,b), getVec2(a,c) ); }
    vec2 unitVec2(vec2 a) { return a/abs(a); }
    vec2 getVec2(point a, point b) { return b-a; }
    double angleBetween(vec2 a, vec2 b) { return acos(dot(a,b)/(abs(a) * abs(b))); } // In radian
}
