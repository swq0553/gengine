#pragma once

#include "script.h"
#include "primitives.h"
#include "vector2.h"
#include "entity_macros.h"

namespace gengine
{
namespace entity
{

class ComponentMouseable
{
public:
    ComponentMouseable();

    ENTITY_COMPONENT_DECLARE(ComponentMouseable);

private:
    Vector2
        extent;
    uint
        worldIndex;
    bool
        itIsHovered;
};

}
}
