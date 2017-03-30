#pragma once

#include "Attributed.h"
#include "Vector.h"

namespace FieaGameEngine
{
	class World final : public Attributed
	{

		RTTI_DECLARATIONS(World, Attributed)

	public:

		World();

		~World();

		void Populate();

		const std::string& Name() const;

		void SetName(const std::string& name);

		Datum& Sectors();

		const Datum& Sectors() const;

		class Sector* CreateSector(const std::string& name) const;

		void Update(const class WorldState& state);

	private:

		std::string mName;

		Datum* mSectors;

	};
}
