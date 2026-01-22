#pragma once
#include <iostream>
#include <cmath>



class Vector2D {
public:
    float x;
    float y;


    Vector2D() : x(0.0f), y(0.0f) {}


    Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D& Add(const Vector2D& vec) {
        this->x += vec.x;
        this->y += vec.y;
        return *this;
    }

    Vector2D& Subtract(const Vector2D& vec) {
        this->x -= vec.x;
        this->y -= vec.y;
        return *this;
    }

    Vector2D& Multiply(const Vector2D& vec) {
        this->x *= vec.x;
        this->y *= vec.y;
        return *this;
    }

    Vector2D& Divide(const Vector2D& vec) {
        this->x /= vec.x;
        this->y /= vec.y;
        return *this;
    }


    friend Vector2D operator+(Vector2D v1, const Vector2D& v2) {
        return v1.Add(v2);
    }

    friend Vector2D operator-(Vector2D v1, const Vector2D& v2) {
        return v1.Subtract(v2);
    }

    friend Vector2D operator*(Vector2D v1, const Vector2D& v2) {
        return v1.Multiply(v2);
    }

    friend Vector2D operator/(Vector2D v1, const Vector2D& v2) {
        return v1.Divide(v2);
    }



    Vector2D& operator+=(const Vector2D& vec) {
        return this->Add(vec);
    }

    Vector2D& operator-=(const Vector2D& vec) {
        return this->Subtract(vec);
    }

    Vector2D& operator*=(const Vector2D& vec) {
        return this->Multiply(vec);
    }

    Vector2D& operator/=(const Vector2D& vec) {
        return this->Divide(vec);
    }


    Vector2D operator*(const int& scalar) const {
        return Vector2D(this->x * scalar, this->y * scalar);
    }


    Vector2D operator*(const float& scalar) const {
        return Vector2D(this->x * scalar, this->y * scalar);
    }

    Vector2D operator/(const float& scalar) const {
        return Vector2D(this->x / scalar, this->y / scalar);
    }


    Vector2D& zero() {
        this->x = 0;
        this->y = 0;
        return *this;
    }

    float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }


    float MagnitudeSquared() const {
        return x * x + y * y;
    }


    Vector2D& Normalize() {
        float mag = Magnitude();
        if (mag > 0) {
            x /= mag;
            y /= mag;
        }
        return *this;
    }


    Vector2D Normalized() const {
        Vector2D result(*this);
        return result.Normalize();
    }


    float Dot(const Vector2D& vec) const {
        return x * vec.x + y * vec.y;
    }


    float Distance(const Vector2D& vec) const {
        float dx = x - vec.x;
        float dy = y - vec.y;
        return std::sqrt(dx * dx + dy * dy);
    }


    float DistanceSquared(const Vector2D& vec) const {
        float dx = x - vec.x;
        float dy = y - vec.y;
        return dx * dx + dy * dy;
    }


    Vector2D& Limit(float max) {
        float magSq = MagnitudeSquared();
        if (magSq > max * max) {
            Normalize();
            x *= max;
            y *= max;
        }
        return *this;
    }


    bool operator==(const Vector2D& vec) const {
        return (x == vec.x && y == vec.y);
    }

    bool operator!=(const Vector2D& vec) const {
        return !(*this == vec);
    }


    friend std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
        stream << "(" << vec.x << ", " << vec.y << ")";
        return stream;
    }


    static Vector2D Zero() { return Vector2D(0, 0); }
    static Vector2D One() { return Vector2D(1, 1); }
    static Vector2D Up() { return Vector2D(0, -1); }
    static Vector2D Down() { return Vector2D(0, 1); }
    static Vector2D Left() { return Vector2D(-1, 0); }
    static Vector2D Right() { return Vector2D(1, 0); }
};