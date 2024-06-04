#pragma once
//VertexLayout

struct Vertex
{
    Float3 pos;
    Vertex() :pos(0, 0, 0){}
    Vertex(Float3 pos) { this->pos = pos; }
    Vertex(float x, float y ,float z) { this->pos = {x,y,z}; }

  
};

struct VertexColor // 3D lib 에서 가장 기본적인 것 
{
    Float3 pos;
    Float4 color;

    VertexColor():pos(0,0,0),color(1,1,1,1){}
    VertexColor(float x, float y, float z, float r, float g, float b) :pos(x, y, z), color(r, g, b, 1.0f) {};
    VertexColor(Float3 pos, Float4 color) :pos(pos), color(color) {};

};

struct VertexUV // 3D lib 에서 가장 기본적인 것 
{
    Float3 pos;
    Float2 uv;

    VertexUV() :pos(0, 0, 0), uv(0, 0) {}
    VertexUV(float x, float y, float z, float u, float v) :pos(x, y, z), uv(u,v) {};
    VertexUV(Float3 pos, Float2 uv) :pos(pos), uv(uv) {};

};
 
struct VertexUVNormal // 3D lib 에서 가장 기본적인 것 
{
    Float3 pos;
    Float2 uv;
    Float3 normal;

    VertexUVNormal() :pos(0, 0, 0), uv(0, 0), normal(0,0,0) {}
    VertexUVNormal(float x, float y, float z, float u, float v,float x_normal, float y_normal, float z_normal) 
        :pos(x, y, z), uv(u, v),normal(x_normal, y_normal, z_normal) {};
};

struct VertexUVNormalTangent
{
    Float3 pos;
    Float2 uv;
    Float3 normal;
    Float3 tangent;

    VertexUVNormalTangent() :pos(0, 0, 0), uv(0, 0), normal(0, 0, 0) ,tangent(0,0,0) {}
    VertexUVNormalTangent(float x, float y, float z, float u, float v, float x_normal, float y_normal, float z_normal , float x_tangent , float y_tangent , float z_tangent)
        :pos(x, y, z), uv(u, v), normal(x_normal, y_normal, z_normal),tangent(x_tangent,y_tangent,z_tangent) {};

};

struct VertexUVNormalTangentBlend
{
    Float3 pos;
    Float2 uv;
    Float3 normal;
    Float3 tangent;
    Float4 indices;
    Float4 weights;

    VertexUVNormalTangentBlend()
        :pos(0, 0, 0), uv(0, 0), normal(0, 0, 0), tangent(0, 0, 0)
        , indices(0, 0, 0, 0), weights(0, 0, 0, 0)
    {}

};

