#pragma once

#include "Attributed.h"

namespace FieaGameEngine
{
	class Entity : public Attributed
	{

		RTTI_DECLARATIONS(Entity, Attributed)

	public:

		Entity();

		virtual ~Entity();

		void Populate();

		const std::string& Name() const;

		void SetName(const std::string& name);

		class Sector* GetSector();
		
		const class Sector* GetSector() const;

		void Update(const class WorldState& state);

	protected:

		std::string mName;


	};
}
