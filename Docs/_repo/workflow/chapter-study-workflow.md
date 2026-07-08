# Chapter Study 정리 방식

이 문서는 raw 코드와 raw 학습 문서를 private archive용 chapter 문서로 재구성하는 작업 방식을 정리합니다.

목표 산출물은 다음 세 가지입니다.

- 빌드 및 시연 가능한 소스코드
- 직접 확인한 capture/video 또는 demo 기록
- issue/portfolio에 옮길 수 있는 chapter 문서

## 문서 배치 기준

- `Part*_Chapter*/`: 빌드 가능한 소스코드와 실행에 필요한 최소 파일을 둡니다.
- `Docs/Part*_Chapter*/ExampleName/README.md`: 예제별 핵심 키워드, 개념 정리, 구현 포인트, 고찰, 실행 결과, 공개 가능성 메모를 둡니다.
- `Docs/_repo/manifests/`: raw에서 archive로 넘길 후보와 제외 항목을 기록합니다.
- `local/`: 코드에서 분리한 원문 메모, raw 문서 원문, 최종 문서 초안을 둡니다.
- `Docs/_assets/`: 직접 촬영한 캡처/영상 파일이 필요할 때 둡니다.
- `Docs`의 workflow, readiness, raw mapping 문서는 작업 기준 문서이며 예제 산출물과 섞지 않습니다.

## 핵심 원칙

- raw 문서와 소스 주석은 참고 자료입니다. 그대로 복사하지 않고 archive 문서로 재작성합니다.
- 기존 소스코드 안의 학습용 장문 주석은 기본적으로 제거합니다.
- 코드에 남기는 주석은 작업한 부분, 중요한 구현 의도, 섹션 구분, 주의해야 할 lifetime/path 같은 정보로 제한합니다.
- 이해 과정, 헷갈렸던 점, 이론 설명, 참고 문서 연결은 source comment가 아니라 chapter 문서에 둡니다.
- chapter 문서에는 구현 흐름을 설명하는 짧은 핵심 코드 조각을 포함할 수 있습니다.
- 강의 원문 구조, 문제/해설 전문, 강의 자료 캡처, 유료 자료는 archive/public 후보로 확정하지 않습니다.

## 작업 순서

1. Chapter mapping 확인
   - `C:\ComputerGraphics\Docs_Graphics\_00_StartHere\01_ChapterDocMapping.md`에서 관련 raw 문서를 찾습니다.

2. Raw 문서 읽기
   - 직접 관련 문서와 필요한 technical docs만 읽습니다.
   - raw 문서의 원문 표현은 그대로 옮기지 않고, 내가 이해한 설명으로 재작성합니다.

3. Source comment 스캔
   - 소스코드에 남아 있는 질문, 이해 메모, TODO, 설명 주석을 확인합니다.
   - 문서로 옮길 내용과 코드에 남길 내용을 분리합니다.

4. Chapter 문서 작성
   - `Docs/Part*_Chapter*/ExampleName/README.md`에 작성합니다.
   - 핵심 키워드
   - 키워드 설명과 필요한 이론/기술
   - 핵심 구현 코드 위치
   - 구현 흐름을 보여주는 짧은 핵심 코드 조각
   - 헷갈렸던 지점과 이해한 내용
   - 추가 탐구와 고찰
   - 실행 결과와 build/run 상태

5. Source 정리
   - 기존 장문 학습 주석을 제거합니다.
   - 필요한 경우 짧은 섹션 주석을 새로 작성합니다.
   - 코드 동작을 바꾸는 리팩터링은 build/run 확인 단위와 분리합니다.

6. Demo 기록
   - 직접 실행해 확인한 결과만 capture/video 또는 demo note로 기록합니다.
   - 확인 전에는 `미확인`으로 둡니다.

## Source comment 기준

남길 수 있는 주석:

- 주요 섹션 구분: device setup, render target setup, texture upload, draw pass
- lifetime 주의: COM object release, owner, cleanup order
- 경로/런타임 주의: shader file path, runtime asset path
- 의도 설명이 없으면 오해하기 쉬운 구현 선택

제거하거나 chapter 문서로 옮길 주석:

- API 사용법을 길게 설명하는 학습 메모
- 질문/답변 형태의 이해 과정
- 강의 진행 순서나 실습문제 안내
- 이미 코드로 분명한 단순 설명
- 임시 디버깅 로그와 오래된 commented-out code

## Chapter 문서의 코드 조각 기준

문서의 코드 조각은 “파일 공개”가 아니라 “구현 설명”을 위한 발췌입니다. 전체 예제 파일을 붙여넣지 않고, 다음 기준에 맞는 짧은 조각만 사용합니다.

- 핵심 API 호출 순서가 보이는 부분
- descriptor에서 의미 있는 필드만 추린 부분
- 직접 작성하거나 수정한 구현 의도가 드러나는 부분
- 실행 흐름을 설명하기 위해 필요한 binding/update/draw 코드

코드 조각 아래에는 반드시 “이 코드가 어떤 흐름을 만든다”는 설명을 붙입니다.

## Chapter 문서 템플릿

```md
# Chapter / Example Name

## 목표

## 핵심 키워드

## 개념 정리

## 구현 포인트

## 핵심 코드 위치

## 핵심 코드 흐름

## 헷갈렸던 지점

## 이해한 내용

## 추가 탐구 / 고찰

## 실행 결과

## 공개 가능성
```
