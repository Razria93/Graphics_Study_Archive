# Candidate List

이 문서는 public subset 후보를 기록한다. 후보는 공개 확정이 아니며, 공개 전 체크리스트를 통과해야 한다.

| 후보 | 연결 문서 | 후보 이유 | 상태 | 비고 |
| --- | --- | --- | --- | --- |
| Graphics Study README 설명 | `Docs/00_Index`, `Docs/04_WorkLogs` | 직접 작성한 학습/포트폴리오 설명으로 재작성 가능 | 검토 필요 | public repo 구성 시 별도 작성 |
| Example 최소 설명 | 코드 폴더 README | 예제가 보여주는 개념을 짧게 설명 가능 | 검토 필요 | 강의 구조 복제 여부 확인 필요 |
| Topic 개념 설명 | `Docs/01_Topics` | 일반 graphics concept 설명으로 재작성 가능 | 검토 필요 | 코드/강의 표현 복제 금지 |
| Build/run 검증 요약 | `Docs/02_Verification` | 직접 확인한 결과를 포트폴리오 신뢰 근거로 사용 가능 | 검토 필요 | `미확인` 항목은 공개 근거로 사용하지 않음 |
| Demo capture/result | `Docs/03_Demos`, `Docs/_assets` | 직접 실행 결과 capture/result로 사용 가능 | 검토 필요 | `02_Bloom` result는 ChatGPT 생성 입력 이미지로 재생성 확인. `Docs/_assets` 승격 전까지 보류 |
| Work Unit summary | `Docs/04_WorkLogs` | 작업 과정과 결과 요약으로 사용 가능 | 검토 필요 | GitHub 본문은 별도 draft로 작성 |
| `02_Bloom` example README | `Part1_Chapter01-02/02_Bloom/README.md` | bloom 처리 흐름과 DirectX11 texture upload를 직접 설명 가능 | 검토 필요 | Debug/Release x64 build/run 확인. ChatGPT 생성 입력 이미지로 결과 재생성 확인 |
| `PostProcessingAndBloom` topic | `Docs/01_Topics/DirectX11Pipeline/PostProcessingAndBloom.md` | 일반적인 bloom 개념 설명으로 재작성 가능 | 검토 필요 | GPU bloom pipeline과 CPU 예제 한계를 명시해야 함 |

## 갱신 기준

- 공개 가능성을 판단하면 근거 문서와 체크리스트 결과를 연결한다.
- 부적합 후보는 `private-only.md` 또는 `excluded-material.md`로 이동한다.
- public repo로 옮길 때는 private archive 문서를 그대로 복사하지 않고 공개용 문장으로 다시 작성한다.
