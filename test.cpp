#include <iostream>
#include <cmath>

using namespace std;

class Vector3D {
public:
    double X, Y, Z;

    // конструктор
    Vector3D(double x = 0, double y = 0, double z = 0) : X(x), Y(y), Z(z) {}

    /* перегрузка операторов */

    // вычитание
    Vector3D operator-(const Vector3D& otherVec) const {
        return Vector3D(X - otherVec.X, Y - otherVec.Y, Z - otherVec.Z);
    }

    // сложение
    Vector3D operator+(const Vector3D& otherVec) const {
        return Vector3D(X + otherVec.X, Y + otherVec.Y, Z + otherVec.Z);
    }

    // умножение на скаляр
    Vector3D operator*(double scalar) const {
        return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }

    // скалярное произведение
    double Dot(const Vector3D& otherVec) const {
        return X * otherVec.X + Y * otherVec.Y + Z * otherVec.Z;
    }
};

class Segment3D {
public:
    Vector3D start;
    Vector3D end;

    // конструктор
    Segment3D(const Vector3D& s = Vector3D(), const Vector3D& e = Vector3D()) : start(s), end(e) {}

    // направляющий вектор
    Vector3D Direction() const {
        return end - start;
    }

    // точка на отрезке через параметр
    Vector3D PointAt(double t) const {
        return start + Direction() * t;
    }
};

bool Intersect(const Segment3D& seg1, const Segment3D& seg2, Vector3D& outIntersection) {
    // значение для учёта погрешностей
    const double epsil = 1e-10;

    // направляющие векторы обоих отрезков
    Vector3D d1 = seg1.Direction(); 
    Vector3D d2 = seg2.Direction();
    
    // вектор между начальными точками отрезков
    Vector3D r = seg1.start - seg2.start;

    double a = d1.Dot(d1); // квадрат длины d1
    double b = d1.Dot(d2); // произведение d1 и d2
    double c = d2.Dot(d2); // квадрат длины  d2
    double d = d1.Dot(r);  // произведение d1 и r
    double e = d2.Dot(r);  // произведение d2 и r

    // определитель матрицы системы
    double determ = a * c - b * b;

    // если определитель близок к нулю, то отрезки параллельны или коллинеарны
    if (determ < epsil) {
        return false; 
    }

    // s - положение точки пересечения на первом отрезке
    // t - положение точки пересечения на втором отрезке
    double s = (b * e - c * d) / determ;
    double t = (a * e - b * d) / determ;

    // если s и t в пределах [0, 1], то точка пересечения находится внутри обоих отрезков
    if (s >= 0 && s <= 1 && t >= 0 && t <= 1) {
        // вычисление точки пересечения
        outIntersection = seg1.PointAt(s);
        return true;
    }

    // если параметры вне диапазона
    return false;
}

    /* 2 примера для демострации работы */
int main() {

    // отрезки пересекаются
    Segment3D segm1(Vector3D(0, 0, 0), Vector3D(2, 2, 0));
    Segment3D segm2(Vector3D(0, 2, 0), Vector3D(2, 0, 0));

    Vector3D coordinate;
    if (Intersect(segm1, segm2, coordinate)) {
        cout << "Отрезки пересекаются в точке: (" << coordinate.X << ", " << coordinate.Y << ", " << coordinate.Z << ")\n";
    } 
    else {
        cout << "Отрезки не пересекаются.\n";
    }

    // отрезки не пересекаются
    Segment3D segm3(Vector3D(0, 0, 0), Vector3D(1, 1, 0));
    Segment3D segm4(Vector3D(2, 2, 0), Vector3D(3, 3, 0));

    if (Intersect(segm3, segm4, coordinate)) {
        cout << "Отрезки пересекаются в точке: (" << coordinate.X << ", " << coordinate.Y << ", " << coordinate.Z << ")\n";
    } 
    else {
        cout << "Отрезки не пересекаются.\n";
    }

    return 0;
}