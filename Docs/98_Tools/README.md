# Tools

이 폴더는 문서 작성에 사용하는 template, validation 기준, troubleshooting 문서를 둔다. 정책 정본은 `Docs/06_Policies`에 둔다.

## 책임

- tracked Docs 작성에 사용하는 template을 보관한다.
- local-only review template의 사용 위치를 안내한다.
- 문서 검수와 GitHub body 검수 기준을 설명한다.
- 반복 실행 가능한 validator script를 보관한다.
- 비파괴적인 session utility script를 보관한다.
- 세션 문제 해결 문서를 둔다.
- 실제 작업 초안이나 게시 본문은 이 폴더에 두지 않는다.

## 문서 목록

| 문서 | 책임 |
| --- | --- |
| [Work Session Quickstart](work-session-quickstart.md) | 작업 유형, 권한, 검증, commit, remote 반영과 handoff 실행 순서 |
| [Templates](templates/README.md) | 산출물별 template과 local-only review template 색인 |
| [Validators](validators/README.md) | GitHub body 등 반복 검수 script 색인 |
| [Validation Tools](validation-tools.md) | 최소 검수 명령과 validator 승격 기준 |
| [Document System Audit Guide](document-system-audit-guide.md) | 문서 체계 감사 실행, 에이전트 분담, 재검증 절차 |
| [Session Troubleshooting](session-troubleshooting.md) | 세션/권한/인코딩/작업 분리 문제 대응 |
| [User Attention Notification](user-attention-notification.md) | 작업 종료, 승인 대기와 blocker 시 Windows 알림 실행 |
| [Example Window Capture](example-window-capture.md) | Windows/DWM 기반 application 전체 창 capture 후보 생성 |
| [Example Window Recording](example-window-recording.md) | FFmpeg 기반 application 전체 창 video 후보 녹화 |
| [UV Diagnostic Texture](uv-diagnostic-texture.md) | UV 방향·보간·seam 확인용 자작 PNG 생성 |

## local tools 기준

`local/tools`는 Git에 올리지 않는 실험용 도구 위치다. 반복 사용할 가치가 있고 민감 정보가 없으면 사용법을 `Docs/98_Tools`에 문서화한 뒤 `validators/` 같은 tracked script 위치로 승격한다.

## 작성 기준

- 평서형 현재형을 사용한다.
- 정책 원문은 `Docs/06_Policies`에 둔다.
- legacy import 기록은 `Docs/99_Legacy`에 둔다.
