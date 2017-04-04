#include "pch.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Entity)

	const std::string Entity::KEY_NAME = "name";
	const std::string Entity::KEY_ACTIONS = "actions";

	const std::string Entity::DEFAULT_NAME = "Entity";


	Entity::Entity() :
		mName(DEFAULT_NAME)
	{
		Populate();
	}

	void Entity::Populate()
	{
		Attributed::Populate();

		AddExternalAttribute(KEY_NAME, &mName, 1);
		AddEmptyNestedScopeAttribute(KEY_ACTIONS);
	}

	const std::string& Entity::Name() const
	{
		return mName;
	}

	void Entity::SetName(const std::string& name)
	{
		mName = name;
	}

	Sector* Entity::GetSector()
	{
		if (mParent == nullptr)
		{
			throw std::exception("Entity's parent is nullptr. Should never happen. Do not manually call Entity constructor. Use Sector::SpawnEntity()");
		}

		assert(mParent->Is(Sector::TypeIdClass()));

		return static_cast<Sector*>(mParent);
	}

	const Sector* Entity::GetSector() const
	{
		if (mParent == nullptr)
		{
			throw std::exception("Entity's parent is nullptr. Should never happen. Do not manually call Entity constructor. Use Sector::SpawnEntity()");
		}

		assert(mParent->Is(Sector::TypeIdClass()));

		return static_cast<Sector*>(mParent);
	}

	void Entity::Update(WorldState& state)
	{
		state;
	}

	Datum& Entity::Actions()
	{
		assert(IsPrescribedAttribute(KEY_ACTIONS));
		return (*this)[KEY_ACTIONS];
	}

	const Datum& Entity::Actions() const
	{
		assert(IsPrescribedAttribute(KEY_ACTIONS));
		return *(this->Find(KEY_ACTIONS));
	}

	void Entity::CreateAction(const std::string& className,
							  const std::string& instanceName)
	{
		Action* newAction = Factory<Action>::Create(className);
		newAction->SetName(instanceName);
		Adopt(*newAction, KEY_ACTIONS);
	}
}
