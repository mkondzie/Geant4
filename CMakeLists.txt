cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Exercise)
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.h)
add_executable(example_exercise src/example_exercise.cc ${sources} ${headers})
target_link_libraries(example_exercise ${Geant4_LIBRARIES})


set(EXCERCISE_SCRIPTS
  test_run.mac
  )

foreach(_script ${EXCERCISE_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()


add_custom_target(Exercise DEPENDS example_exercise)
