# Assets Policy

이 문서는 capture/result, diagram, third-party asset 관리 기준을 정의한다.

## 정본 위치

Asset 사용 기준은 이 문서를 따른다. Demo capture/result 설명은 `Docs/03_Demos`에 둔다.

## 운영 기준

- raw repo의 기존 capture/result를 그대로 archive/public 후보로 사용하지 않는다.
- 직접 실행해 새로 만든 결과물만 우선 검토한다.
- 강의 화면, 강의 자료 이미지, 문제/해설 캡처는 포함하지 않는다.
- 외부 texture, model, image asset은 출처와 라이선스를 확인하기 전까지 `검토 필요`로 둔다.
- 검토된 capture/result와 diagram reference는 `Docs/_assets`에 둔다.

## third-party 기준

Build dependency로 필요한 third-party header는 출처와 라이선스를 확인한다. Public subset 구성 시 별도 notice를 다시 검토한다.

## Result Image 입력 asset 기준

- result image가 외부 image, texture, model, HDRI를 입력으로 사용했다면 입력 asset의 출처와 라이선스를 확인한다.
- 입력 asset의 출처와 라이선스를 확인하기 전에는 해당 result image를 public 후보로 승격하지 않는다.

## Generated Image 기준

ChatGPT 등 생성형 이미지 도구로 만든 이미지는 외부 wallpaper보다 우선 검토할 수 있다. 다만 생성 이미지도 출처 기록과 사용 목적을 남긴 뒤 단계적으로 승격한다.

- 생성 도구, 생성 날짜, 프롬프트 원문, 작업용 원본 파일 경로를 기록한다.
- 생성 화면 스크린샷은 provenance 기록으로 `local/`에만 둔다.
- provenance screenshot은 ChatGPT UI를 포함하므로 public 문서에 직접 게시하지 않는다.
- 작업용 원본 이미지는 `local/<work-unit>/image.png`처럼 local-only 위치에 둔다.
- 예제 실행용 변환 파일과 result image도 먼저 `local/<work-unit>/`에서 검토한다.
- tracked 입력 asset으로 교체할 때는 사용자 확인과 정책 검수를 거친다.
- `Docs/_assets` 승격과 public subset 후보 판단은 demo capture/result 승격 기준을 따른다.