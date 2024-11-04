# Graphics pipeline<br>
그림이 그려지는 과정<br>
## Application<br>
그리고 싶은 위치, 색상 등을 결정 (OpenGL 함수 호출)<br>
## Geometry Processing<br>
정점 단위 처리 및 위치 결정 (GPU)<br>
## Rasterization<br>
정점 -> 픽셀 (GPU)<br>
## Pixel Processing<br>
픽셀 단위 처리 및 색상 결정 (GPU)<br>
# Shader
각 파이프라인 단계마다 GPU 상에서 실행되는 작은 프로그램 (GLSL로 작성)<br>
OpenGL은 Vertex & Fragment shader 요구<br>