#include "pch.h"

namespace FieaGameEngine
{

	RTTI_DEFINITIONS(Entity)

	const std::string Entity::KEY_NAME = "name";
	const std::string Entity::KEY_ACTIONS = "actions";

	const std::string Entity::DEFAULT_NAME = "Entity";


	Entity::Entity() :
		mName(DEFAULT_NAME),
		mActions(nullptr)
	{
		Populate();
	}

	void Entity::Populate()
	{
		Attributed::Populate();

		AddExternalAttribute(KEY_NAME, &mName, 1);
		AddEmptyNestedScopeAttribute(KEY_ACTIONS);

		mActions = &(*this)[KEY_ACTIONS];
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

		assert(mActions != nullptr);
		
		if (mActions->Size() > 0)
		{
			Scope** actions = &(mActions->GetScope(0));
			for (std::uint32_t i = 0; i < mActions->Size(); i++)
			{
				assert(actions[i] != nullptr);
				assert(actions[i]->Is(Action::TypeIdClass()));
				state.mAction = static_cast<Action*>(actions[i]);
				static_cast<Action*>(actions[i])->Update(state);
			}
		}

		state.mAction = nullptr;
	}

	Datum& Entity::Actions()
	{
		assert(IsPrescribedAttribute(KEY_ACTIONS));
		assert(mActions != nullptr);
		return *mActions;
	}

	const Datum& Entity::Actions() const
	{
		assert(IsPrescribedAttribute(KEY_ACTIONS));
		assert(mActions != nullptr);
		return *mActions;
	}

	Action* Entity::CreateAction(const std::string& className,
								 const std::string& instanceName)
	{
		Action* newAction = Factory<Action>::Create(className);
		newAction->SetName(instanceName);
		Adopt(*newAction, KEY_ACTIONS);

		return newAction;
	}
}
