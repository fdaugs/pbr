# Gather the source files
set(SOURCE_FILES main.cpp shapes/sphere.cpp shapes/sphere.h core/ray.cpp core/ray.h core/image.h core/Scene.cpp core/Scene.h)

# # Add executable called "libDemo" that is built from the source files
# The extensions are automatically found.
add_executable(assignment1 ${SOURCE_FILES})
target_link_libraries(assignment1 ${OpenCV_LIBS})