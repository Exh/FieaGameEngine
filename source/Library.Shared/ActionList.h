#pragma once

namespace FieaGameEngine
{

	class ActionList : public Action 
	{
		RTTI_DECLARATIONS(ActionList, Action)

	public:

		static const std::string KEY_ACTIONS;

		/** Default constructor which populates this class's attributes. */
		ActionList();

		virtual ~ActionList() = default;

		ActionList(const ActionList& rhs) = delete;
		ActionList& operator=(const ActionList& rhs) = delete;

		/** Updates the action, essentially executing any of its behavior.
		@param state The current world state.*/
		virtual void Update(class WorldState& state) override;

		/** Updates the action, essentially executing any of its behavior.
		@param state The current world state.*/
		Action* CreateAction(const std::string& className, const std::string& instanceName);

	protected:

		void Populate();

	};

	DeclareActionFactory(ActionList)
}