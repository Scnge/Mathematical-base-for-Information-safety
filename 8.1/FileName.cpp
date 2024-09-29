/*
3 2 5
1 4
3 1
4
*/
#include<iostream>
#include<vector>
using namespace std;

struct Point {
    int x, y;
    bool inf;

    Point(int x, int y) : x(x), y(y), inf(false) {}
    Point(bool inf) : x(0), y(0), inf(inf) {}

    bool operator==(const Point& other) const {
        if (inf != other.inf)
            return false;
        if (inf && other.inf)
            return true;
        return (!inf && !other.inf) && (x == other.x) && (y == other.y);
    }
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }
};



class EllipticCurve {
public:
    int a, b, p;
    Point ZERO;

    EllipticCurve(int a, int b, int p) : a(a), b(b), p(p), ZERO(true) {}

    // 最大公约数
    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    // 扩展欧几里得求逆元
    int inverse(int a, int m) {
        int m0 = m, t, q;
        int x0 = 0, x1 = 1;

        if (m == 1)
            return 0;
        if (m == 0)
            return a;

        while (a > 1) {
            q = a / m;
            t = m;
            m = a % m;
            a = t;
            t = x0;
            x0 = x1 - q * x0;
            x1 = t;
        }

        if (x1 < 0)
            x1 += m0;

        return x1;
    }

    // 判断是否为椭圆曲线
    bool isEllipticCurve() {
        return (4 * a * a * a + 27 * b * b) % p != 0;
    }

    // 判断点是否在曲线上
    bool isOnCurve(const Point& P) {
        if (P == ZERO)
            return true;
        else
            return (P.y * P.y - P.x * P.x * P.x - a * P.x - b) % p == 0;
    }

    // 2P
    Point doublePoint(const Point& P) {
        int s = ((3 * P.x * P.x + a) * inverse(2 * P.y, p)) % p;
        while (s < 0)
            s += p;
        int xR = (s * s - 2 * P.x) % p;
        while (xR < 0)
            xR += p;
        int yR = (s * (P.x - xR) - P.y) % p;
        while (yR < 0)
            yR += p;
        return Point(xR, yR);
    }

    // P+Q
    Point addPoints(const Point& P, const Point& Q) {
        if (P == ZERO)
            return Q;
        if (Q == ZERO)
            return P;
        if (P.x == Q.x)
            return ZERO;

        int s = ((Q.y - P.y) * inverse(Q.x - P.x, p)) % p;
        while (s < 0)
            s += p;
        int xR = (s * s - P.x - Q.x) % p;
        while (xR < 0)
            xR += p;
        int yR = (s * (P.x - xR) - P.y) % p;
        while (yR < 0)
            yR += p;
        return Point(xR, yR);
    }

    // kP
    Point multiplyPoint(const Point& P, int k) {
        Point R = ZERO;
        Point Q = P;
        while (k > 0) {
            if (k % 2 == 1) {
                R = addPoints(R, Q);
            }
            Q = doublePoint(Q);
            k = k / 2;
        }
        return R;
    }


    // 点阶
    int orderOfPoint(const Point& P) {
        if (!isOnCurve(P))
            return -1;
        if (P == ZERO)
            return INT_MAX;
        Point Q = P;
        int order = 1;
        while (Q != ZERO) {
            Q = addPoints(P, Q);
            order++;
        }
        return order;
    }

    // 曲线阶
    int orderOfCurve() {
        vector<Point> points = allPoints();
        return points.size();
    }

    // 点
    vector<Point> allPoints() {
        vector<Point> points{ ZERO };
        for (int x = 0; x < p; x++) {
            for (int y = 0; y < p; y++) {
                if (isOnCurve(Point(x, y))) {
                    points.push_back(Point(x, y));
                }
            }
        }
        return points;
    }
};

string Output(int i) {
    if (i == 1)
        return "Yes";
    if (i == 0)
        return "No";
}


int main() {
    int a, b, p;
    cout << "Please input a,b and p:";
    cin >> a >> b >> p;
    int x1, x2, y1, y2;
    cout << "Please input P(x1,y1):";
    cin >> x1 >> y1;
    cout << "Please input Q(x2,y2):";
    cin >> x2 >> y2;
    int k;
    cout << "Please input k:";
    cin >> k;

    EllipticCurve curve(a, b, p);
    Point P(x1, y1);
    Point Q(x2, y2);

    cout << "Elliptic curvey is y^2 = x^3 + " << a << "x + " << b << " (mod " << p << ")" << endl;
    cout << "Is elliptic curve: " << Output(curve.isEllipticCurve()) << endl;
    cout << "Is P(" << P.x << ", " << P.y << ") on curve: " << Output(curve.isOnCurve(P)) << endl;
    cout << "Is Q(" << Q.x << ", " << Q.y << ") on curve: " << Output(curve.isOnCurve(Q)) << endl;

    // P+Q
    Point R = curve.addPoints(P, Q);
    cout << "P + Q = (" << R.x << ", " << R.y << ")" << endl;

    // 2P
    Point twoP = curve.doublePoint(P);
    cout << "2P = (" << twoP.x << ", " << twoP.y << ")" << endl;

    // kP
    Point sevenP = curve.multiplyPoint(P, k);
    cout << k << "P = (" << sevenP.x << ", " << sevenP.y << ")" << endl;

    // P阶
    int orderP = curve.orderOfPoint(P);
    cout << "Order of P: " << orderP << endl;

    // 曲线阶
    int orderCurve = curve.orderOfCurve();
    cout << "Order of curve: " << orderCurve << endl;

    // 点
    vector<Point> points = curve.allPoints();
    cout << "The number of points:" << points.size() << endl;
    cout << "All points:" << endl;
    for (int i = 0; i < points.size(); ++i) {
        const Point& point = points[i];
        if (point == curve.ZERO)
            cout << "O" << " ";
        else
            cout << "(" << point.x << "," << point.y << ")" << " ";
    }
    
    return 0;
}