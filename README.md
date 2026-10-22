# Graphics Study Archive

**그래픽스 학습·구현과 AI를 활용한 아카이브 구축 자동화**

DirectX11 기반 그래픽스 학습 코드와 일부 개인 확장 구현을 정리한 프로젝트다. 코드 주석과 옵시디언에 분산된 학습 기록을 예제 설명·실행 결과·검증 자료로 구성하고, 반복되는 정리·실행·기록 작업을 Codex로 자동화한다.

[포트폴리오 안내](PORTFOLIO.md) · [포트폴리오 PDF · 25쪽](https://razria93.github.io/Graphics_Study_Archive/portfolio/files/graphics-portfolio-20261022-v5.pdf) · [영상·검증 보고서](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/) · [실행 안내](#quickstart)

[![Bloom 예제의 처리 결과](Docs/_assets/captures/part1_chapter01-02_02_bloom_result.png)](Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)

*대표 결과 — ChatGPT 생성 입력 이미지에 Bloom을 적용한 학습 예제다. 직접 제작한 3D 장면이 아니라 이미지 후처리 결과이며, [입력·처리 과정·결과](Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md)를 함께 기록한다.*

## 이 저장소에서 볼 수 있는 경험

| 경험 구분 | 대표 사례 | 핵심 내용 | 바로 보기 |
| --- | --- | --- | --- |
| **AI 활용** | 아카이브 구축 자동화 | 작업 규격 설정·대표 예제 검토<br>자동화 확대·검수 | [진행 과정](#automation) |
| **문제 해결 01** | 자동 촬영 도구 보완 | 오류 대응 반복 원인 확인<br>정리 완료 판별 보완 | [문제·해결·검증](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/capture/index.html) |
| **문제 해결 02** | Assimp 호환 문제 | 임포트 구조 불일치 확인<br>Pivot 보존 설정 보정 | [옵션 비교·검증](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/assimp/index.html) |
| **그래픽스<br>학습·구현** | 렌더링과 GPU 연산 | 렌더링 기초·재질·후처리<br>애니메이션·GPU 연산 | [학습 범위](#learning)<br>[주제별 포트폴리오](PORTFOLIO.md#graphics) |

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

## 문제 해결과 검증

**01 · 자동 촬영 도구 — 오류 창 정리 완료를 판별하도록 보완**

오류 창 A를 닫은 뒤 나타난 B가 남아, 이전 오류와 새 실행 결과가 혼재하고 Codex의 대응이 반복되는 문제가 있었다. 사용자는 일정 간격으로 재확인하고, 오류 창이 없음을 확인한 뒤 다음 작업을 진행하도록 제안했다. Codex는 오류 창 정리와 결과 판별 코드를 보완했다.

[비교 재현 영상](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/capture/index.html#video) · [테스트 결과와 한계](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/capture/index.html#results)

공개 영상은 현상과 대응 절차를 설명하는 재현 시연이다. 이번 재검증은 테스트 창을 이용한 정리 코드의 정상·실패 조건 확인이며, 실제 DLL 복구·Clean/Rebuild·원래 촬영 재개를 검증한 결과로 표현하지 않는다.

**02 · Assimp — 임포트 구조를 로더의 처리 방식에 맞춤**

Pivot 보존으로 생성되는 보조 노드와 애니메이션 채널 구조가 기존 로더의 처리 방식과 맞지 않아 캐릭터 형태가 무너지는 사례다. 동일한 자산과 Assimp 버전에서 옵션 적용 전후의 구조와 보행 결과를 비교한다.

[옵션 비교 영상](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#comparison-video) · [구조 검사](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#case-3) · [당시 기록과 이번 작업 구분](https://razria93.github.io/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#case-4)

당시 보정의 최초 분석자·코드 작성자는 확인된 기록을 넘어 특정하지 않는다. 이번 Codex의 초기 자세 보완은 비교 양쪽에 동일하게 적용한 별도 작업으로 구분한다.

<a id="learning"></a>

## 그래픽스 학습 범위

| 파트 | 주요 학습 내용 | 코드·예제 설명 |
| --- | --- | --- |
| Part 1 | DirectX11 기초, 이미지 후처리, CPU Ray Tracing | [Chapter 01–02](Part1_Chapter01-02/README.md) · [Chapter 03](Part1_Chapter03/README.md) |
| Part 2 | 래스터화·UV 보간, 변환·조명, 메시 구성과 렌더링 파이프라인 | [Chapter 04](Part2_Chapter04/README.md) · [Chapter 05–08](Part2_Chapter05-08/README.md) |
| Part 3 | 선택·조작, Tessellation, Mapping, PBR·IBL, HDR·그림자 | [Chapter 09](Part3_Chapter09/README.md) · [Chapter 10–13](Part3_Chapter10-13/README.md) |
| Part 4 | Compute Shader, 입자·유체, 스켈레탈 애니메이션, 인스턴싱 | [Chapter 14–20](Part4_Chapter14-20/README.md) |

[학습 전체 지도](Docs/00_Index/study-map.md) · [개념 문서](Docs/00_Index/topic-map.md) · [실행 결과·Demo](Docs/00_Index/demo-map.md)

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

포트폴리오는 선정한 경험을 요약하고, 예제 README·개념 문서·검증 기록·Demo가 세부 근거를 제공한다. [포트폴리오 안내와 버전 기준](PORTFOLIO.md#version)에서 공개 PDF의 기준일과 갱신 방식을 확인할 수 있다.

<details>
<summary>문서 구조와 관리 안내</summary>

- [문서 전체 진입점](Docs/00_Index/README.md): 학습·개념·검증·Demo 지도
- [작업 기록](Docs/04_WorkLogs/README.md): 정리 과정과 검토 내역
- [공개 정책](Docs/06_Policies/publication-policy.md): 자료 공개 범위
- [문서 관리 도구](Docs/98_Tools/README.md): 규격·검사·작업 절차
- [저장소 작업 지침](AGENTS.md): 변경과 검증 기준

</details>
