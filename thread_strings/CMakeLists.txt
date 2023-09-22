cmake_minimum_required(VERSION 3.5)
project(thread_strings)

get_filename_component(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}" DIRECTORY)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Add your package's source files
add_executable(
  thread_strings 
  ${SRC_DIR}/thread_strings/src/threading.cpp
  ${SRC_DIR}/thread_strings/src/chars_map.cpp
  ${SRC_DIR}/thread_strings/src/trie.cpp
  ${SRC_DIR}/thread_strings/src/read_lines.cpp
  ${SRC_DIR}/thread_strings/src/read_vocab.cpp
  ${SRC_DIR}/thread_strings/src/input_handling.cpp
  ${SRC_DIR}/thread_strings/src/output_handling.cpp
  ${SRC_DIR}/thread_strings/src/parent_thread.cpp
  ${SRC_DIR}/thread_strings/src/count_vocab_strings.cpp
  ${SRC_DIR}/thread_strings/src/args_handling.cpp
  ${SRC_DIR}/thread_strings/src/main.cpp
  )
  
target_link_libraries(thread_strings PRIVATE Threads::Threads)

target_include_directories(
    thread_strings PUBLIC 
    ${SRC_DIR}/thread_strings/include
)

# Install the executable
install(TARGETS thread_strings
  DESTINATION lib/${PROJECT_NAME}
)

