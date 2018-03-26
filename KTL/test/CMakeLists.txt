SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")

file(GLOB tests "*.cpp" "*/*.cpp" "*/*/*.cpp")

enable_testing()

add_executable(test.ktl ${tests})
target_link_libraries(test.ktl KtlModule)
