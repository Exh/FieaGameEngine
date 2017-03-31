#pragma once

#include "Attributed.h"

namespace FieaGameEngine
{

	class Sector final : public Attributed
	{

		RTTI_DECLARATIONS(Sector, Attributed)

	public:

		static const std::string KEY_NAME;
		static const std::string KEY_ENTITIES;

		static const std::string DEFAULT_NAME;

	public:

		Sector();
		
		~Sector() = default;

		Sector(const Sector& rhs) = delete;
		Sector& operator=(const Sector& rhs) = delete;

		const std::string& Name() const;

		void SetName(const std::string& name);

		Datum& Entities();

		const Datum& Entities() const;

		class Entity* CreateEntity(const std::string& className);

		class World* GetWorld();

		const class World* GetWorld() const;

		void Update(class WorldState& state);

	private:

		void Populate();

	private:

		std::string mName;

		Datum* mEntities;

	};
}
