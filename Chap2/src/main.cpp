#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

int main(int argc, const char** argv) {
    
    SPDLOG_INFO("Start Program");
    // 출력 결과
    // [2024-11-02 18:55:14.145] [info] [main.cpp:4] Hello, OpenGL!
    // 시간, 로그 레벨, 실행 코드 소스, 실행 결과 순서로 출력

    SPDLOG_INFO("Initialize glfw"); //glfw 라이브러리 초기화
    if (!glfwInit()) { //초기화를 시도하고, 실패했다면
        const char* description = nullptr;
        glfwGetError(&description); //문자열에 에러 넣고
        SPDLOG_ERROR("failed to initialize glfw: {}", description); //출력
        return -1; //프로그램 종료
    }  

     SPDLOG_INFO("Create glfw window"); //glfw 윈도우 생성
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr);
    if (!window) { //실패하면 NULL이니까 0이 들어감
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate(); //라이브러리 종료
        return -1; //프로그램 종료
    }

    SPDLOG_INFO("Start main loop"); //glfw 루프 실행
    while (!glfwWindowShouldClose(window)) { //close 버튼 누르면 종료
        glfwPollEvents(); //키보드, 마우스 입력과 같은 이벤트 수집
    }

    glfwTerminate();
    return 0;
    
}

