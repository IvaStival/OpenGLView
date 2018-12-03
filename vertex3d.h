#ifndef VERTEX3D_H
#define VERTEX3D_H

#include "vector3d.h"
#include <cstddef>

class Vertex3D{
private:
    Vector3D position;
    Vector3D color;

public:
    Vertex3D();
    explicit Vertex3D(float x, float y, float z, float r, float g, float b);
    explicit Vertex3D(float x, float y, float z, float r, float g, float b, float w);
    explicit Vertex3D(const Vector3D& position,  float r, float g, float b);
    explicit Vertex3D(const Vector3D& position);
    explicit Vertex3D(float x, float y, float z, const Vector3D& color);
    explicit Vertex3D(const Vector3D& position, const Vector3D& color);

    const Vector3D& getPosition() const;
    const Vector3D& getColor() const;
    void setPosition(float x, float y, float z);
    void setPosition(const Vector3D& n_position);
    void setColor(float r, float g, float b);
    void setColor(const Vector3D& n_color);
    void setColorAlpha(float w);

    static const int positionSize = 3;
    static const int colorSize = 3;
    static int positionOffSet();
    static int colorOffSet();
    static int stride();

    friend std::ostream& operator<<(std::ostream& os,const Vertex3D& v);
};

inline Vertex3D::Vertex3D() : position(0.0f, 0.0f, 0.0f), color(1.0f, 0.0f, 0.0f){}
inline Vertex3D::Vertex3D(float x, float y, float z, float r, float g, float b) : position(x,y,z), color(r,g,b){}
inline Vertex3D::Vertex3D(float x, float y, float z, float r, float g, float b, float w) : position(x,y,z), color(r,g,b,w){}
inline Vertex3D::Vertex3D(const Vector3D& position,  float r, float g, float b) : position(position), color(r,g,b){}
inline Vertex3D::Vertex3D(const Vector3D& position) : position(position) {}
inline Vertex3D::Vertex3D(float x, float y, float z, const Vector3D& color) : position(x,y,z), color(color){}
inline Vertex3D::Vertex3D(const Vector3D& position, const Vector3D& color) : position(position), color(color){}

inline const Vector3D& Vertex3D::getPosition() const {
    return this->position;
}

inline const Vector3D& Vertex3D::getColor() const {
    return this->color;
}

inline void Vertex3D::setPosition(float x, float y, float z){
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
}

inline void Vertex3D::setPosition(const Vector3D& n_position){
    this->position = n_position;
}

inline void Vertex3D::setColor(float r, float g, float b){
    this->color.setX(r);
    this->color.setY(g);
    this->color.setZ(b);
}

inline void Vertex3D::setColor(const Vector3D& n_color){
    this->color = n_color;
}

inline void Vertex3D::setColorAlpha(float w){
    this->color.setW(w);
}

inline int Vertex3D::positionOffSet(){
    return offsetof(Vertex3D, position);
}
inline int Vertex3D::colorOffSet(){
    return offsetof(Vertex3D, color);
}
inline int Vertex3D::stride(){
    return sizeof (Vertex3D);
}

inline std::ostream& operator<<(std::ostream& os,const Vertex3D& v){
    os << "Position:"<< v.position << "\n";
    os << "Color:"<< v.color << "\n";
    return os;
}

#endif // VERTEX3D_H
