# Graphics Study Archive

교재·강의 기반 그래픽스 예제를 학습·구현하고, 원리·코드·실행 결과를 연결한 아카이브다. 일부 개인 확장 구현을 포함하며, 코드 주석과 옵시디언에 분산된 기록의 문서화·실행·촬영·형식 검사를 Codex로 정리하고 자동화한다.

[프로젝트 안내](https://razria93.github.io/site/graphics.html) · [프로젝트 PDF · 25쪽](https://razria93.github.io/files/pdf/graphics-review.pdf) · [주제별 포트폴리오](PORTFOLIO.md) · [실행 안내](#quickstart)

![기존 학습 예제의 잔디 인스턴싱과 바람 변형 실행 화면](https://razria93.github.io/site/assets/graphics.jpg)

*기존 학습 예제 실행 기록 · 잔디 인스턴싱과 바람 변형. 교재·강의 기반 예제이며 독자 설계나 통제된 성능 측정 결과를 뜻하지 않는다.*

[그래픽스 학습·구현](#learning) · [자동화·문제 해결](#automation)

## 프로젝트 개요·작업 범위

| 항목 | 내용 |
| --- | --- |
| 성격 | 교재·강의 기반 학습 프로젝트 · 일부 개인 확장 구현 |
| 학습·정리 기간 | 학습 2025.07–11 · 아카이브 정리 2026.07 이후 |
| 구현 환경 | C++ · HLSL · DirectX11 |
| 주요 범위 | 렌더링 파이프라인·재질·후처리·입력·애니메이션·GPU 연산 |
| 자동화 도구 | Codex · Windows API · FFmpeg |

- **본인 작업:** 그래픽스 예제를 학습·구현하고, 문서·촬영 규격과 조건을 제시했다. 대표 산출물과 실행 결과를 검토하며 오류 대응 방향을 보완했다.
- **Codex 작업:** 코드·학습 기록 조사, 문서화와 촬영 도구 구현, 반복 실행·촬영·검사를 수행했다. 별도 재현 사본의 수정·추가 검증은 당시 작업과 구분한다.

<a id="learning"></a>

## 대표 학습·구현

| 사례 | 원리·구현과 결과 해석 | 자료 |
| --- | --- | --- |
| DirectX11 데이터·셰이더 연결 | 정점·인덱스·텍스처·상수 버퍼를 연결하고 DrawIndexed로 출력한다. 실제 바인딩 코드와 결과를 설명하며 개별 입력 효과를 분리한 비교 실험은 아니다. | [데이터·셰이더 연결 예제 설명](Docs/03_Demos/Part2_Chapter05-08/06_TexturingLightingSelf.md) · [PDF 15쪽](https://razria93.github.io/files/pdf/graphics-review.pdf#page=15) |
| GPU Blur 리소스 교대 | X 패스는 A 읽기·B 쓰기, Y 패스는 B 읽기·A 쓰기로 SRV/UAV를 교대한다. 바인딩 해제는 GPU 완료 대기가 아니며 성능 비교를 제시하지 않는다. | [GPU Blur 예제 설명](Docs/03_Demos/Part4_Chapter14-20/14_02_Blur.md) · [PDF 23쪽](https://razria93.github.io/files/pdf/graphics-review.pdf#page=23) |

### 전체 학습 범위

| 파트 | 주요 학습 내용 | 코드·예제 설명 |
| --- | --- | --- |
| Part 1 | DirectX11 기초, 이미지 후처리, CPU Ray Tracing | [Chapter 01–02](Part1_Chapter01-02/README.md) · [Chapter 03](Part1_Chapter03/README.md) |
| Part 2 | 래스터화·UV 보간, 변환·조명, 메시 구성과 렌더링 파이프라인 | [Chapter 04](Part2_Chapter04/README.md) · [Chapter 05–08](Part2_Chapter05-08/README.md) |
| Part 3 | 선택·조작, Tessellation, Mapping, PBR·IBL, HDR·그림자 | [Chapter 09](Part3_Chapter09/README.md) · [Chapter 10–13](Part3_Chapter10-13/README.md) |
| Part 4 | Compute Shader, 입자·유체, 스켈레탈 애니메이션, 인스턴싱 | [Chapter 14–20](Part4_Chapter14-20/README.md) |

[학습 전체 지도](Docs/00_Index/study-map.md) · [개념 문서](Docs/00_Index/topic-map.md) · [실행 결과·Demo](Docs/00_Index/demo-map.md)


<a id="automation"></a>

## AI로 반복 작업을 확장한 과정

학습 결과를 설명할 수 있는 자료로 정리하기 위해, 예제마다 반복되는 작업에 공통 규격과 순서를 적용한다. 대표 예제로 규격을 검토한 뒤 Codex의 작업 범위를 문서 정리·실행·촬영·형식 검사로 넓힌 과정이다.

| 단계 | 사용자 작업 | Codex 작업 |
| --- | --- | --- |
| 01 · 정리 기준 설정 | 문서·실행 결과 규격과 촬영 방법·조건·제한사항 제시 | 자료 조사·문서 초안 작성, 요구사항에 따른 촬영 도구 구현 |
| 02 · 대표 예제 적용·보완 | 대표 예제 결과 검토와 보완 의견 제시 | 예제 문서·검증 기록·Demo 연결과 작업 절차 보완 |
| 03 · 후속 예제로 확대 | 진행 관찰, 예외 발생 시 맥락과 해결 방향 조정 | 후속 예제 정리, 실행·촬영·형식 검사 |
| 04 · 산출물 검수 | 학습 내용·정리 목적과 자료의 대응 확인 | 보완 의견에 따른 자료 수정과 문서·링크 정리 |

Windows API·FFmpeg 기반 도구는 예제의 시각적 실행 결과를 사진·영상으로 남기는 데 사용한다. 사용자가 목적과 조건을 정하고, 수집 자료와 문서를 검토하는 방식이다.

[대표 예제 적용 기록](Docs/04_WorkLogs/reviews/Part1_Chapter01-02.md) · [공통 README 규격](Docs/98_Tools/templates/example-readme.md) · [촬영 도구](Docs/98_Tools/example-window-recording.md)

## 문제 해결

### 01 · 자동 촬영 도구 — 오류 창 정리 완료를 판별하도록 보완

오류 창 A를 닫은 뒤 나타난 B가 남아, 이전 오류와 새 실행 결과가 혼재하고 Codex의 대응이 반복되는 문제가 있었다. 사용자는 일정 간격으로 재확인하고, 오류 창이 없음을 확인한 뒤 다음 작업을 진행하도록 제안했다. Codex는 오류 창 정리와 결과 판별 코드를 보완했다.

[비교 재현 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/capture/index.html#video) · [테스트 결과와 한계](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/capture/index.html#results)

실패 감지 조건의 충족은 오류 창 정리 성공과 구분합니다. 실제 DLL 복구·Clean/Rebuild·원래 촬영 재개까지 확인한 결과는 아닙니다.

### 02 · Assimp — 임포트 구조를 로더의 처리 방식에 맞춤

Pivot 보존으로 생성되는 보조 노드와 애니메이션 채널 구조가 기존 로더의 처리 방식과 맞지 않아 캐릭터 형태가 무너지는 사례다. 동일한 자산과 Assimp 버전에서 옵션 적용 전후의 구조와 보행 결과를 비교한다.

[옵션 비교 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#comparison-video) · [구조 검사 결과](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#case-3) · [당시 기록과 이번 작업 구분](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#case-4)

초기 자세 보완은 별도 재현 사본 양쪽에 동일하게 적용했으며 원본에는 반영하지 않았습니다. 실제 재생 비교는 보행 클립에 한정합니다.

## 검증 조건·한계

### 자동 촬영 도구

- **자료 성격:** 공개 영상은 현상과 대응 절차를 설명하는 재현 시연이다.
- **검증 방법:** 테스트 창 5개 조건을 각 3회 확인했다. 이번 재검증은 테스트 창을 이용한 정리 코드의 정상·실패 조건 확인이다.
- **결과 해석:** 실패 감지 조건의 충족은 오류 창 정리 성공을 의미하지 않는다. 지연 오류는 감지 후 실패 종료하고 자동 재정리하지 않는다.
- **별도 회귀 테스트:** 완료 대기 한도 5초의 원본이 실패하고 한도만 15초로 늘린 사본이 통과했으나, 실패 원인은 확정하지 못했다.
- **확인하지 않은 범위:** 실제 DLL 복구·Clean/Rebuild·원래 촬영 재개를 검증한 결과로 표현하지 않는다.

### Assimp 구조 호환

- **당시 확인:** 당시 수정 결과는 본인이 직접 실행해 확인했다.
- **이번 비교 조건:** 별도 재현 사본에서 Codex가 초기 자세 보완을 양쪽에 동일하게 적용하고 Pivot 옵션을 바꿔 수행했다.
- **원본 반영 여부:** 초기 자세 보완은 원본에 반영하지 않았다.
- **확인 범위:** 구조 검사는 5개 클립·실제 재생 비교는 보행 클립에 한정한다.
- **미검증 범위:** 다른 클립 전체 재생·장시간 실행·임의 자산은 미검증이다.

## 관련 자료

- [현재 프로젝트 안내](https://razria93.github.io/site/graphics.html) · [현재 프로젝트 PDF · 25쪽](https://razria93.github.io/files/pdf/graphics-review.pdf)
- [통합 PDF · 그래픽스 39–62쪽](https://razria93.github.io/files/pdf/combined-review.pdf#page=39) · [학습 예제 실행 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-demos/index.html)
- [이전 제출 PDF · 2026-10-22 v5](https://razria93.github.io/Graphics_Study_Archive/portfolio/files/graphics-portfolio-20261022-v5.pdf): 보존본. [버전 안내](PORTFOLIO.md#version)에서 현재 안내와 구분한다.

<a id="quickstart"></a>

## 예제 실행 시작하기

기본 환경은 Windows, Visual Studio 2022의 C++ 데스크톱 개발 도구(v143), Windows SDK 10.x다. 예제별 추가 라이브러리와 실행 조건은 해당 폴더의 README와 검증 기록을 확인한다.

```bash
git clone https://github.com/Razria93/Graphics_Study_Archive.git
```

1. [01_DX11InitAndImGui](Part1_Chapter01-02/01_DX11InitAndImGui/README.md)의 `01_DX11InitAndImGui.sln`을 Visual Studio에서 연다.
2. 시작 프로젝트를 `01_DX11InitAndImGui`, 구성을 `Debug | x64`로 설정하고 빌드·실행한다.
3. 셰이더 파일을 찾지 못하면 실행 작업 디렉터리가 해당 예제 폴더인지 확인한다.

[빌드·실행 기준](BUILD.md) · [기존 Debug/Release 검증 기록](Docs/02_Verification/Part1_Chapter01-02/verification-index.md) · [알려진 이슈](Docs/02_Verification/known-issues.md)

실행 상태는 연결한 검증 기록의 환경과 범위를 기준으로 확인한다.

## 학습 출처와 작업 범위

교재·강의 기반 예제를 학습하며 구현·실행한 코드와 일부 개인 확장을 포함한다. 모든 기능을 독자 설계한 프로젝트로 주장하지 않으며, 개별 예제의 출처와 확장 범위는 각 README와 [NOTICE](NOTICE.md)를 따른다. 이후 Codex를 활용한 조사·문서화·촬영·재검증은 기존 학습 구현과 구분한다.

**Bloom 예제의 입력 이미지 출처**

Bloom 예제는 ChatGPT 생성 입력 이미지에 후처리를 적용한 결과이며 직접 제작한 3D 장면이 아니다. [입력·처리 과정·결과](Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)와 출처 설명은 해당 사례에서 확인할 수 있다.

포트폴리오는 선정한 경험을 요약하고, 예제 README·개념 문서·검증 기록·Demo가 세부 근거를 제공한다. [포트폴리오 안내와 버전 기준](PORTFOLIO.md#version)에서 공개 PDF의 기준일과 갱신 방식을 확인할 수 있다.

<details>
<summary>문서 구조와 관리 안내</summary>

- [문서 전체 진입점](Docs/00_Index/README.md): 학습·개념·검증·Demo 지도
- [작업 기록](Docs/04_WorkLogs/README.md): 정리 과정과 검토 내역
- [공개 정책](Docs/06_Policies/publication-policy.md): 자료 공개 범위
- [문서 관리 도구](Docs/98_Tools/README.md): 규격·검사·작업 절차
- [저장소 작업 지침](AGENTS.md): 변경과 검증 기준

</details>
