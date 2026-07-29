# Candidate List

이 문서는 public subset 후보를 기록한다. 후보는 공개 확정이 아니며, 공개 전 체크리스트를 통과해야 한다.

| 후보 | 연결 문서 | 후보 이유 | 상태 | 판정 근거 | 필요 체크 | 비고 |
| --- | --- | --- | --- | --- | --- | --- |
| Graphics Study README 설명 | `Docs/00_Index`, `Docs/04_WorkLogs` | 직접 작성한 학습/포트폴리오 설명으로 재작성 가능 | 검토 필요 | private archive 설명이므로 public 문장으로 재작성 필요 | 표현 재작성, 민감 정보 확인 | public repo 구성 시 별도 작성 |
| Example 최소 설명 | 코드 폴더 README | 예제가 보여주는 개념을 짧게 설명 가능 | 검토 필요 | 강의 기반 구조와 표현이 섞일 수 있음 | 강의 구조 복제 여부 확인 |  |
| Topic 개념 설명 | `Docs/01_Topics` | 일반 graphics concept 설명으로 재작성 가능 | 검토 필요 | 개념 설명은 공개 가능성이 높으나 코드/강의 표현 복제 금지 | 표현 재작성, 출처 확인 |  |
| Build/run 검증 요약 | `Docs/02_Verification` | 직접 확인한 결과를 포트폴리오 확인 자료로 사용 가능 | 검토 필요 | 확인된 항목만 공개 설명에 사용 가능 | `미확인` 항목 제외, 검증 일자 확인 | 미확인 build/run 상태는 공개 후보가 아니라 검토 필요 상태로 둠 |
| Demo capture/result | `Docs/03_Demos`, `Docs/_assets` | 직접 실행 결과 capture/result로 사용 가능 | 검토 필요 | `02_Bloom` input/result 비교 이미지를 `Docs/_assets/captures`에 승격함 | asset 출처, metadata, 강의명/워터마크/개인 식별자 확인 | public 공개 확정은 아님 |
| `02_Bloom` Demo publication bundle | `Docs/03_Demos/Part1_Chapter01-02/02_Bloom.md`, `Docs/07_GitHub/issues/demo/demo_part1_chapter01-02.md`, `Docs/_assets/captures` | input/result와 구현 선택을 독립적인 시각·기술 설명으로 제공 가능 | public 후보 | 사용자 직접 생성 입력이며 외부 자료를 복제하지 않음. 워터마크·개인 식별자·application UI와 image metadata 검수 완료. 실행 입력과 tracked input의 SHA-256 일치. 이미지·코드 증거는 commit permalink로 고정 | 게시된 Demo Issue와 tracked 후보의 중요 변경 동기화 | 2026-07-29 최소 출처 검수 완료. [Demo Issue #9](https://github.com/Razria93/Graphics_Study_Archive/issues/9) 게시 완료. 생성 날짜, prompt 원문, provenance screenshot과 작업용 원본은 선택 기록이며 미보유가 게시 blocker는 아님 |
| Work Unit summary | `Docs/04_WorkLogs` | 작업 과정과 결과 요약으로 사용 가능 | 검토 필요 | WorkLog는 마감 snapshot이므로 public 문장으로 재작성 필요 | 최신 정본 링크 확인, 내부 판단 제거 | GitHub 본문은 `Docs/07_GitHub`에서 관리 |
| `02_Bloom` example README | `Part1_Chapter01-02/02_Bloom/README.md` | bloom 처리 흐름과 DirectX11 texture upload를 직접 설명 가능 | 검토 필요 | Debug/Release x64 build/run 확인. ChatGPT 생성 입력 이미지로 결과 재생성 확인 | 공개 문장 재작성, input/result 출처 확인 |  |
| `PostProcessingAndBloom` topic | `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md` | 일반적인 bloom 개념 설명으로 재작성 가능 | 검토 필요 | GPU bloom pipeline과 CPU 예제 한계를 명시해야 함 | Topic/Example 중복 축소, 표현 재작성 |  |

## 갱신 기준

- 공개 가능성을 판단하면 판단 자료와 체크리스트 결과를 연결한다.
- 부적합 후보는 `private-only.md` 또는 `excluded-material.md`로 이동한다.
- public repo로 옮길 때는 private archive 문서를 그대로 복사하지 않고 공개용 문장으로 다시 작성한다.
- 최종 판정일과 redaction ID는 후보가 공개 후보로 좁혀진 뒤 추가한다.
