# Include all the directories
include_directories(
    ${PROJECT_BINARY_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/test
    ${Boost_INCLUDE_DIRS}
    ${netCDF_INCLUDE_DIR}
)

# Copy resource files for testing

file(GLOB resourceFiles "${PROJECT_SOURCE_DIR}/test/resources/*")

# add_library(additional "${PROJECT_SOURCE_DIR}/test/additional.cpp")

foreach(file ${resourceFiles})
    file(COPY ${file} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
endforeach(file)

# Compile and execute all sequential test files

file(GLOB testFiles "test_*.cpp")

foreach(file ${testFiles})
    get_filename_component(fileName ${file} NAME)

    string(REPLACE ".cpp" ".exe" exeName ${fileName})

    add_executable(${exeName} ${fileName})

    # # Link the library
    target_link_libraries(${exeName} par_calculation)
    # target_link_libraries(${exeName} additional)

    # Build test executable
    ADD_TEST(NAME build_${exeName} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${exeName} VERBOSE=1)

    # runs the executable test
    ADD_TEST(NAME run_${exeName} COMMAND ${exeName})

    # check that the build_test_cpp passed before running the exe.
    SET_TESTS_PROPERTIES(run_${exeName} PROPERTIES DEPENDS build_${exeName})


endforeach(file)

# # Compile and execute, for both ORCA grids, all the grid testss

# file(GLOB testFiles "orca_*.cpp")

# foreach(file ${testFiles})
#     get_filename_component(fileName ${file} NAME)

#     string(REPLACE ".cpp" ".exe" exeName ${fileName})

#     add_executable(${exeName} ${fileName})

#     # # Link the library
#     target_link_libraries(${exeName} Apecosm)
#     target_link_libraries(${exeName} additional)

#     # Build test executable
#     ADD_TEST(NAME build_${exeName} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${exeName} VERBOSE=1)

#     # runs the executable test
#     ADD_TEST(NAME run_orca1_${exeName} COMMAND ${exeName} orca1)
#     ADD_TEST(NAME run_orca2_${exeName} COMMAND ${exeName} orca2)

#     # check that the build_test_cpp passed before running the exe.
#     SET_TESTS_PROPERTIES(run_orca1_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca2_${exeName} PROPERTIES DEPENDS build_${exeName})

# endforeach(file)

# # Compile and execute, for different MPI versions, all the MPI tests

# file(GLOB mpitestFiles "mpi_*orca*.cpp")

# foreach(file ${mpitestFiles})
#     get_filename_component(fileName ${file} NAME)

#     string(REPLACE ".cpp" ".exe" exeName ${fileName})

#     add_executable(${exeName} ${fileName})

#     # # Link the library
#     target_link_libraries(${exeName} Apecosm)
#     target_link_libraries(${exeName} additional)

#     # Build test executable
#     ADD_TEST(NAME build_${exeName} COMMAND "${CMAKE_COMMAND}" --build ${CMAKE_BINARY_DIR} --target ${exeName} VERBOSE=1)

#     # runs the tests for different ORCA1 configs
#     ADD_TEST(NAME run_orca1_1x1_${exeName} COMMAND mpirun --oversubscribe -np 1 ${exeName} 1 1 orca1)
#     ADD_TEST(NAME run_orca1_3x4_${exeName} COMMAND mpirun --oversubscribe -np 12 ${exeName} 3 4 orca1)
#     ADD_TEST(NAME run_orca1_4x3_${exeName} COMMAND mpirun --oversubscribe -np 12 ${exeName} 4 3 orca1)
#     ADD_TEST(NAME run_orca1_1x4_${exeName} COMMAND mpirun --oversubscribe -np 4 ${exeName} 1 4 orca1)
#     ADD_TEST(NAME run_orca1_4x1_${exeName} COMMAND mpirun --oversubscribe -np 4 ${exeName} 4 1 orca1)

#     # check that the build_test_cpp passed before running the exe.
#     SET_TESTS_PROPERTIES(run_orca1_1x1_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca1_3x4_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca1_4x3_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca1_1x4_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca1_4x1_${exeName} PROPERTIES DEPENDS build_${exeName})

#     # runs the tests for different ORCA1 configs
#     ADD_TEST(NAME run_orca2_1x1_${exeName} COMMAND mpirun --oversubscribe -np 1 ${exeName} 1 1 orca2)
#     ADD_TEST(NAME run_orca2_3x4_${exeName} COMMAND mpirun --oversubscribe -np 12 ${exeName} 3 4 orca2)
#     ADD_TEST(NAME run_orca2_4x3_${exeName} COMMAND mpirun --oversubscribe -np 12 ${exeName} 4 3 orca2)
#     ADD_TEST(NAME run_orca2_1x4_${exeName} COMMAND mpirun --oversubscribe -np 4 ${exeName} 1 4 orca2)
#     ADD_TEST(NAME run_orca2_4x1_${exeName} COMMAND mpirun --oversubscribe -np 4 ${exeName} 4 1 orca2)

#     # check that the build_test_cpp passed before running the exe.
#     SET_TESTS_PROPERTIES(run_orca2_1x1_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca2_3x4_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca2_4x3_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca2_1x4_${exeName} PROPERTIES DEPENDS build_${exeName})
#     SET_TESTS_PROPERTIES(run_orca2_4x1_${exeName} PROPERTIES DEPENDS build_${exeName})

# endforeach(file)
