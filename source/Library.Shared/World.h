#pragma once

#include "Attributed.h"
#include "Vector.h"

namespace FieaGameEngine
{
	class World final : public Attributed
	{

		RTTI_DECLARATIONS(World, Attributed)

		static const std::string KEY_NAME;
		static const std::string KEY_SECTORS;

		static const std::string DEFAULT_NAME;

	public:

		World();

		~World() = default;

		World(const World& rhs) = delete;
		World& operator=(const World& rhs) = delete;

		void Populate();

		const std::string& Name() const;

		void SetName(const std::string& name);

		Datum& Sectors();

		const Datum& Sectors() const;

		class Sector* CreateSector(const std::string& name);

		void Update(class WorldState& state);

	private:

		std::string mName;

		Datum* mSectors;

	};
}
