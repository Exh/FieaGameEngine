#pragma once

namespace FieaGameEngine
{

	class ActionList : public Action 
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:

		static const std::string KEY_ACTIONS;

		ActionList();

		virtual ~ActionList() = default;

		ActionList(const ActionList& rhs) = delete;
		ActionList& operator=(const ActionList& rhs) = delete;

		virtual void Update(class WorldState& state) override;

		Action* CreateAction(const std::string& className, const std::string& instanceName);

	protected:

		void Populate();

	};

	DeclareActionFactory(ActionList)
}