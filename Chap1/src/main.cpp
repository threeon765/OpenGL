/*
//CMake 세팅에 대해서
cmake_minimum_required(VERSION 3.13) //프로젝트에서 사용하는 CMake의 최소 버전

set(PROJECT_NAME Chap2) //PROJECT_NAME 변수 = Chap2
set(CMAKE_CXX_STANDARD 17) //C++ 표준 17

project(${PROJECT_NAME}) //프로젝트 생성 (${}으로 써야 변수로 사용 가능)
add_executable(${PROJECT_NAME} src/main.cpp) //실행 파일 지정


//빌드를 위한 VS 솔루션 만들기
//터미널에 밑 명령어를 입력
//cmake -Bbulid . -DCMAKE_BUILD_TYPE=Debug
//-B빌드명 .(CMakeLists 경로)


//실행 파일 만들기
//cmake --build build
//--build 솔루션 디렉토리

//결론
//CMake의 역할은 각 OS가 선호하는 빌드 파일들을 생성하는 거임

//이 모든 과정은 커맨드로 딸깍 가능 ㅋㅋ
//디버그 ctrl + F5, 빌드 F7

//Git 사용
//Git Fork라는 프로그램을 사용하면 편리하게 관리 가능

//.gitignore
//변경 및 업데이트를 하지 않아도 되는 폴더 디렉토리를 써두면 그것을 무시할 수 있다
*/

#include <iostream>

int main(int argc, const char** argv) {
    std::cout << "hello, world" << std::endl;
    return 0;
}