#pragma once

#include "primitives.h"
#include "graphics_object.h"
#include "graphics_vertex.h"
#include "vector2.h"

namespace gengine
{
namespace graphics
{

class Atlas;

class SpriteBatch : public Object
{
friend class Renderer;

public:
    SpriteBatch();

    virtual Renderer::Type getRenderType() override;

    void setAtlas(const Atlas & _atlas)
    {
        atlas = & _atlas;
    }

    const uint getItemCount() const { return vertexData.getSize() / 4; }

    void init();
    void addItem(const int index, const Vector2 & position, const Vector2 & extent);
    void reserve(const int size);

    void lock();
    void unlock();

private:
    VertexBuffer<Vertex>
        vertexBuffer;
    Array<Vertex>
        vertexData;
    const Atlas
        * atlas;
};

}
}
