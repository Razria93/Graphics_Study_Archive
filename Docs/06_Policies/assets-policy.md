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

생성형 이미지 도구로 만든 이미지는 외부 wallpaper보다 우선 검토할 수 있다.
기본 검수는 복잡한 생성 이력보다 출처 상태, 공개 안전성, 실행 증거 연결을
확인하는 최소 출처 기록을 사용한다.

필수 기록:

- 출처 상태를 `사용자 직접 생성`, `사용자 직접 촬영`,
  `라이선스 확인 외부 자료`, `출처 검토 필요` 중 하나로 분류한다.
- 사용자 직접 생성 또는 촬영 자료는 외부 자료 복제 여부를 확인한다.
- 공개 asset의 metadata, 워터마크, 개인 식별자, 계정과 로컬 경로를 확인한다.
- 실행 입력과 tracked 공개 증거의 관계를 기록한다.
  - 동일 파일은 SHA-256 일치를 확인한다.
  - metadata 제거 등으로 재인코딩한 파일은 해상도와 decoded pixel 관계를
    확인한다.
  - 의도적으로 편집한 파일은 편집 관계를 짧게 기록한다.
- `Docs/_assets` 승격과 public subset 후보 판단은 demo capture/result 승격
  기준을 따른다.

생성 도구, 생성 날짜, prompt 원문, 생성 화면 screenshot, 작업용 원본 파일,
local 원본 경로와 상세 source ID는 선택 기록이다. 이 항목이 없다는 이유만으로
사용자 직접 생성 asset을 `검토 필요` 또는 게시 보류로 판정하지 않는다.

다음 조건에서는 강화 출처 검수를 적용한다.

- 생성 주체가 불명확하거나 사용자 직접 생성 여부를 확인할 수 없다.
- 외부 source가 섞였거나 라이선스·재배포 조건이 불명확하다.
- 강의, 유료 자료, 제3자 화면과 혼동될 가능성이 있다.
- 상업적 배포, 별도 public release 또는 출처 분쟁 가능성이 있다.

강화 검수에서는 source URL, 라이선스, 생성 도구와 날짜, prompt 원문, 생성
화면 screenshot, 작업용 원본, import commit 또는 source ID를 필요에 따라
추가 확인한다. 민감 원문과 UI screenshot은 `local/`에만 두고 public 문서에
게시하지 않는다.
