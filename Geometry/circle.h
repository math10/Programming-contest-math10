
// compute center of circle given three points
point ComputeCircleCenter(point a, point b, point c)
{
    b=(a+b)/2;
    c=(a+c)/2;
    point p;
    ComputeLineIntersection(b, b+(a-b).rotright(), c, c+(a-c).rotright(),p); // global
    return p;
}

struct circle
{
    point p ;  //  বৃত্তের কেন্দ্র
    double r ; // বৃত্তের  ব্যাসার্ধ
    circle() {}
    circle(point _p, double _r)
    {
        p = _p , r = _r ;
    }
    circle(point a,point b,point c)
    {
        p = ComputeCircleCenter(a,b,c); // global
        r = dis(p,a); // point.h
    }
    bool operator ==(circle v)
    {
        return (( p == v.p ) && EQ( r - v.r ) == 0 );
    }
    bool operator <(circle v)const
    {
        return ((p < v.p )||(p == v.p) && EQ( r - v.r ) < 0 );
    }
    double area() //  বৃত্তের  ক্ষেত্রফল
    {
        return pi*r*r;
    }
    double circumference() //বৃত্তের  পরিধি
    {
        return 2*pi*r;
    }
    // 5 way off / are away from
    // 4 circumscribed /outer cutting
    // 3 intersect
    // 2-cut inside/inscribed
    // 1 contains / includes
    int relationcircle(circle v)
    {
        double d = dis(p,v.p); // point
        if ( EQ( d - r - v.r ) >  0 ) return 5;
        if ( EQ( d - r - v.r ) == 0 ) return 4;
        double l = fabs( r - v.r );
        if ( EQ( d - r - v.r ) < 0 && EQ( d - l ) > 0 ) return 3;
        if ( EQ( d - l ) == 0) return 2;
        if ( EQ( d - l ) <  0) return 1;
    }
    // 0    __ বৃত্তের বাইরে
    // 1 __ বৃত্তের  উপরে অবস্থিত
    // 2 __  বৃত্তের ভিতরে
    int relation(point b) // বৃত্ত  ও   একটি বিন্দুর সম্পর্ক
    {
        double dst = dis(b,p); // point
        if ( EQ( dst - r ) < 0 ) return 2;
        if ( EQ( dst - r ) == 0 ) return 1;
        return 0;
    }
    void input()
    {
        p.input();
        scanf("%lf",&r);
    }
};
//যদি  ABC ত্রিভুজ গঠন করতে পারে তাহলে ABC এর  বহিবৃত্ত উৎপন্ন করে এমন Circle তৈরী করে ।
circle Circum_circle(point a,point b,point c)
{
    point center = ComputeCircleCenter(a,b,c); // global
    double  radius = dis(center,a); // point.h
    return circle(center,radius); // circle
}
//যদি  ABC ত্রিভুজ গঠন করতে পারে তাহলে ABC এর  অন্তবৃত্ত  উৎপন্ন করে এমন Circle তৈরী করে ।
circle Inscribed_circle(point a,point b,point c)
{
    line u , v ;
    double m = atan2( b.y - a.y , b.x - a.x ) , n = atan2( c.y - a.y , c.x - a.x );
    u.a = a ;
    u.b = u.a + ( point( cos((n+m)/2) , sin((n+m)/2) ) ); // point
    v.a = b ;
    m = atan2( a.y - b.y , a.x - b.x ) , n = atan2( c.y - b.y , c.x - b.x );
    v.b = v.a + ( point( cos( (n+m)/2 ) , sin( (n+m)/2) ) ); // point
    point center;
    ComputeLineIntersection(u.a,u.b,v.a,v.b,center); // global
    double radius = DistancePointSegment(a,b,center); // global
    return circle(center,radius); // circle
}
// দুইটা circle নিজেদের ছেদ করলে তাদের ছেদ বিন্দু return করে
int pointcrosscircle(circle a, circle v , point &p1 , point &p2 )
{
    int rel = a.relationcircle(v); // own
    if (rel == 1 || rel == 5) return 0;
    double d = dis(a.p,v.p); // point
    double l = ( d + ( a.r*a.r - v.r * v.r )/d )/2.00;
    double h = sqrt( a.r*a.r- l*l );
    p1 = a.p +  ( trunc((v.p - a.p),l) ) + ( trunc((v.p - a.p).rotleft(),h) ) ; // point
    p2 = a.p +  ( trunc((v.p - a.p),l) ) + ( trunc((v.p - a.p).rotright(),h)) ; // point
    if (rel == 2 || rel == 4)
    {
        return 1;
    }
    return 2;
}
// compute intersection of line through points a and b with
// circle centered at c with radius r > 0
vector<point> CircleLineIntersection(point a, point b, point c, double r)
{
    vector<point> ret;
    b = b-a;
    a = a-c;
    double A = dot(b,b) , B = dot(a,b) , C = dot(a,a) - r*r;
    double D = B*B - A*C;
    if (D < -EPS) return ret;
    ret.push_back(c+a+b*(-B+sqrt(D+EPS))/A);
    if (D > EPS)
        ret.push_back(c+a+b*(-B-sqrt(D))/A);
    return ret;
}

// compute intersection of circle centered at a with radius r
// with circle centered at b with radius R
vector<point> CircleCircleIntersection(point a, point b, double r, double R)
{
    vector<point> ret;
    double d = dis(a,b);
    if (d > r+R || d+min(r, R) < max(r, R)) return ret;
    double x = (d*d-R*R+r*r)/(2*d);
    double y = sqrt(r*r-x*x);
    point v = (b-a)/d;
    ret.push_back(a+v*x + (v.rotleft())*y);
    if (y > 0)
        ret.push_back(a+v*x -(v.rotleft())*y);
    return ret;
}
// circle এর বাহিরের কোন বিন্দু q থেকে circle এর উপর স্পর্শক লাইন(u,v) return করে
int tangentline(circle c,point q , line &u , line &v )
{
    int x = c.relation(q); // own
    if (x == 2 ) return 0;
    if (x == 1 )
    {
        u = line( q , q + ( (q-c.p).rotleft() )  ); // point,line
        v = u;
        return 1;
    }
    double d = dis(c.p,q); // point
    double l = (c.r*c.r)/d;
    double h = sqrt( c.r*c.r - l*l );
    u = line( q , c.p +  ( trunc((q-c.p),l) ) + ( trunc((q-c.p).rotleft(),h) ) ); // point
    v = line( q , c.p +  ( trunc((q-c.p),l) ) + ( trunc((q-c.p).rotright(),h)) ); // point
    return 2 ;
}

struct tmpLine{
    db a,b,c;
};

void tangents (point c, double r1, double r2, vector<tmpLine> &ans) {
	double r = r2 - r1;
	double z = sqr(c.x) + sqr(c.y);
	double d = z - sqr(r);
	if (d < -EPS)  return;
	d = sqrt (abs (d));
	tmpLine l;
	l.a = (c.x * r + c.y * d) / z;
	l.b = (c.y * r - c.x * d) / z;
	l.c = r1;
	ans.push_back (l);
}

vector<line> tangents (circle a, circle b) {
	vector<tmpLine> ans;
	vector<line>ret;
	for (int i=-1; i<=1; i+=2)
		for (int j=-1; j<=1; j+=2)
			 tangents(b.p - a.p,a.r*i,b.r*j,ans);
	for (size_t i=0; i<ans.size(); ++i)
		ans[i].c -= ans[i].a * a.p.x + ans[i].b * a.p.y;
    forstl(it,ans){
        ret.pb(line(it->a,it->b,it->c));
    }
	return ret;
}
