# Demo Note

이 문서는 Demo source docs 작성용 템플릿이다. GitHub 게시 문장은 `Docs/07_GitHub`에서 이 내용을 요약/재구성한다.

## 대상

- 루트 코드 폴더:
- 예제 폴더:
- 연결 Topic:
- 연결 Verification:

## Demo 목표

- 최소 capture/result: screenshot 최소 1개 필수
- 대표 capture/result:
- video 필요 여부:

## 구현 하이라이트 초안

- 구현 목표(3줄 이내):
- 처리 흐름(번호 목록 4~6단계):
- 핵심 파일 맵(파일/역할 3~5개):

## C++ 스타일 의사코드 초안

문서 가독성 중심 구조 요약만 기록한다. 원본 코드는 링크로 위임한다.

```cpp
// Pseudo C++: 구조 설명용 요약
void FunctionPseudo(...)
{
	// 입력/전처리
	if (...) {
		return;
	}

	// 핵심 처리
	for (...) {
		...
	}

	// 출력/반영
}
```

- 원본 코드 링크 1:
- 원본 코드 링크 2:
- 가독성 체크: 한 줄 80~120자 범위를 권장하고 긴 식은 2~3줄로 분해한다.

## 사용자 요청 조건

- 요청 유형: screenshot / video / result image
- 찍어야 할 화면 또는 출력 파일:
- before/after 또는 input/result 비교 필요 여부:
- README 연결 대상 여부 또는 local 검토 후보 여부:
- 피해야 할 노출 요소: 강의명, 강사명, 워터마크, 개인 식별자, 계정, 로컬 경로, 불필요한 IDE/terminal/browser UI
- 권장 비율과 구도:
- 권장 파일명:

## Capture/Result 후보

| 항목 | 위치 | 상태 | 비고 |
| --- | --- | --- | --- |
| screenshot | `local/` | 미확인 | 화면 이미지 캡처 |
| video | `local/` | 미확인 | 화면 녹화 |
| result image | ignored output 또는 `local/` | 미확인 | 프로그램이 파일로 출력한 이미지 |

## 검수 단계

- 정책 검수:
- 후보 검수:
- 승격 검수:

## GitHub Body 전환 체크

- Demo Issue 필수 섹션 순서 점검 여부:
- 시각 자료(소제목/설명/이미지) 순서 점검 여부:
- 의사코드(C++ 스타일, Pseudo C++ 표기) 점검 여부:
- 원본 코드 링크 쌍 점검 여부:
- body validator 결과:
- quality validator 결과:

## 공개 전 확인

- 직접 실행 결과인지:
- 강의 화면 캡처가 아닌지:
- 강의명/강사명/강의 브랜드 표기가 없는지:
- 워터마크가 없는지:
- window title 또는 overlay text가 public-safe인지:
- debug HUD, browser tab, taskbar, notification 노출 여부:
- video audio/subtitle/metadata 확인 여부:
- asset 권리와 출처:
- 개인 이름/계정/로컬 경로 포함 여부:
- 민감 정보 포함 여부:
- 파일명 규칙:
- `Docs/_assets` 승격 가능 여부:

## 갱신 위치

- `Docs/03_Demos/demo-priority.md`
- `Docs/03_Demos/capture-plan.md`
- `Docs/03_Demos/<Part*>/demo-index.md`
- `Docs/02_Verification/capture-matrix.md`
- `Docs/_assets`

## Metadata 확인

- screenshot/result image metadata: 미확인
- video metadata/audio/subtitle: 미확인
- external input asset source/license: 미확인
- lecture name/instructor/watermark/personal identifier: 미확인

## 생성 이미지 출처 기록

- 생성 도구:
- 생성 날짜:
- 프롬프트 원문:
- 작업용 원본 이미지:
- provenance screenshot:
- 원본 파일 SHA256:
- 변환 입력 SHA256:
- result image SHA256:
- public 게시 가능성:
- 비고:
