
# TODO : library name goes here
project(BeletteHell)

# Configure (and thus copy) the template export file to the build dir
# The export file will be added to the project headers list (and installed with them)
configure_file(${CMAKE_SOURCE_DIR}/cmake/Export.h.in
        ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
        @ONLY)

# TODO : list .h files here. 
# Helpful windows command : dir /b /oen
set(${PROJECT_NAME}_HEADERS
	${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}_Export.h
	AABB.h
	user_constants.h
	XBoxController.h
	World.h
	TerrainManager.h
	TerrainWrapper.h
	SpriteComponent.h
	SpawnPoint.h
	SpeedMessage.h
	Physics.h
	Slice.h
	PatternSpawner.h
	Physics.cpp
	Node.h
	Pattern.h
	MultipleSpawnPattern.h
	MockController.h
	MoveMessage.h
	MessageVisitor.h
	MessageParent.h
	MessageReceiver.h
	json.h
	GraphicWrapper.h
	GameLogic.h
	Entity.h
	DrawerSprite.h
	DeletionHandlerTerrain.h
	Drawer.h
	DeletionHandlerNull.h
	ControllerNull.h
	DeletionHandler.h
	constants.h
	Controller.h
	collisions.h
	Camera.h
	Closure.h
	BackgroundPlanThreeManager.h
	BackgroundPlanFourManager.h
	AttackMessage.h
	AttackerBullet.h
	AttackerNull.h
	Attacker.h
	AnimatorSpriteSwitcher.h
	Animator.h
	AnimatorNull.h
	AIRoundingAroundYourDickController.h
	AnimationMessage.h
	AIFlyingInPenisFormation.h
	AbstractMessage.h
	AIDontComeAnyCloserController.h
	FuckYouChoucheController.h
	QuadTreeProxy.h
)

SOURCE_GROUP("Controllers Headers"
	FILES AIDontComeAnyCloserController.h
	FuckYouChoucheController.h
	AIRoundingAroundYourDickController.h
)

# TODO : list .cpp files here
set(${PROJECT_NAME}_SOURCES
    AABB.cpp
	XBoxController.cpp
	World.cpp
	TerrainManager.cpp
	SpriteComponent.cpp
	SpawnPoint.cpp
	Physics.cpp
	PatternSpawner.cpp
	MultipleSpawnPattern.cpp
	main.cpp
	json.cpp
	gameplay.cpp
	GraphicWrapper.cpp
	GameLogic.cpp
	FuckYouChoucheController.cpp
	Entity.cpp
	DrawerSprite.cpp
	DeletionHandlerTerrain.cpp
	collisions.cpp
	Camera.cpp
	BackgroundPlanThreeManager.cpp
	BackgroundPlanFourManager.cpp
	AttackerBullet.cpp
	AnimatorSpriteSwitcher.cpp
	AIRoundingAroundYourDickController.cpp
	AIFlyingInPenisFormation.cpp
	AIDontComeAnyCloserController.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG
  "/MTd"
  CACHE STRING "Debug compiler flags" FORCE
)

set(CMAKE_CXX_FLAGS_RELEASE
  "/MT"
  CACHE STRING "Release compiler flags" FORCE
)

add_executable(${PROJECT_NAME} WIN32
	${${PROJECT_NAME}_SOURCES}
	${${PROJECT_NAME}_CONTROLLERS}
	${${PROJECT_NAME}_HEADERS}
)

include_directories(
	${ClanLib_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
	${ClanLib_LIBRARIES}
	${ClanLibDependencies_LIBRARIES}
	${DirectX_LIBRARY}
	${DirectX_DXGUID_LIBRARY}
)

######################################################################
## Installation stuff - common to all projects
######################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION "${VERSION}"
        SOVERSION "${SOVERSION}"
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${RUNTIME_OUTPUT_DIRECTORY}
        LIBRARY DESTINATION ${LIBRARY_OUTPUT_DIRECTORY}
        ARCHIVE DESTINATION ${ARCHIVE_OUTPUT_DIRECTORY}
        PUBLIC_HEADER DESTINATION include/${PROJECT_NAME}
)
