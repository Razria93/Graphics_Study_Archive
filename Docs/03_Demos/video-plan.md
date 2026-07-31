# Video Plan

이 문서는 video 필요성, selected 후보와 게시 상태를 기록하는 registry다. 촬영·검수·저장 규칙은 [Demo Capture Policy](../06_Policies/demo-capture-policy.md)를 따른다.

## 상태 위치

- raw, attempt와 selected video: `local/`
- 게시된 video reference와 운영 안내: `Docs/_assets/videos/`
- published video: GitHub Demo Issue attachment
- 게시 전 설명 초안: `local/github/draft`

## 우선 video 후보

| 범위 | 후보 | 필요성 | 보여줄 개념 | selected | published |
| --- | --- | --- | --- | --- | --- |
| Part2_Chapter04 Step1A | triangle count 3→32 slider 조작 | 필수 | triangle fan 재생성과 polygonal circle 수렴 과정 | 검증 완료 | 미게시 |
| Part2_Chapter04 Step4 | Animation2D 실행 | 필수 | 시간에 따른 계층적 2D orbit | 검증 완료 | 미게시 |
| Part3_Chapter09 | camera, picking, trackball 조작 | 필수 | interaction | 미확인 | 미게시 |
| Part3_Chapter10-13 | shadow quality 비교 | 선택 | shadow mapping, PCF, PCSS | 미확인 | 미게시 |
| Part4_Chapter14-20 | 대표 sample 실행 | 선택 | advanced graphics 후보 | 미확인 | 미게시 |
| Portfolio_RayTracer | feature progression | 선택 | ray tracing extension | 미확인 | 미게시 |

## Video Checklist

| 항목 | 기준 |
| --- | --- |
| 길이 | 짧고 반복 시청 가능함 |
| 흐름 | 시작, 조작, 결과가 분명함 |
| 설명 | 화면 밖 설명은 README/PR 본문으로 분리함 |
| 권리 검토 | 강의 화면, 유료 자료, 출처 불명 asset이 아님 |
| 연결 문서 | Example, Topic, Verification 문서와 연결됨 |
| 자동 검수 | container, codec, pixel format, CFR, stream, 민감 metadata, hash와 decode를 확인함 |
| 사용자 시각 검수 | 조작과 결과 대응, 화면 노출, 시작·종료 frame과 추가 설명 가치를 확인함 |
| 게시 | Demo Issue에 한 번 첨부하고 PR은 대표성이 있을 때 동일 URL을 재사용함 |

## 갱신 기준

- MP4, MOV와 WEBM을 일반 Git history에 추가하지 않으며 예외는 별도 Publication 판단과 사용자 승인을 따른다.
- public 공개 전에는 `Docs/05_Publication` 기준으로 다시 점검한다.
- Published 상태와 actual URL은 merge 전에 관련 tracked 정본에 동기화한다.
