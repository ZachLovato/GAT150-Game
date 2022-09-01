#include "SpriteAniComponent.h"
#include "Renderer/Renderer.h"
#include "FrameWork/Actor.h"
#include "Engine.h"


namespace wrap 
{

    void SpriteAniComponent::Update()
    {   
        //update frame
        frameTimer += g_time.deltaTime;
        if (frameTimer >= 1.0f / m_sequence->fps)
        {
            frameTimer = 0;
            frame++;
            if (frame > m_sequence->end_frame)
            {
                frame = (m_sequence->loop) ? m_sequence->start_frame : m_sequence->end_frame;
            }
        }

        //calculate source frame
        /*Vector2 cellSize = m_texture->GetSize() / Vector2{ num_colums, num_rows };

        int column = (frame - 1) % num_colums;
        int row = (frame - 1) / num_colums;

        source.x = (int)(column * cellSize.x);
        source.y = (int)(row * cellSize.y);
        source.w = (int)(cellSize.x);
        source.h = (int)(cellSize.y);*/
    }

    void SpriteAniComponent::Draw(Renderer& renderer)
    {
        renderer.Draw(m_sequence->texture, GetSource(), m_owner -> m_transform, registration, flipHorizontal);
       // renderer.Draw(m_texture, GetSource(), m_owner->m_transform, registration, flipHorizontal);
    }

    bool SpriteAniComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool SpriteAniComponent::Read(const rapidjson::Value& value)
    {
        if (value.HasMember("sequences") && value["sequences"].IsArray())
        {
            for (auto& sequenceValue : value["sequences"].GetArray())
            {
                Sequence sequence;

                READ_DATA(sequenceValue, sequence.name);
                //READ_DATA(sequenceValue, sequence.fps);
                READ_DATA(sequenceValue, sequence.num_columns);
                READ_DATA(sequenceValue, sequence.num_rows);
                READ_DATA(sequenceValue, sequence.start_frame);
                READ_DATA(sequenceValue, sequence.end_frame);

                std::string texture_name;
                READ_DATA(sequenceValue, texture_name);

                sequence.texture = g_resources.Get<Texture>(texture_name, g_renderer);

                m_sequences[sequence.name] = sequence;
            }
        }

        std::string default_sequence;
        if (!READ_DATA(value, default_sequence))
        {
            // if default sequence not specified, use the first sequence name in the sequences map 
            default_sequence = m_sequences.begin()->first;
        }

        SetSequence(default_sequence);

        return true;
    }

    Rect& SpriteAniComponent::GetSource()
    {
        // calculate sequence source rect 
        Vector2 cellSize = m_sequence->texture->GetSize() / Vector2{ m_sequence->num_columns, m_sequence -> num_rows };

        int column = (frame - 1) % m_sequence->num_columns;
        int row = (frame - 1) / m_sequence->num_columns;

        source.x = (int)(column * cellSize.x);
        source.y = (int)(row * cellSize.y);
        source.w = (int)(cellSize.x);
        source.h = (int)(cellSize.y);

        return source;

    }

    void SpriteAniComponent::SetSequence(const std::string& name)
    {
        // don�t restart sequence if already playing 
        if (m_sequence && m_sequence->name == name) return;

        if (m_sequences.find(name) != m_sequences.end())
        {
            m_sequence = &m_sequences[name];

            frame = m_sequence->start_frame;
            frameTimer = 0;
        }
    }

}
