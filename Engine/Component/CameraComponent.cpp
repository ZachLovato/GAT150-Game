#include "CameraComponent.h" 
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace wrap
{
    void CameraComponent::Initialize()
    {
        SetViewport(viewport_size);
    }

    void CameraComponent::Update()
    {
        // create camera view matrix 
        Matrix3x3 mxTranslation = Matrix3x3::CreateTranslation(-m_owner->m_transform.position);
        Matrix3x3 mxRotation = Matrix3x3::CreateRotation(-math::DegToRad(m_owner->m_transform.rotation));

        m_view = mxTranslation * mxRotation;

        g_renderer.SetViewMatrix(m_view);
    }

    void CameraComponent::SetViewport(const Vector2& size)
    {
        m_viewport = Matrix3x3::CreateTranslation(size * 0.5f);
        g_renderer.SetViewportMatrix(m_viewport);
    }

    bool CameraComponent::Write(const rapidjson::Value& value) const
    {
        return true;
    }

    bool CameraComponent::Read(const rapidjson::Value& value)
    {
        READ_DATA(value, viewport_size);

        return true;
    }

}