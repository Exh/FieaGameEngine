#pragma once

#include "Attributed.h"

namespace FieaGameEngine
{
	class Entity : public Attributed
	{

		RTTI_DECLARATIONS(Entity, Attributed)

	public:

		static const std::string KEY_NAME;

		static const std::string DEFAULT_NAME;

	public:

		Entity();

		virtual ~Entity() = default;

		void Populate();

		const std::string& Name() const;

		void SetName(const std::string& name);

		class Sector* GetSector();
		
		const class Sector* GetSector() const;

		void Update(class WorldState& state);

	protected:

		std::string mName;


	};
}
