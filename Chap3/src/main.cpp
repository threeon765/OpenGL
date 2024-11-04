#include <spdlog/spdlog.h>
#include <glad/glad.h> //glad -> GLFW 순으로 넣을 것
#include <GLFW/glfw3.h>

//GLFW Callback 함수: 윈도우에 특정 이벤트 발생 시 작동하는 함수들
//창 크기 재설정
void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    SPDLOG_INFO("framebuffer size changed: ({} x {})", width, height);
    glViewport(0, 0, width, height); //그릴 화면의 위치, 크기 설정
}
//키보드 입력 관련 (ESC 누르면 꺼지는 기능)
void OnKeyEvent(GLFWwindow* window,
    int key, int scancode, int action, int mods) {
    SPDLOG_INFO("key: {}, scancode: {}, action: {}, mods: {}{}{}",
        key, scancode,
        action == GLFW_PRESS ? "Pressed" :
        action == GLFW_RELEASE ? "Released" :
        action == GLFW_REPEAT ? "Repeat" : "Unknown",
        mods & GLFW_MOD_CONTROL ? "C" : "-",
        mods & GLFW_MOD_SHIFT ? "S" : "-",
        mods & GLFW_MOD_ALT ? "A" : "-");
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

//FRAMEBUFFER SWAP: Back Buffer & Front Buffer를 준비하여 
//백에서 코드에 따라 수정 과정을 거치고 결과물을 프론트와 뒤바꾸기

int main(int argc, const char** argv) {
    
    SPDLOG_INFO("Start Program");
    // 출력 결과
    // [2024-11-02 18:55:14.145] [info] [main.cpp:4] Hello, OpenGL!
    // 시간, 로그 레벨, 실행 소스 코드 위치, 실행 결과 순서로 출력

    SPDLOG_INFO("Initialize glfw"); //glfw 라이브러리 초기화
    if (!glfwInit()) { //초기화를 시도하고, 실패했다면
        const char* description = nullptr;
        glfwGetError(&description); //문자열에 에러 넣고
        SPDLOG_ERROR("failed to initialize glfw: {}", description); //출력
        return -1; //프로그램 종료
    }  

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //사용하길 원하는 OpenGL 버전
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    SPDLOG_INFO("Create glfw window"); //glfw 윈도우 생성
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME,
      nullptr, nullptr);
    if (!window) { //실패하면 NULL이니까 0이 들어감
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate(); //라이브러리 종료
        return -1; //프로그램 종료
    }
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩 (OpenGL context가 생성된 후 (윈도우 생성 후)에 넣을 것)
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
    auto glVersion = glGetString(GL_VERSION); //OpenGL 버전 확인
    SPDLOG_INFO("OpenGL context version: {}", reinterpret_cast<const char*>(glVersion));

    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT); //프레임 버퍼의 경우 첫 호출은 수동으로 해야 함
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange); //콜백 함수 호출
    glfwSetKeyCallback(window, OnKeyEvent);

    SPDLOG_INFO("Start main loop"); //glfw 루프 실행
    while (!glfwWindowShouldClose(window)) { //close 버튼 누르면 종료
        glfwPollEvents(); //키보드, 마우스 입력과 같은 이벤트 수집 + 알아서 콜백 함수 명령 실행
        //렌더링 코드
        glClearColor(0.1f, 0.2f, 0.3f, 0.0f); //컬러 프레임버퍼 화면을 클리어할 색상 결정 (State-setting function)
        glClear(GL_COLOR_BUFFER_BIT); //진짜 프레임버퍼 클리어 (State-using function)
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
    
}

