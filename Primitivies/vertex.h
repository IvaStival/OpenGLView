#ifndef VERTEX_H
#define VERTEX_H

#include "Math/vector3d.h"
#include <cstddef>

class Vertex{
private:
    Vector3D position;
    Vector3D color;

public:
    Vertex();
    explicit Vertex(float x, float y, float z, float r, float g, float b);
    explicit Vertex(float x, float y, float z, float r, float g, float b, float w);
    explicit Vertex(const Vector3D& position,  float r, float g, float b);
    explicit Vertex(const Vector3D& position);
    explicit Vertex(float x, float y, float z, const Vector3D& color);
    explicit Vertex(const Vector3D& position, const Vector3D& color);

    const Vector3D& getPosition() const;
    const Vector3D& getColor() const;
    void setPosition(float x, float y, float z);
    void setPosition(const Vector3D& n_position);
    void setColor(float r, float g, float b);
    void setColor(const Vector3D& n_color);
    void setColorAlpha(float w);

    static const int positionSize = 3;
    static const int colorSize = 4;
    static int positionOffSet();
    static int colorOffSet();
    static int stride();

    friend std::ostream& operator<<(std::ostream& os,const Vertex& v);
};

inline Vertex::Vertex() : position(0.0f, 0.0f, 0.0f), color(1.0f, 0.0f, 0.0f){}
inline Vertex::Vertex(float x, float y, float z, float r, float g, float b) : position(x,y,z), color(r,g,b){}
inline Vertex::Vertex(float x, float y, float z, float r, float g, float b, float w) : position(x,y,z), color(r,g,b,w){}
inline Vertex::Vertex(const Vector3D& position,  float r, float g, float b) : position(position), color(r,g,b){}
inline Vertex::Vertex(const Vector3D& position) : position(position) {}
inline Vertex::Vertex(float x, float y, float z, const Vector3D& color) : position(x,y,z), color(color){}
inline Vertex::Vertex(const Vector3D& position, const Vector3D& color) : position(position), color(color){}

inline const Vector3D& Vertex::getPosition() const {
    return this->position;
}

inline const Vector3D& Vertex::getColor() const {
    return this->color;
}

inline void Vertex::setPosition(float x, float y, float z){
    this->position.setX(x);
    this->position.setY(y);
    this->position.setZ(z);
}

inline void Vertex::setPosition(const Vector3D& n_position){
    this->position = n_position;
}

inline void Vertex::setColor(float r, float g, float b){
    this->color.setX(r);
    this->color.setY(g);
    this->color.setZ(b);
}

inline void Vertex::setColor(const Vector3D& n_color){
    this->color = n_color;
}

inline void Vertex::setColorAlpha(float w){
    this->color.setW(w);
}

inline int Vertex::positionOffSet(){
    return offsetof(Vertex, position);
}
inline int Vertex::colorOffSet(){
    std::cout<<offsetof(Vertex, color)<<std::endl;
    return offsetof(Vertex, color);
}
inline int Vertex::stride(){
    return sizeof (Vertex);
}

inline std::ostream& operator<<(std::ostream& os,const Vertex& v){
    os << "Position:"<< v.position << "\n";
    os << "Color:"<< v.color << "\n";
    return os;
}

#endif // Vertex_H
