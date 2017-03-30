#pragma once

#include "Attributed.h"

namespace FieaGameEngine
{

	class Sector final : public Attributed
	{

		RTTI_DECLARATIONS(Sector, Attributed)

	public:

		Sector();

		~Sector();

		void Populate();

		const std::string& Name() const;

		void SetName(const std::string& name);

		Datum& Entities();

		const Datum& Entities() const;

		Entity* CreateEntity(const std::string& className);

		class World* GetWorld();

		const class World* GetWorld() const;

		void Update(const class WorldState& state);

	private:

		std::string mName;

		Datum* mEntities;

	};
}
