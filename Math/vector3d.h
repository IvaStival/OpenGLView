#ifndef Vector3D_H
#define Vector3D_H

#include<iostream>

class Vector3D{
private:
    float x, y, z;
    float w;

public:
    Vector3D();
    explicit Vector3D(float x, float y, float z);
    explicit Vector3D(float x, float y, float z, float w);
    explicit Vector3D(const Vector3D& right);
    ~Vector3D();

    float getX();
    float getY();
    float getZ();
    float getW();
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    void setW(float z);

    Vector3D& operator+(float scalar) const;
    Vector3D& operator+(const Vector3D& right) const;
    Vector3D& operator-(float scalar) const;
    Vector3D& operator-(const Vector3D& right) const;
    Vector3D& operator*(float scalar) const;
    Vector3D& operator*(const Vector3D& right) const;

    Vector3D& operator+=(float scalar);
    Vector3D& operator+=(const Vector3D& right);
    Vector3D& operator-=(float scalar);
    Vector3D& operator-=(const Vector3D& right);
    Vector3D& operator*=(float scalar);
    Vector3D& operator*=(const Vector3D& right);

    friend std::ostream& operator<<(std::ostream& os,const Vector3D& v);

};


inline Vector3D::Vector3D() : x(0.0f), y(0.0f), z(0.0f), w(1.0f){}
inline Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z), w(1.0f) {}
inline Vector3D::Vector3D(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
inline Vector3D::Vector3D(const Vector3D& right) : x(right.x), y(right.y), z(right.z), w(right.w){}
inline Vector3D::~Vector3D(){}

inline float Vector3D::getX(){ return this->x; };
inline float Vector3D::getY(){ return this->y; };
inline float Vector3D::getZ(){ return this->z; };
inline float Vector3D::getW(){ return this->w; };

inline void Vector3D::setX(float n_x) { this->x = n_x;}
inline void Vector3D::setY(float n_y) { this->y = n_y;}
inline void Vector3D::setZ(float n_z) { this->z = n_z;}
inline void Vector3D::setW(float n_w) { this->w = n_w;}


inline Vector3D& Vector3D::operator+(float scalar)  const{
    Vector3D v;
    v.x = this->x+scalar;
    v.y = this->y+scalar;
    v.z = this->z+scalar;
    return v;
}

inline Vector3D& Vector3D::operator+(const Vector3D& right)  const{
    Vector3D v;
    v.x = this->x+right.x;
    v.y = this->y+right.y;
    v.z = this->z+right.z;
    return v;
}

inline Vector3D& Vector3D::operator-(float scalar)  const{
    Vector3D v;
    v.x = this->x-scalar;
    v.y = this->y-scalar;
    v.z = this->z-scalar;
    return v;
}

inline Vector3D& Vector3D::operator-(const Vector3D& right)  const{
    Vector3D v;
    v.x = this->x-right.x;
    v.y = this->y-right.y;
    v.z = this->z-right.z;
    return v;
}

inline Vector3D& Vector3D::operator*(float scalar) const{
    Vector3D v;
    v.x = this->x*scalar;
    v.y = this->y*scalar;
    v.z = this->z*scalar;
    return v;
}

inline Vector3D& Vector3D::operator*(const Vector3D& right) const{
    Vector3D v;
    v.x = this->x*right.x;
    v.y = this->y*right.y;
    v.z = this->z*right.z;
    return v;
}

inline Vector3D& Vector3D::operator+=(const Vector3D& right){
    this->x += right.x;
    this->y += right.y;
    this->z += right.z;
    return *this;
}

inline Vector3D& Vector3D::operator +=(float scalar){
    this->x += scalar;
    this->y += scalar;
    this->z += scalar;
    return *this;
}

inline Vector3D& Vector3D::operator-=(const Vector3D& right){
    this->x -= right.x;
    this->y -= right.y;
    this->z -= right.z;
    return *this;
}

inline Vector3D& Vector3D::operator-=(float scalar){
    this->x -= scalar;
    this->y -= scalar;
    this->z -= scalar;
    return *this;
}
inline Vector3D& Vector3D::operator*=(const Vector3D& right){
    this->x *= right.x;
    this->y *= right.y;
    this->z *= right.z;
    return *this;
}

inline Vector3D& Vector3D::operator*=(float scalar){
    this->x *= scalar;
    this->y *= scalar;
    this->z *= scalar;
    return *this;
}

inline std::ostream& operator<<(std::ostream& os,const Vector3D& v){

    os << "X:"<< v.x << " " << "Y:"<< v.y << " " << "Z:" << v.z << "\n";
    return os;
}





#endif // Vector3D_H
