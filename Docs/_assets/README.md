# Assets

이 폴더는 검토된 capture, video, diagram reference를 둔다. raw capture 후보와 게시 전 검토 자료는 먼저 `local/`에 둔다.

## 책임

- 검토된 screenshot, video reference, diagram만 둔다.
- evidence 파일은 `Docs/04_Demos`에서 설명하고 이 폴더에서는 파일 위치와 용도만 관리한다.
- build/run 상태는 `Docs/03_Verification`으로 링크한다.
- public 후보 판단은 `Docs/06_Publication`으로 분리한다.
- `Docs/_assets`는 raw asset archive가 아니라 검증 완료 evidence 보관 위치다.

## 폴더 역할

| 폴더 | 역할 |
| --- | --- |
| [captures](captures/README.md) | screenshot evidence |
| [videos](videos/README.md) | video evidence 또는 video link reference |
| [diagrams](diagrams/README.md) | 직접 만든 diagram 또는 설명용 이미지 |

## 승격 기준

`local/`의 파일은 다음 조건을 만족할 때만 이 폴더로 승격한다.

- `Docs/04_Demos` 또는 `Docs/03_Verification`에서 실제로 참조한다.
- build/run/capture 상태가 `성공`, `부분 성공`, `확보` 등으로 구분되어 있다.
- 파일명과 문서 연결만으로 어떤 Part/Chapter/Portfolio evidence인지 알 수 있다.
- public 후보 또는 private-only 사유를 판단할 수 있다.
- 권리 검토가 필요한 자료를 포함하지 않는다.

## 운영 기준

- 강의 화면 캡처, 유료 자료, 출처 불명 asset은 이 폴더에 두지 않는다.
- 파일명은 Part/Chapter, 예제 또는 Topic이 드러나게 작성한다.
- 큰 영상 파일은 repo에 직접 추가하기 전에 저장 방식을 검토한다.
- 검토하지 않은 raw 파일은 `local/`에 둔다.
- 같은 의미의 중복 evidence는 하나만 승격한다.
- 실패 기록이나 비교용 원본 후보는 필요한 경우 `local/`에 보존하고 tracked Docs에는 요약만 남긴다.

## 연결 문서

- Demo 계획: `Docs/04_Demos`
- Capture 상태: `Docs/03_Verification/capture-matrix.md`
- Build/run 상태: `Docs/03_Verification/build-run-matrix.md`
- 공개 판단: `Docs/06_Publication`
- GitHub 게시 후보: `local/github/public`
