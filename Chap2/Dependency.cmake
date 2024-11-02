# 외부 라이브러리 사용하기
# 라이브러리를 불러오는 방식은 운영체제와 에디터마다 다르지만
# cmake를 통해 이것을 통일시킬 수 있으므로 크로스 플랫폼이 가능하다

# ExternalProject 관련 명령어 셋 추가
include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib)

# spdlog: fast logger library
ExternalProject_Add(
    dep-spdlog # 추가한 라이브러리를 사용하기 위한 명칭 (일명 target)
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git" # 사용할 라이브러리의 리포 주소
    GIT_TAG "v1.x" # branches 또는 tags의 이름
    GIT_SHALLOW 1 # Shallow(최신 버전만 사용) True(활성화), 비활성화 시 모든 commit의 버전을 다운받게 됨
    UPDATE_COMMAND "" # 자동 업데이트 비활성화
    PATCH_COMMAND "" # 직접 받은 코드 수정 비활성화
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} # Configure 시 인자 설정: 빌드 결과 저장 위치 = DEP_INSTALL_DIR
    # DEP_INSTALL_DIR은 위에 변수 설정한 PROJECT_BINARY_DIR/install, PROJECT_BINARY_DIR은 build 파일
    # 즉 이 외부 라이브러리를 사용하기 위한 파일들을 install 경로에 다운하는거
    TEST_COMMAND "" # 자동 TEST 비활성화
)

# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep-spdlog)
set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) # debug 모드일 경우 d를 붙일 것 (추후 자세하게 다룸)


# OpenGL은 그래픽을 지원하는 API에 불가함
# GLFW: Creating windows, contexts, and surfaces,
# Receiving inputs and events
ExternalProject_Add(
    dep_glfw
    GIT_REPOSITORY "https://github.com/glfw/glfw.git"
    GIT_TAG "3.4"
    GIT_SHALLOW 1
    UPDATE_COMMAND "" PATCH_COMMAND "" TEST_COMMAND ""
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR}
        -DGLFW_BUILD_EXAMPLES=OFF # 예제, 테스트, 문서 제외
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
    # 이런 옵션들의 존재는 사용하려는 외부 라이브러리의 리포에서 cmakelist의 option에서 확인 가능
    )
set(DEP_LIST ${DEP_LIST} dep_glfw)
set(DEP_LIBS ${DEP_LIBS} glfw3)