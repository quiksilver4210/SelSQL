project(Tests_Stress)

SET(CMAKE_CXX_STANDARD 17)

FILE(GLOB Utils ${SOURCE_DIR}/Utils/*.cpp ${SOURCE_DIR}/Utils/Headers/*.h)

link_libraries(stdc++fs)
if (UNIX)
    add_executable(Tests_Stress main_test.cpp TestClass.cpp
            ../Headers/TestUtils.h . ../../Client/Client.cpp ../../Client/ClientUtils/ClientUtilsLin.cpp)
    link_libraries(stdc++fs)
endif ()

if (WIN32)
    add_executable(Tests_Stress main_test.cpp TestClass.cpp
            ../Headers/TestUtils.h . ../../Client/Client.cpp ../../Client/ClientUtils/ClientUtilsWin.cpp)
    target_link_libraries(Tests_Stress ws2_32)
endif ()

enable_testing()
target_link_libraries(Tests_Stress gtest gtest_main)