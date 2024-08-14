cmake_minimum_required(VERSION 3.28)
project(VulkanMiragePathtracer)
set(CMAKE_CXX_STANDARD 26)

# Adding debug and build definitions 
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG_BUILD)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DRELEASE_BUILD)
endif()

# ---- Main project's files ----
# Add source files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/res)

# Gather source and header files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp") #SIDE note u need to rerun CMAKE each time u add class manually since it doesn't need to change to add file.
file(GLOB_RECURSE HEADER_FILES "src/*.h")

# Search for the assets files
file(GLOB_RECURSE ASSETS_FILES "res/*.*")

# Group files for easier navigation in IDEs
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES} ${HEADER_FILES})
source_group(TREE ${CMAKE_SOURCE_DIR} FILES ${ASSETS_FILES})

#enable rc for the icon
enable_language("RC")
# Define the startup executable for the project
add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${ASSETS_FILES} resources.rc)
# Treat asset files as headers (prevents them from being compiled)
set_source_files_properties(${ASSETS_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

# ---- Libraries ----
add_definitions(-D GLM_ENABLE_EXPERIMENTAL)

# Find packages for your dependencies
find_package(SDL2 CONFIG REQUIRED)
find_package(Vulkan REQUIRED)
find_package(VulkanMemoryAllocator CONFIG REQUIRED)
find_package(Tracy CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(unofficial-imguizmo CONFIG REQUIRED) 
find_package(Stb REQUIRED)
find_package(assimp CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

# Link the libraries to your project's executable
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} PRIVATE Vulkan::Vulkan GPUOpen::VulkanMemoryAllocator)

target_link_libraries(${PROJECT_NAME}  PRIVATE Tracy::TracyClient)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE unofficial::imguizmo::imguizmo)
target_include_directories(${PROJECT_NAME} PRIVATE ${Stb_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE assimp::assimp)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)
target_link_libraries(${PROJECT_NAME} PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)

#Asssimp config
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE)
set(ASSIMP_BUILD_FBX_IMPORTER TRUE)

# tracey config
option( TRACY_ENABLE "" ON)
option( TRACY_ON_DEMAND "" ON)

# ---- Post build linkage ----
# Add and link to resource files in build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_CURRENT_BINARY_DIR}/res)

# Add and link to tracy files in build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E create_symlink
        ${CMAKE_SOURCE_DIR}/tracey
        ${CMAKE_CURRENT_BINARY_DIR}/tracey)
