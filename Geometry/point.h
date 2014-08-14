struct point
{
    double x,y;
    point()
    {
        x = y = 0;
    }
    point(double x, double y) : x(x), y(y) {}
    void input()
    {
        scanf("%lf %lf",&x,&y);
    }
    point (const point &p)
    {
        x = p.x, y = p.y;
    }
    point operator+(point k)
    {
        return point(x + k.x , y + k.y );
    }
    point operator-(point k)
    {
        return point(x - k.x , y - k.y );
    }
    point operator*(double k)
    {
        return point(k * x , k * y );
    }
    point operator/(double k)
    {
        return point(x / k , y/k );
    }
    point rotleft()
    {
        return point(-y,x);
    }
    point rotright()
    {
        return point(y,-x);
    }

    bool operator ==(const point &p)const
    {
        return ((x==p.x) && (y==p.y));
    }
    bool operator <(const point &p) const
    {
        return x < p.x || (x == p.x && y < p.y);
    } // sorting angle by x axis
    /*
    bool operator <(const point &p) const {
                 return y < p.y || (y == p.y && x < p.x);
    } // sorting angle by y axis
    */
    friend ostream& operator<<(ostream& out, const point& p)
    {
        return out << '(' << p.x << ',' << p.y << ')' << endl;
    }
};

double cross(point a,point b)
{
    return a.x*b.y-a.y*b.x;
}
double dot(point a,point b)
{
    return a.x*b.x+a.y*b.y;
}
// মূলবিন্দু (0,0)  থেকে r দুরত্তে  নতুন একটি বিন্দু তৈরী করে যা (০,০) এবং a বিন্দুর সাথে co-linear
point trunc(point a,double r)
{
    double l = hypot(a.x,a.y);
    if ( !EQ(l) )return *this;
    r /= l ;
    return point(a.x*r,a.y*r);
}
point rotate(point a,point p,double angle) // p er sapekkhe a ke clock wise rotate kore
{
    point v(a.x - p.x , a.y-p.y );
    double c = cos(angle) , s = sin(angle);
    return point(p.x + v.x*c - v.y*s , p.y + v.x*s + v.y*c );
}
bool in_box(point a,point b,point c)  // rectangle : a = leftDown , b = rightTop , c ab rectangle er vitore ase kina
{
    double lox = min(a.x, b.x), hix = max(a.x, b.x);
    double loy = min(a.y, b.y), hiy = max(a.y, b.y);
    return c.x >= lox && c.x <= hix && c.y >= loy && c.y <= hiy; // remove = (eq) if strictly in box need
}
bool collinear(point p1,point p2,point p3) // p1 ,p2,p3 ekoi sorolrekhay ase kina || p1p2 line er upor p3 ase kina
{
    return (p1.y - p3.y) * (p2.x - p3.x) == (p2.y - p3.y) * (p1.x - p3.x);
}
#define sqr(x) ((x)*(x))
double sqrdis(point a,point b)
{
    return sqr(a.x - b.x) + sqr(a.y - b.y);
}
double dis(point a,point b)
{
    return sqrt(sqrdis(a,b));
}
void translate(point a,double tx, double ty)
{
    a.x += tx;
    a.y += ty;
}
void translate(point a,point t)
{
    a.x += t.x;
    a.y += t.y;
}
