struct line
{
    point a , b ;
    line(point _a , point _b )
    {
        a = _a , b = _b ;
    }
    line() {}
    // ** ভুমির সাথে  থিটা কোণে  নতুন রেখা উৎপন্ন  করে এবং থিটা রেডিয়ান  এ হতে হবে .
    line(point p,double theta)
    {
        a = p;
        if ( EQ( theta - pi/2.00 ) == 0 ) b = a + point(0,1);
        else b= a + point( 1 , tan( theta ) );
    }
    //ax+by+c=0 ,a,b,c দেয়া আছে তার জন্য রেখার দুইটা বিন্দু তৈরি করে
    line(double _a,double _b,double _c)
    {
        if ( EQ( _a ) == 0)
        {
            a = point(0,-_c/_b);
            b = point(1,-_c/_b);
        }
        else if (EQ(_b)==0)
        {
            a = point(-_c/_a,0);
            b = point(-_c/_a,1);
        }
        else
        {
            a = point(0,-_c/_b);
            b = point(1,(-_c-_a)/_b);
        }
    }
    void input()
    {
        a.input() ;
        b.input();
    }
};
// dont know the usage :p
point lineprog(line l,point p)
{
    double d = (l.b - l.a).x * (l.b - l.a).x + (l.b - l.a).y * (l.b - l.a).y ;
    return l.a + ((l.b-l.a)*(dot((l.b-l.a),(p-l.a))/d) );
}
//প্রতিবিম্ব বিন্দু /  Shadow point
point symmetrypoint(line l,point p)
{
    point q = lineprog(l,p);
    return point(2 * q.x - p.x , 2 * q.y - p.y );
}
// p বিন্দুটা  l segment এর উপর আছে কিনা
bool pointonseg(line l,point p)
{
    return EQ(cross((p - l.a),l.b - l.a))==0&&EQ(dot((p - l.a),p - l.b))<=0;
}
// একটি বিন্দু থেকে লাইন এর লম্বদূরত্ব
double dispointtoline(line l,point p)
{
    return fabs(cross((p-l.a),(l.b-l.a)))/dis(l.a,l.b);
}
//ভুমির সাথে কত ডিগ্রী কোনে রেখাটি  অবস্থিত
// return করতেছে রেডিয়ানে  //   angle 0 <= angle < pi
double angle(line l)
{
    double k = atan2(l.b.y-l.a.y,l.b.x-l.a.x);
    if (EQ(k) < 0)k += pi;
    if (EQ(k-pi) == 0)k -= pi;
    return k;
}
// project point c onto line through a and b
// assuming a != b
point ProjectPointLine(point a, point b, point c)
{
    return a + (b-a)*dot((c-a),b-a) / dot((b-a),b-a);
}


// project point c onto line segment through a and b
point ProjectPointSegment(point a, point b, point c)
{
    double r = dot((b-a),b-a);
    if (fabs(r) < EPS) return a;
    r = dot((c-a),b-a)/r;
    if (r < 0) return a;
    if (r > 1) return b;
    return a + (b-a)*r;
}

// compute distance from c to segment between a and b
double DistancePointSegment(point a, point b, point c)
{
    return dis(c,ProjectPointSegment(a, b, c) ); // global
}
// determine if lines from a to b and c to d are parallel or collinear
bool LinesParallel(point a, point b, point c, point d)
{
    return fabs( cross((b-a),c-d)) < EPS;
}

bool LinesCollinear(point a, point b, point c, point d)
{
    return LinesParallel(a, b, c, d) // global
           && fabs( cross((a-b), a-c) ) < EPS
           && fabs( cross((c-d),c-a) ) < EPS;
}
// compute intersection of line passing through a and b
// with line passing through c and d, assuming that unique
// intersection exists; for segment intersection, check if segments intersect first
// **use LinesParallel and LinesColliner to detect wether they intersect
bool ComputeLineIntersection(point a, point b, point c, point d,point &p)
{
    if(LinesCollinear(a,b,c,d) || LinesParallel(a,b,c,d)) return false;
    b = b - a ;
    d = c - d ;
    c = c - a ;
   // assert( dot(b,b) > EPS && dot(d,d) > EPS);
    p = a + b* cross(c,d) / cross(b,d) ;
    return true;
}
