# Import Workflow

이 문서는 raw/reference 예제를 private archive로 선별 반영할 때 따르는 import 작업 순서를 정의합니다.

## 역할

- 실제 import 작업 순서의 기준 문서입니다.
- 포함/제외 정책은 [Import Policy](01_ImportPolicy.md)를 따릅니다.
- 작업 전후 체크리스트는 [Import Checklist](03_ImportChecklist.md)를 따릅니다.
- 파일/project/asset 검증은 [Import Verification](04_ImportVerification.md)를 따릅니다.
- 실제 Part별 판단 기록은 [Manifests](Manifests/)를 따릅니다.

## Import 상태 단계

| 단계                    | 의미                    | 완료 기준                              |
| --------------------- | --------------------- | ---------------------------------- |
| `1_code_split`        | 코드와 메모/문서 분리          | 소스의 장문 메모를 제거하거나 local-only 문서로 분리 |
| `2_build_check`       | archive 코드 실행 확인      | Debug x64 기준 build/run 결과 기록       |
| `3_diff_review`       | raw/original 대비 차이 확인 | 핵심 구현부와 변경 의도 기록                   |
| `4_refactor_check`    | 품질 검토                 | 리팩터링 필요 여부와 범위 기록                  |
| `5_ready_for_capture` | 촬영 준비                 | 사용자가 실행해 영상/사진을 찍을 수 있는 상태         |

## 작업 순서

1. Raw Part 구조 확인
   - raw 폴더의 최상위 구조를 읽습니다.
   - `.sln`, `.vcxproj`, shader, asset, capture/video 후보 위치를 확인합니다.
   - 제외 기준은 [Import Policy](01_ImportPolicy.md)를 따릅니다.

2. Import manifest 작성
   - 실제 파일 반영 전에 포함/제외 파일 목록을 문서로 남깁니다.
   - manifest에는 source, target, include candidates, exclude patterns, unresolved risks를 적습니다.
   - manifest 작성만으로는 파일을 복사하지 않습니다.

3. 선별 반영
   - manifest 기준으로 필요한 파일만 archive Part 폴더에 반영합니다.
   - build output, Visual Studio local state, raw-only 자료는 제외합니다.
   - 외부 asset은 출처와 라이선스가 불명확하면 복사하지 않거나 `검토 필요`로 분리합니다.

4. 경로 의존성 점검
   - `.sln`, `.vcxproj`, shader path, asset path가 raw 경로에 의존하는지 확인합니다.
   - archive 폴더명 변경으로 깨질 수 있는 상대 경로를 기록합니다.
   - 확인 전에는 build/run 상태를 `미확인`으로 둡니다.

5. Source/comment 정리
   - 기존 장문 학습 주석은 제거하고 필요한 내용은 note로 재작성합니다.
   - 코드에는 섹션 구분, 구현 의도, lifetime/path 주의처럼 유지보수에 필요한 주석만 남깁니다.
   - 코드 동작을 바꾸는 리팩터링은 별도 build/run 확인 단위로 진행합니다.

6. Build/run 확인
   - Visual Studio에서 `Debug x64`를 먼저 확인합니다.
   - 필요한 예제는 `Release x64`를 추가 확인합니다.
   - 실패하면 실패 원인과 다음 조치를 `Docs/03_Verification/build-run-matrix.md` 또는 예제 `status.md`에 기록한다.
   - Part4 `Examples` project는 단일 executable이므로 예제 이름의 `Ex` 뒤 4자리 숫자를 Visual Studio `Debugging > Command Arguments`에 넣어 실행합니다.

7. Demo/capture 정리
   - raw capture를 그대로 가져오지 않습니다.
   - archive 기준으로 직접 실행한 결과를 새로 캡처합니다.
   - 강의 화면, 슬라이드, 유료 자료, 문제/해설 캡처는 제외합니다.

8. 상태 갱신
   - Part README와 예제 `status.md`를 필요한 범위에서 갱신합니다.
   - import 당시 포함/제외 판단은 manifest에 기록합니다.
   - 최신 build/run/capture 상태는 `Docs/03_Verification/build-run-matrix.md` 또는 예제 `status.md`를 기준으로 한다.

## Manifest 기본 양식

```md
# Import Manifest: Part Name

> 이 문서는 import 당시 포함/제외 판단 기록입니다.
> 최신 build/run/capture 상태의 기준 문서가 아닙니다.

## Source / Target

- Source:
- Target:
- Import status:
- Public readiness:
- Build/run status:

## Include Candidates

- 

## Exclude Patterns

- 

## Unresolved Risks

- Asset/license:
- Path dependency:
- Private-only notes:

## Next Action

- 
```
