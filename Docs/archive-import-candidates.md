# Archive Import 후보 검토표

이 문서는 `C:\ComputerGraphics` raw/reference repo에서 `C:\Graphics_Study_Archive` private archive로 옮길 수 있는 후보를 파일 또는 예제 단위로 검토하기 위한 표입니다.

현재 단계에서는 실제 파일을 복사하지 않습니다. 후보 분류와 다음 확인 작업만 기록합니다.

## 상태값

`Import status`는 raw에서 private archive로 가져올 수 있는지를 표시합니다. `Public readiness`는 archive로 정리된 뒤 public repo 후보가 될 수 있는지를 별도로 표시합니다.

| 상태 | 의미 |
| --- | --- |
| `archive 후보` | private archive로 옮겨 정리할 수 있는 후보입니다. |
| `private 전용` | raw 또는 private archive 안에서만 유지할 자료입니다. |
| `검토 필요` | 저작권, 라이선스, 개인정보, 경로 의존성 확인이 필요합니다. |
| `제외` | archive/public 이동 대상이 아닙니다. |

## 검토 항목

| 항목 | 확인 내용 |
| --- | --- |
| Source | raw repo의 참고 위치 |
| Target | archive repo의 예상 위치 |
| Import status | `archive 후보`, `private 전용`, `검토 필요`, `제외` 중 하나 |
| Public readiness | `public 후보`, `private 전용`, `검토 필요`, `제외` 중 하나 |
| Build/run status | 직접 확인 전에는 `미확인` |
| Copyright/license note | 강의 원문, 유료 자료, 외부 asset, 라이선스 확인 내용 |
| Personal-info check | 개인 경로, 계정, 제출 기록, local-only 메모 포함 여부 |
| Next action | 다음 확인 또는 정리 작업 |

## 초기 후보 목록

| Source | Target | Import status | Public readiness | Build/run status | Copyright/license note | Personal-info check | Next action |
| --- | --- | --- | --- | --- | --- | --- | --- |
| `C:\ComputerGraphics\_00_Graphics_Portfolio\16-01_Sampling` | `Portfolio_RayTracer/16-01_Sampling` | 검토 필요 | 검토 필요 | 미확인 | 대표 ray tracer 후보. `12_Raytracing_Refactoring.sln`, texture asset, 강의 기반 코드 범위 확인 필요 | 미확인 | `.sln`, `.vcxproj`, shader path, asset path 확인 |
| `C:\ComputerGraphics\_00_Graphics_Portfolio\12-06_Raytracing_Refactoring_Complete` | `Portfolio_RayTracer` reference | 검토 필요 | 검토 필요 | 미확인 | refactoring complete reference. 대표 후보의 설명/비교용으로만 우선 검토 | 미확인 | `16-01_Sampling`과 중복/차이 확인 |
| `C:\ComputerGraphics\_00_Graphics_Portfolio\15-01_Texturing` | `Portfolio_RayTracer` reference | 검토 필요 | 검토 필요 | 미확인 | texture sampling reference. texture asset 출처 확인 필요 | 미확인 | texture dependency와 license 확인 |
| `C:\ComputerGraphics\_00_Graphics_Portfolio\_TextureRaw` | 없음 | 검토 필요 | 검토 필요 | 해당 없음 | raw texture reference. 통째 이동 금지, 출처/라이선스 확인 필요 | 미확인 | 필요한 asset만 출처 확인 후 별도 판단 |
| `C:\ComputerGraphics\Part1_Chapter03` | `Part1_Chapter03` | 검토 필요 | 검토 필요 | 미확인 | CPU ray tracing study code의 강의 기반 범위 확인 필요 | 미확인 | P0 ray tracing 예제 후보만 선별 |
| `C:\ComputerGraphics\Part1_Chapter01-02` | `Part1_Chapter01-02` | 검토 필요 | 검토 필요 | 미확인 | `02_Bloom` 입력 이미지 출처/라이선스 확인 필요 | 미확인 | [Part1 manifest](import-manifests/Part1_Chapter01-02.md) 기준으로 선별 복사 여부 결정 |
| `C:\ComputerGraphics\Part2_Chapter04` | `Part2_Chapter04` | 검토 필요 | 검토 필요 | 미확인 | software rasterization study code 범위 확인 필요 | 미확인 | depth buffer 대표 예제 후보 확인 |
| `C:\ComputerGraphics\Part2_Chapter05-08` | `Part2_Chapter05-08` | 검토 필요 | 검토 필요 | 미확인 | D3D11 pipeline, shader, model/texture asset 출처 확인 필요 | 미확인 | lighting/bloom 후보와 asset 의존성 확인 |
| `C:\ComputerGraphics\Part3_Chapter09` | `Part3_Chapter09` | 검토 필요 | 검토 필요 | 미확인 | picking 예제의 코드/asset 출처 확인 필요 | 미확인 | mouse picking 대표 예제 후보 확인 |
| `C:\ComputerGraphics\Part3_Chapter10_13` | `Part3_Chapter10-13` | 검토 필요 | 검토 필요 | 미확인 | PBR, texture, model asset 라이선스 확인 필요 | 미확인 | PBR/shadow 대표 예제 후보 확인 |
| `C:\ComputerGraphics\Part3_Chapter10_13_2` | `Part3_Chapter10-13` | 검토 필요 | 검토 필요 | 미확인 | `Part3_Chapter10_13`와 중복/후속 관계 확인 필요 | 미확인 | archive 대상 폴더를 하나로 합칠지 판단 |
| `C:\ComputerGraphics\Part4_HongLabGraphics` | `Part4_Chapter14-20` | 검토 필요 | 검토 필요 | 미확인 | compute/simulation 예제와 asset 출처 확인 필요 | 미확인 | Ex1402_Blur, particle 후보 확인 |
| `C:\ComputerGraphics\Part4_HongLabGraphics_2` | `Part4_Chapter14-20` | 검토 필요 | 검토 필요 | 미확인 | `Part4_HongLabGraphics`와 중복/후속 관계 확인 필요 | 미확인 | archive 대상 폴더를 하나로 합칠지 판단 |
| `C:\ComputerGraphics\Docs_Graphics` | `Docs/` | 검토 필요 | 검토 필요 | 해당 없음 | 계획 문서, 학습 노트, private-only 기록 포함 가능성 확인 필요 | 미확인 | 공개 가능한 설명/검증 기록만 선별 |
| `C:\ComputerGraphics\export-candidates` | `Docs/archive-import-candidates.md` | archive 후보 | private 전용 | 해당 없음 | 후보 기록 문서로만 참고 | 확인 필요 | raw 후보 기록과 archive 검토표 동기화 |
| `C:\ComputerGraphics\OriginalExamples` | 없음 | 제외 | 제외 | 해당 없음 | 원본 기준점으로만 참고, 통째 이동 금지 | 미확인 | 필요한 경우 비교 참고만 수행 |
| `C:\ComputerGraphics\ignore` | 없음 | 제외 | 제외 | 해당 없음 | raw local/private 자료로 간주 | 미확인 | archive/public 후보에서 제외 |

## 후보 기록 템플릿

```md
## Candidate

- Source:
- Target:
- Import status:
- Public readiness:
- Build/run status:
- Copyright/license note:
- Personal-info check:
- Next action:
```

## 공개 전 연결 기준

- archive로 옮긴 뒤에도 public 공개 여부는 별도로 판단합니다.
- public 후보는 [public-readiness.md](public-readiness.md)의 공개 전 체크리스트를 통과해야 합니다.
- 강의 원문 코드, 강의 자료, 유료 자료, 강의 화면 캡처, 문제/해설 전문은 public 후보가 아닙니다.
- 출처나 라이선스가 불명확한 외부 asset은 `검토 필요`로 유지합니다.
