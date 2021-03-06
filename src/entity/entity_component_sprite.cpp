#include "entity_component_sprite.h"

#include "graphics_system.h"
#include "graphics_world.h"
#include "graphics_texture.h"
#include "graphics_atlas.h"
#include "entity_system.h"
#include "script.h"
#include "debug.h"
#include <string.h>
#include "entity.h"

namespace gengine
{
namespace entity
{

ComponentSprite::ComponentSprite()
    :
    atlas(nullptr),
    worldIndex(0),
    atlasItem(0),
    extentHasBeenSet(false)
{
}

ENTITY_COMPONENT_IMPLEMENT(ComponentSprite)
{
    ENTITY_ADD_GETTER(ComponentSprite, "extent", { Vector2::push(state, self.sprite.getExtent()); });
}

ENTITY_COMPONENT_SETTERS(ComponentSprite)
{
    ENTITY_COMPONENT_SETTER_FIRST(layer)
    {
        self.sprite.setLayer(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(extent)
    {
        Vector2::fill(state, self.sprite.getExtent(), 3);
        self.extentHasBeenSet = true;
    }
    ENTITY_COMPONENT_SETTER(uvScale)
    {
        Vector2::fill(state, self.sprite.getUvScale(), 3);
    }
    ENTITY_COMPONENT_SETTER(uvOffset)
    {
        Vector2::fill(state, self.sprite.getUvOffset(), 3);
    }
    ENTITY_COMPONENT_SETTER(color)
    {
        Vector4::fill(state, self.sprite.getColor(), 3);
    }
    ENTITY_COMPONENT_SETTER(alpha)
    {
        self.sprite.setColorAlpha(lua_tonumber(state,3));
    }
    ENTITY_COMPONENT_SETTER(texture)
    {
        graphics::Texture * texture = static_cast<graphics::Texture *>(lua_touserdata(state, 3));
        self.sprite.setTexture(*texture);
    }
    ENTITY_COMPONENT_SETTER(atlas)
    {
        self.atlas = static_cast<graphics::Atlas *>(lua_touserdata(state, 3));
    }
    ENTITY_COMPONENT_SETTER(atlasItem)
    {
        self.atlasItem = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER(world)
    {
        self.worldIndex = lua_tonumber(state,3);
    }
    ENTITY_COMPONENT_SETTER_END()
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSprite, init)
{
    if(self.atlas)
    {
        self.sprite.setTexture(self.atlas->getTexture());
        const graphics::AtlasItem & item = self.atlas->getItem(self.atlasItem);
        self.sprite.setUvOffset(item.uvOffset);
        self.sprite.setUvScale(item.uvScale);

        if(!self.extentHasBeenSet)
        {
            self.atlas->getDefaultExtent(self.sprite.getExtent(), self.atlasItem);
        }
    }
    else
    {
        if(!self.extentHasBeenSet)
        {
            const Pointer<const graphics::Texture> texture = self.sprite.getTexture();

            if(!texture.isNull())
            {
                self.sprite.getExtent().x = texture->getWidth();
                self.sprite.getExtent().y = texture->getHeight();
            }
        }
    }
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSprite, insert)
{
    graphics::System::getInstance().getWorld(self.worldIndex).addObject(self.sprite);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSprite, update)
{
    graphics::Sprite & sprite = self.sprite;

    Transform transform;
    fillTransformFromComponent(state, transform);

    sprite.setPosition(transform.position);
    sprite.setRotation(transform.rotation);
}
ENTITY_COMPONENT_END()

ENTITY_COMPONENT_METHOD(ComponentSprite, remove)
{
    graphics::System::getInstance().getWorld(self.worldIndex).removeObject(self.sprite);
}
ENTITY_COMPONENT_END()

}
}
