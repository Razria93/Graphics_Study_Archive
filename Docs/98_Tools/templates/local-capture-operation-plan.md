# Local Capture Operation Plan

이 template은 screenshot·video 개별 take의 UI 조작과 reset을 `local/`에 계획할 때 사용한다. 작성한 계획은 tracked 산출물 정본이 아니며 Example별 실제 좌표와 parameter를 이 template에 고정하지 않는다.

## 대상

| 항목 | 내용 |
| --- | --- |
| Part/Chapter/Example |  |
| Capture 유형 | screenshot / video / result image |
| 목표 visual |  |
| Graphics 개념 |  |
| Executable |  |
| Working directory |  |
| Expected title |  |
| Local output |  |
| Tracked 승격 후보 |  |

## Window와 입력 안전

| 항목 | 내용 |
| --- | --- |
| Window size·position |  |
| Center window | 예 / 아니오 |
| Countdown |  |
| 사용자 입력 중단 안내 |  |
| Cursor 대피 위치 |  |
| PID·title·bounds 재확인 |  |

## 초기·목표 상태

| 항목 | 내용 |
| --- | --- |
| 초기 application 상태 |  |
| 초기 parameter |  |
| 목표 parameter |  |
| 종료 상태 |  |
| Reset 방식 | application restart / 값 복구 |

## UI 조작 sequence

| 순서 | UI control | DWM bounds 기준 상대 좌표 | 조작 | 목표값 | 전·후 대기 |
| --- | --- | --- | --- | --- | --- |
| 1 |  |  |  |  |  |

## Capture 시점

| 항목 | 내용 |
| --- | --- |
| Screenshot 시점 |  |
| Recording 시작 |  |
| Recording 종료 |  |
| 시작 안정 구간 |  |
| 결과 안정 구간 |  |

## 실패와 재촬영

- 재촬영 조건:
- 중단 조건:
- partial·attempt 처리:
- 기존 selected 보호:

## 검수

### 자동 기술 검수

- [ ] 파일 format, dimensions, duration과 stream이 기준에 맞는다.
- [ ] metadata, hash와 전체 decode를 확인한다.
- [ ] process, FFmpeg와 global hotkey 잔재가 없다.
- [ ] 대상 PID, exact title과 bounds가 계획과 일치한다.

### 사용자 시각 검수

- [ ] title bar와 border가 포함되고 화면이 잘리지 않는다.
- [ ] 다른 window, notification, account와 local path가 노출되지 않는다.
- [ ] 조작과 결과의 대응이 명확하다.
- [ ] 불필요한 parameter 왕복, click, mouse movement와 대기가 없다.
- [ ] 시작·종료 안정 구간과 정지 이미지 대비 추가 설명 가치를 확인한다.

## Publication

| 항목 | 내용 |
| --- | --- |
| 판정 | 검토 필요 / public 후보 / private-only |
| 입력 asset 출처·license |  |
| 승격 전 남은 검수 |  |
