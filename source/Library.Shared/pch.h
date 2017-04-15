#pragma once

// Windows Headers
#include <SDKDDKVer.h>
#include <windows.h>

// C++ Standard Headers
#include <vector>
#include <cstdint>
#include <memory>
#include <algorithm>

// C Standard Headers
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Project Header Files
#include "SList.h"
#include "Vector.h"
#include "Datum.h"
#include "Scope.h"
#include "RTTI.h"
#include "Attributed.h"
#include "IXmlParseHelper.h"
#include "XmlParseMaster.h"
#include "XmlParseHelperScope.h"
#include "XmlParseHelperWorld.h"
#include "World.h"
#include "Sector.h"
#include "Entity.h"
#include "GameTime.h"
#include "GameClock.h"
#include "WorldState.h"
#include "Game.h"
#include "Factory.h"
#include "Action.h"
#include "ActionList.h"
#include "ActionCreateAction.h"
#include "ActionDestroyAction.h"
#include "ActionIncrement.h"
#include "ActionIf.h"
#include "EventSubscriber.h"
#include "EventPublisher.h"
#include "Event.h"
#include "EventQueue.h"
#include "Reaction.h"
#include "EventMessage.h"
#include "ReactionAttributed.h"
#include "ActionEvent.h"

// GLM
#include "glm/glm.hpp"
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Expat 
#include "expat.h"
