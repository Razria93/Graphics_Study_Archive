# Assets Policy

이 문서는 capture, video, image, third-party asset 관리 기준을 정의한다.

## 정본 위치

Asset 사용 기준은 이 문서를 따른다. Demo evidence 설명은 `Docs/04_Demos`에 둔다.

## 운영 기준

- raw repo의 기존 capture/video를 그대로 archive/public 후보로 사용하지 않는다.
- 직접 실행해 새로 만든 결과물만 우선 검토한다.
- 강의 화면, 강의 자료 이미지, 문제/해설 캡처는 포함하지 않는다.
- 외부 texture, model, image asset은 출처와 라이선스를 확인하기 전까지 `검토 필요`로 둔다.
- 검토된 capture/image/video reference는 `Docs/_assets`에 둔다.

## third-party 기준

Build dependency로 필요한 third-party header는 출처와 라이선스를 확인한다. Public subset 구성 시 별도 notice를 다시 검토한다.