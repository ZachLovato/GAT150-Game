#pragma once
#include "Component/CharacterComponent.h"

class EnemyComponent : public wrap::CharacterComponent 
{
public:
	CLASS_DECLARATION(EnemyComponent)

		virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(wrap::Actor* other) override;
	virtual void OnCollisionExit(wrap::Actor* other) override;

	virtual void OnNotify(const wrap::Event& event) override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

protected:
};