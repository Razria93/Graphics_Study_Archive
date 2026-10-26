# 그래픽스 학습·구현과 AI 아카이브 자동화 포트폴리오

그래픽스 학습 기록을 설명 가능한 코드·문서·실행 자료로 정리하고, 그 반복 작업을 AI로 확장한 경험을 소개한다. 이 문서는 **25쪽 포트폴리오와 저장소의 상세 근거를 연결하는 안내**다.

[현재 프로젝트 안내](https://razria93.github.io/site/graphics.html) · [프로젝트 PDF · 25쪽](https://razria93.github.io/files/pdf/graphics-review.pdf) · [저장소 소개](README.md) · [비교 영상·검증 보고서](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/)

## 읽는 순서

| 포트폴리오 구간 | 살펴볼 내용 | 관련 자료 |
| --- | --- | --- |
| 표지·개요·색인·소개 (1–4쪽) | 프로젝트 목적과 전체 구성 | [README](README.md) |
| AI 아카이브 자동화 (5쪽) | 공통 규격, 대표 예제 검토, 작업 확대와 검수 | [적용 기록](Docs/04_WorkLogs/reviews/Part1_Chapter01-02.md) · [촬영 도구](Docs/98_Tools/example-window-recording.md) |
| 문제 해결 01 (6–8쪽) | 자동 촬영 중 오류 대응 반복, 정리 완료 판별과 실패 조건 | [영상·검증 보고서](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/capture/index.html) |
| 문제 해결 02 (9–11쪽) | Assimp의 FBX 구조 호환과 캐릭터 형태 복원 | [영상·검증 보고서](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html) |
| 그래픽스 학습·구현 (12–25쪽) | 학습 기반과 13개 상세 주제의 원리·구현·결과 | [아래 주제별 안내](#graphics) |

PDF의 3쪽 색인에서 각 본문으로 이동하고, 상세 페이지의 영상·문서·코드 링크로 근거를 확인한다. 그래픽스 내용이 우선이면 12쪽의 학습 범위부터 원하는 주제로 이동한다.

## 자동화 과정과 작업 기여

| 구분 | 확인되는 작업 |
| --- | --- |
| 사용자 작업 | 아카이브 목적과 문서 규격 설정, 촬영 방법·조건·제한사항 제시, 대표 예제 및 결과 검토, 예외 발생 시 해결 방향 조정 |
| Codex 작업 | 코드·기록 조사와 문서 작성, 요구사항에 따른 Windows API·FFmpeg 촬영 도구 구현, 반복 실행·촬영·형식 검사, 보완 의견에 따른 자료 수정 |

사용자가 공통 절차와 결과의 채택 기준을 정하고, 대표 예제에서 보완한 절차를 후속 예제로 확장한 과정에 초점을 둔다.

[공통 README 규격](Docs/98_Tools/templates/example-readme.md) · [대표 예제 적용 기록](Docs/04_WorkLogs/reviews/Part1_Chapter01-02.md) · [촬영 도구 설명](Docs/98_Tools/example-window-recording.md)

## 두 문제 해결 사례의 근거 범위

### 문제 해결 01 — 자동 촬영 도구

사용자는 오류 창을 닫은 뒤 일정 간격으로 잔존 여부를 재확인하고, 모두 정리됐음을 확인한 뒤 다음 작업을 진행하도록 제안했다. Codex는 정리 절차와 결과 판별 코드를 보완했다. 공개 영상은 현상·대응 순서를 설명하는 재현 시연이며, 기능 검증의 근거는 정리 코드에 대한 테스트 로그와 창 상태다.

- [전후 비교 재현 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/capture/index.html#video)
- [5개 조건·각 3회 재검증](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/capture/index.html#results)
- [대기 한도 보완 기록](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/capture/index.html#prior)

실패 조건에서의 통과는 오류 잔존을 감지하고 실패를 반환했다는 뜻이다. 실제 DLL 복구·Clean/Rebuild·원래 촬영 재개까지 검증한 것으로 확대하지 않는다.

### 문제 해결 02 — Assimp 스켈레탈 애니메이션

당시 Pivot 보존 옵션 보정과 이번 비교 검증을 구분한다.

- **당시 확인:** 당시 수정 결과는 본인이 직접 실행해 확인했다.
- **이번 비교 조건:** 이번 Codex가 보완한 초기 자세는 별도 재현 사본 양쪽에 동일하게 적용한 비교 조건이다. 캐릭터 형태 붕괴를 해결한 Assimp 옵션 변경과 별도로 기록한다.
- **원본 반영 여부:** 초기 자세 보완은 원본에는 반영하지 않았다.
- **확인 범위:** 구조 검사는 5개 클립, 실제 재생 비교는 보행 클립에 한정한다.
- **미검증 범위:** 다른 클립 전체 재생·장시간 실행·임의 자산은 미검증이다.

- [동일 자산·버전의 옵션 전후 비교](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#comparison-video)
- [구조 검사와 보행 재생 결과](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#case-3)
- [당시 기록·이번 작업·검증 범위](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/assimp/index.html#case-4)

<a id="graphics"></a>

## 그래픽스 학습·구현 주제별 안내

12쪽은 교재·강의 기반 학습, 일부 개인 확장과 이후 AI를 활용한 정리 범위를 설명한다. 아래 문서는 코드·실행 결과·한계를 연결하며, 실행 영상은 해당 문서에서 제공하는 경우 함께 확인할 수 있다.

| 번호·페이지 | 주제 | 예제 설명·실행 근거 |
| --- | --- | --- |
| 01 · 13쪽 | CPU Ray Tracing의 반사·굴절 | [반사](Docs/03_Demos/Part1_Chapter03/03_12_Reflection.md) · [굴절](Docs/03_Demos/Part1_Chapter03/03_13_Transparency.md) |
| 02 · 14쪽 | 원근 투영과 UV 보간 보정 | [원근 투영](Docs/03_Demos/Part2_Chapter04/08_PerspectiveProjection.md) |
| 03 · 15쪽 | DirectX11의 데이터·셰이더 연결 | [Texturing LightingSelf](Docs/03_Demos/Part2_Chapter05-08/06_TexturingLightingSelf.md) |
| 04 · 16쪽 | Normal Mapping의 법선 변환 | [Normal Mapping](Docs/03_Demos/Part3_Chapter10-13/11_02_NormalMapping.md) |
| 05 · 17쪽 | Height Mapping의 정점 변위 | [Height Mapping](Docs/03_Demos/Part3_Chapter10-13/11_03_HeightMapping.md) |
| 06 · 18쪽 | Tessellation의 분할 밀도 제어 | [Tessellation](Docs/03_Demos/Part3_Chapter10-13/10_05_Tessellation.md) |
| 07 · 19쪽 | PBR·IBL의 재질 입력과 조명 계산 | [Unreal PBR](Docs/03_Demos/Part3_Chapter10-13/12_01_UnrealPBR.md) |
| 08 · 20쪽 | HDR·Bloom의 후처리 흐름 | [HDR Pipeline](Docs/03_Demos/Part3_Chapter10-13/11_05_HDRPipeline.md) |
| 09 · 21쪽 | 화면 입력과 3D 선택·조작 | [Virtual Trackball](Docs/03_Demos/Part3_Chapter09/09_05_VirtualTrackball.md) |
| 10 · 22쪽 | 스켈레탈 애니메이션의 변환 흐름 | [Skeletal Animation](Docs/03_Demos/Part4_Chapter14-20/17_01_SkeletalAnimation.md) · [실행 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-demos/#skeletal-animation) |
| 11 · 23쪽 | GPU Blur의 구현 경로와 리소스 교대 | [Compute Shader Blur](Docs/03_Demos/Part4_Chapter14-20/14_02_Blur.md) |
| 12 · 24쪽 | GPU 연기의 시뮬레이션과 볼륨 렌더링 | [Realtime Smoke](Docs/03_Demos/Part4_Chapter14-20/16_04_RealtimeSmoke.md) · [실행 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-demos/#realtime-smoke) |
| 13 · 25쪽 | 잔디 인스턴싱과 셰이더 변형 | [Grass](Docs/03_Demos/Part4_Chapter14-20/18_02_Grass.md) · [실행 영상](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-demos/#grass) |

개별 기능의 학습·개인 확장 범위는 예제 README와 [학습 출처 안내](NOTICE.md)를 따른다. 포트폴리오의 문서화·자료 정리를 기존 학습 코드 전체의 독자 구현으로 해석하지 않는다.

<a id="version"></a>

## 공개본과 갱신 기준

| 자료 | 연결·기준 |
| --- | --- |
| 현재 안내 | [프로젝트 페이지](https://razria93.github.io/site/graphics.html). |
| 현재 프로젝트 PDF | [graphics-review.pdf · 25쪽](https://razria93.github.io/files/pdf/graphics-review.pdf). 현재 공개 프로젝트 페이지에서 연결하는 파일이다. |
| 통합 PDF | [combined-review.pdf · 62쪽](https://razria93.github.io/files/pdf/combined-review.pdf#page=39). 그래픽스 구간은 39–62쪽이며 개별본 표지를 제외한다. |
| 이전 제출본 보존 | [2026-10-22 v5 · 25쪽](https://razria93.github.io/Graphics_Study_Archive/portfolio/files/graphics-portfolio-20261022-v5.pdf). 당시 최종 제출용 파일이며 현재 안내와 구분한다. |

- 이 문서의 주제별 쪽수는 개별본 25쪽 기준이다.
- 페이지의 포트폴리오 업데이트 표기는 2026.10.25이며, 개별 구현·검증의 수행일을 뜻하지 않는다.

<details>
<summary>이전 편집 이력·파일명 안내</summary>

기존 표지·개요·PROFILE·CONTACT 통일 및 FBX 안내의 9–11쪽 정정 이력은 위의 이전 제출본에 해당한다.

파일명의 `review`는 보존된 이름이며 새 검증 수행을 뜻하지 않는다.

</details>

### 보존·갱신 원칙

- **원본 보존:** 기존 제출용 PPTX·PDF와 공개 PDF 주소는 보존한다. 현재 안내는 별도 공개 경로로 제공하며 이전 파일을 대체하지 않는다.
- **갱신 방식:** 내용 변경 시 새 버전 PDF를 추가하고 이 안내의 날짜·페이지 범위·대표 링크를 함께 갱신한다. 기존 버전 파일과 주소는 보존한다.
- **문서 기준:** 포트폴리오는 해당 날짜의 요약본이다. 예제 구현·검증의 상세 내용은 연결된 저장소 문서를 기준으로 확인한다.

[저장소 메인으로](README.md) · [영상·검증 자료로](https://razria93.github.io/site/details/Graphics_Study_Archive/portfolio-evidence/)
