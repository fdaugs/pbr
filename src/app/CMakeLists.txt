# Gather the source files
set(SOURCE_FILES main.cpp)

# # Add executable called "libDemo" that is built from the source files
# The extensions are automatically found.
add_executable(assignment1 ${SOURCE_FILES})
target_link_libraries(assignment1 ${OpenCV_LIBS})