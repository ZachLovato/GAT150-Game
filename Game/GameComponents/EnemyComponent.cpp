#include "EnemyComponent.h"
#include "Engine.h"
#include "FrameWork/Event.h"
#include <iostream>

void EnemyComponent::Initialize()
{
    CharacterComponent::Initialize();
}

void EnemyComponent::Update()
{
    auto actor = m_owner->GetScene()->GetActorFromName("Player");
    if (actor)
    {
        wrap::Vector2 direction = actor->m_transform.position - m_owner->m_transform.position;
        wrap::Vector2 force = direction.Normalized() * 2;

        auto component = m_owner->GetComponent<wrap::PhysicsComponent>();
        if (component) component->ApplyForce(force);
    }
}

void EnemyComponent::OnCollisionEnter(wrap::Actor* other) // it does not enter here
{
    if (other->GetTag() == "Player")
    {
        std::cout << "player\n";

        wrap::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.receiver = other;

        wrap::g_eventManager.Notify(event);
    }
}

void EnemyComponent::OnCollisionExit(wrap::Actor* other)
{
    if (other->GetTag() == "Player")
    {
        wrap::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.receiver = other;

        wrap::g_eventManager.Notify(event);
    }
}

void EnemyComponent::OnNotify(const wrap::Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            m_owner->SetDestory();
        }
    }
}

bool EnemyComponent::Write(const rapidjson::Value& value) const
{
    return true;
}

bool EnemyComponent::Read(const rapidjson::Value& value)
{
    CharacterComponent::Read(value);

    return true;
}