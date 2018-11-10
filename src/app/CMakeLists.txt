# Gather the source files
set(SOURCE_FILES main.cpp shapes/sphere.cpp shapes/sphere.h core/ray.cpp core/ray.h core/image.h core/Scene.cpp core/Scene.h)

# # Add executable called "libDemo" that is built from the source files
# The extensions are automatically found.
add_executable(pbr ${SOURCE_FILES})
target_link_libraries(pbr ${OpenCV_LIBS})

# Adds a post-build event to uselib
add_custom_command(TARGET pbr POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/lib/libstdc++-6.dll"      # this is in-file
        $<TARGET_FILE_DIR:pbr>)