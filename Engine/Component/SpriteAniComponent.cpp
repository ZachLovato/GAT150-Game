#include "SpriteAniComponent.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"
#include "Engine.h"


void wrap::SpriteAniComponent::Update()
{
    //update frame
    frameTimer += g_time.deltaTime;
    if (frameTimer >= 1.0f / fps)
    {
        frameTimer = 0;
        frame++;
        if (frame > end_frame)
        {
            frame = start_frame;
        }
    }

    //calculate source frame
    Vector2 cellSize = m_texture->GetSize() / Vector2{ num_colums, num_rows };

    int column = (frame - 1) % num_colums;
    int row = (frame - 1) / num_colums;

    source.x = (int)(column * cellSize.x);
    source.y = (int)(row * cellSize.y);
    source.w = (int)(cellSize.x);
    source.h = (int)(cellSize.y);
}

void wrap::SpriteAniComponent::Draw(Renderer& renderer)
{
    renderer.Draw(m_texture, source, m_owner->m_transform);
}

bool wrap::SpriteAniComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool wrap::SpriteAniComponent::Read(const rapidjson::Value& value)
{
    std::string texture_name;
    READ_DATA(value, texture_name);

    m_texture = g_resources.Get<Texture>(texture_name, g_renderer);

    READ_DATA(value, fps);
    READ_DATA(value, num_colums);
    READ_DATA(value, num_rows);
    READ_DATA(value, start_frame);
    READ_DATA(value, end_frame);

    return true;
}
