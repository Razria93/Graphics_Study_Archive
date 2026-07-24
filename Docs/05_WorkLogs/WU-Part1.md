# WU-Part1 WorkLog

## 범위

| 항목 | 내용 |
| --- | --- |
| Work Unit | `WU-Part1` |
| 코드 범위 | `Part1_Chapter01-02`, `Part1_Chapter03`, `Portfolio_RayTracer` |
| 현재 pilot 대상 | `Part1_Chapter01-02/02_Bloom` |
| 주요 문서 축 | 코드 폴더 README, `02_Topics`, `03_Verification`, `04_Demos`, `06_Publication` |

## 현재 상태

| 항목 | 상태 | 비고 |
| --- | --- | --- |
| workflow 검증 | 진행 중 | `02_Bloom`으로 새 문서화 workflow를 검증한다. |
| code 조사 | 확인 | current code, raw/reference, origin 기준을 비교했다. |
| source comment inventory | 확인 | raw/reference의 학습 주석을 분류했다. |
| 기존 Docs stale 검토 | 확인 | pilot 초안과 Legacy PartDocs는 참고 전용으로 둔다. |
| README 이관 | 진행 중 | `02_Bloom` README 정본을 코드 폴더로 이동했다. |
| build/run | 미확인 | 직접 실행 전까지 상태를 바꾸지 않는다. |
| capture/video | 미확인 | 검증 후 evidence 후보를 만든다. |
| Issue/PR | 예정 | 문서 검수 후 draft를 작성한다. |

## 02_Bloom 작업 요약

- archive current code를 문서화 대상 코드로 둔다.
- raw/reference code와 docs는 학습 흔적 확인용으로만 읽고 tracked 문서에는 직접 이해한 설명으로 재작성한다.
- origin은 수정 전 기준점으로 사용한다.
- 기존 `Docs/01_Examples` 파일럿 README는 stale 초안으로 판단하고 정본 위치에서 내린다.
- 예제 README 정본은 `Part1_Chapter01-02/02_Bloom/README.md`로 이동한다.
- `PostProcessingAndBloom` topic은 CPU bloom 처리와 DirectX11 dynamic texture upload 중심으로 정리한다.

## 산출물 상태

| 산출물 | 문서 | 상태 |
| --- | --- | --- |
| Example README | `Part1_Chapter01-02/02_Bloom/README.md` | 작성 |
| Example redirect | 제거 완료 | `Docs/01_Examples` 폐기에 따라 삭제 |
| Verification | `Docs/03_Verification/Part1_Chapter01-02/verification-index.md` | `미확인` 유지 |
| Topic | `Docs/02_Topics/DirectX11Pipeline/PostProcessingAndBloom.md` | 작성 |
| Demo | `Docs/04_Demos/Part1_Chapter01-02/demo-index.md` | 후보 작성 |
| Publication | `Docs/06_Publication/candidate-list.md` | 검토 필요 |

## 다음 작업

1. 사용자가 `02_Bloom` 코드 폴더 README 내용을 검토한다.
2. `02_Bloom.sln` Debug x64 build/run을 직접 확인한다.
3. 실행 결과가 정상이라면 capture 후보를 만든다.
4. 검증 결과를 verification/demo 문서에 반영한다.
5. 같은 workflow를 Part1의 다음 대표 예제에 적용한다.
