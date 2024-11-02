# make solution file
# cmake -Bbulid . -DCMAKE_BUILD_TYPE=Debug
# -B빌드명 .(CMakeLists 경로)

# make build file
# cmake --build build
# --build 솔루션 디렉토리

# 디버깅을 위해서 WorkPlace를 Chap 단위로 항상 갈아주자

cmake_minimum_required(VERSION 3.13) # cmake 버전 3.13 이상 사용

# 한글 지원
add_compile_options(/utf-8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /utf-8")

set(PROJECT_NAME Chap2) # 프로젝트 이름 Chap2
set(CMAKE_CXX_STANDARD 17) # C++ 버전 17

set(WINDOW_NAME "Hello, OpenGL!") # 윈도우 이름 및 해상도 설정
set(WINDOW_WIDTH 960)
set(WINDOW_HEIGHT 540)

project(${PROJECT_NAME}) # Chap2라는 이름으로 프로젝트 생성 (일명 target)
add_executable(${PROJECT_NAME} src/main.cpp) # main.cpp 파일을 통해 빌드

# 파일 분할
include(Dependency.cmake)

# 우리 프로젝트에 include / lib 관련 옵션 추가
target_include_directories(${PROJECT_NAME} PUBLIC ${DEP_INCLUDE_DIR}) # 타겟에 install/include 옵션 추가 (헤더는 컴파일 단계에서 포함)
target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR}) # 타겟에 install/lib 옵션 추가 (라이브러리는 링크 단계에서 포함)
target_link_libraries(${PROJECT_NAME} PUBLIC ${DEP_LIBS}) # 사용할 실제적인 라이브러리 설정

target_compile_definitions(${PROJECT_NAME} PUBLIC # 매크로 상수 설정
    WINDOW_NAME="${WINDOW_NAME}"
    WINDOW_WIDTH=${WINDOW_WIDTH}
    WINDOW_HEIGHT=${WINDOW_HEIGHT}
    )

# Dependency들이 먼저 build 될 수 있게 관계 설정
add_dependencies(${PROJECT_NAME} ${DEP_LIST}) 
# 병렬 처리가 되어버리면 망하는겨...