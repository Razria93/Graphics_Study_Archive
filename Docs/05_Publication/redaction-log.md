# Redaction Log

이 문서는 public 후보로 옮기기 전에 제거하거나 재작성해야 할 항목을 기록한다. 민감한 원문은 이 문서에 직접 적지 않는다.

## 기록표

| ID | 대상 | 유형 | 조치 | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- |
| RD-001 | public README 후보 | 강의 기반 표현 가능성 | 공개용 문장으로 재작성 | 예정 | 후보 확정 후 수행 |
| RD-002 | `02_Bloom` input/result | generated asset 출처와 실행 증거 연결 | 사용자 직접 생성과 외부 자료 미복제를 확인하고 metadata·개인 식별자 검수 및 실행 입력과 tracked input의 SHA-256 일치를 기록 | 완료 | Input과 tracked input SHA-256 일치. Input APP1 metadata 제거와 decoded pixel 유지, Result PNG metadata와 육안 검사 완료. 생성 날짜, prompt 원문, provenance screenshot과 작업용 원본은 선택 기록으로 분류 |
| RD-003 | WorkLog 요약 | local/GitHub draft 흔적 | 게시 전 문체와 민감 정보 제거 | 예정 | Issue/PR 작성 전 수행 |
| RD-004 | `Step10 Texturing` input/result | 출처 불명 texture 교체 | 출처 불명 JPEG를 제거하고 사용자 직접 생성 석재 PNG와 재촬영한 전체 창 capture를 사용 | 완료 | 외부 image 직접 입력·pixel 복제 없음. 실행 입력과 tracked input SHA-256 일치. 입력·capture PNG의 text/EXIF/XMP 정보와 개인 식별자 없음 |
| RD-005 | `Step11 Supersampling` input/result | 출처 불명 texture 교체 | Step11의 출처 불명 JPEG를 제거하고 Step10에서 검수한 석재 PNG의 동일 바이트 사본과 전체 창 capture를 사용 | 완료 | Step11 입력과 Step10 검증 input의 SHA-256 일치. 입력·capture PNG의 text/EXIF/XMP 정보와 개인 식별자 없음 |
| RD-006 | `Step12 Reflection` input/result | 출처 불명 texture와 미사용 asset 제거 | Step12의 출처 불명 JPEG와 미사용 background 사본을 제거하고 Step10·11에서 검수한 석재 PNG의 동일 바이트 사본과 전체 창 capture를 사용 | 완료 | Step12 입력과 Step10·11 검증 input의 SHA-256 일치. 입력·capture PNG의 text/EXIF/XMP 정보와 개인 식별자 없음. Step13 asset은 변경하지 않음 |
| RD-007 | `Step13 Transparency` input/result | 출처 불명 ground·background 교체 | Step13의 출처 불명 JPEG 두 개를 제거하고 검수한 석재 PNG를 ground에, 사용자 직접 생성 해수면·하늘 PNG를 background에 사용 | 완료 | Ground 입력은 Step10~12 검증 input과 SHA-256이 일치한다. Background는 참고 이미지의 pixel을 직접 복제하지 않은 새 생성 결과다. Background의 C2PA에는 OpenAI 생성 이력만 있고 개인 식별자와 로컬 경로는 없다. 입력·capture의 PNG text/EXIF/XMP 정보와 개인 식별자를 확인했다. Step14 asset은 변경하지 않음 |
| RD-008 | `Step14 CubeEnvironment` asset/result | Runtime 미사용 environment asset 정리 | 실행에 필요한 Humus CC BY 3.0 cubemap 6면과 attribution 원문만 유지하고 미사용 blurred face 6개와 별도 skybox asset 18개 제거 | 완료 | 실행용 JPEG 6면의 metadata와 공개 안전성, Debug/Release x64 load를 확인했다. Capture는 프로그램이 6면을 sampling해 렌더링한 결과이며 6면 orientation 전체 검증으로 사용하지 않음 |
| RD-009 | `Chapter06 Step5 Texturing` input/result | 출처 불명 texture 교체 | 출처 불명 PNG·JPEG를 제거하고 공개용 generated 석재·목재 PNG와 재촬영한 전체 창 capture를 사용 | 완료 | 외부 원문 pixel 복제 없음. Generated input 2개는 1254×1254 RGB PNG이며 C2PA에는 OpenAI 생성 이력만 있다. 개인 식별자·PNG text·EXIF가 없고 Debug/Release x64 load와 capture 2장의 공개 안전성을 확인했다 |
| RD-010 | `Chapter06 Step5A Texturing LightingSelf` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 texture 2개를 제거하고 Step5에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | Step5A와 Step5 목재 input SHA-256 일치. 미사용 texture·shader resource를 제거하고 Debug/Release x64 load, capture 2장의 metadata와 개인 식별자를 확인했다 |
| RD-011 | `Chapter06 Step6 Lighting` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG를 제거하고 Step5·Step5A에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | Step6와 Step5·Step5A 목재 input SHA-256 일치. 미사용 texture·shader resource를 제거하고 Debug/Release x64 load, Directional·Point·Spot capture 3장의 metadata와 개인 식별자를 확인했다 |
| RD-012 | `Chapter06 Step7 ResizingViewport` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG와 두 번째 texture resource를 제거하고 Step5·Step5A·Step6에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 네 단계의 목재 input SHA-256 일치. Debug/Release x64 load와 1282×992 capture의 metadata·개인 식별자 부재를 확인했다 |
| RD-013 | `Chapter06 Step8 ResizingWindow` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG와 두 번째 texture resource를 제거하고 Step5·Step5A·Step6·Step7에서 검수한 generated 목재 PNG의 동일 바이트 사본과 세 크기의 전체 창 capture를 사용 | 완료 | 다섯 단계의 목재 input SHA-256 일치. Debug/Release x64 load와 default·wide·compact capture의 metadata·개인 식별자 부재와 시각 결과를 확인했다 |
| RD-014 | `Chapter06 Step9 PhongVsBlinnPhong` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG를 제거하고 Step5·Step5A·Step6·Step7·Step8에서 검수한 generated 목재 PNG의 동일 바이트 사본과 같은 조건의 Phong·Blinn-Phong 전체 창 capture를 사용 | 완료 | 여섯 단계의 목재 input SHA-256 일치. Debug/Release x64 load와 capture 2장의 metadata·개인 식별자 부재와 시각 결과를 확인했다 |

| RD-015 | `Chapter07 Step1 DrawingWireFrames` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG와 두 번째 texture resource를 제거하고 Chapter06 Step5–9에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 일곱 단계의 목재 input SHA-256 일치. Debug/Release x64 load, 반복 resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다 |
| RD-016 | `Chapter07 Step2 DrawingNormals` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG와 두 번째 texture resource를 제거하고 Chapter06 Step5–9와 Chapter07 Step1에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 여덟 단계의 목재 input SHA-256 일치. Debug/Release x64 load, 반복 resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다 |
| RD-017 | `Chapter07 Step3 Grid` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG를 제거하고 Chapter06 Step5–9와 Chapter07 Step1–2에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 아홉 단계의 목재 input SHA-256 일치. Debug/Release x64 load, resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다 |
| RD-018 | `Chapter07 Step4 Cylinder` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG를 제거하고 Chapter06 Step5–9와 Chapter07 Step1–3에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 열 단계의 목재 input SHA-256 일치. Debug/Release x64 load, resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다 |
| RD-019 | `Chapter07 Step5 Sphere UserSolution` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG 3개와 미사용 두 번째 texture resource를 제거하고 이전 단계에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 열한 단계의 목재 input SHA-256 일치. Debug/Release x64 load, resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다. ReferenceSolution은 private 비교 근거로 유지한다 |
| RD-020 | `Chapter07 Step6 Subdivision` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG 3개와 미사용 두 번째 texture resource를 제거하고 이전 단계에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 열두 단계의 목재 input SHA-256 일치. Debug/Release x64 load, resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다 |
| RD-021 | `Chapter07 Step7 FaceNormals` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG 3개와 미사용 두 번째 texture resource를 제거하고 이전 단계에서 검수한 generated 목재 PNG의 동일 바이트 사본과 재촬영한 전체 창 capture를 사용 | 완료 | 열세 단계의 목재 input SHA-256 일치. Debug/Release x64 load, winding 수치 검사, resize·minimize/restore와 capture metadata·개인 식별자 부재를 확인했다 |
| RD-022 | `Chapter07 Step8 SphereMapping UserSolution` input/result | 출처 불명·미사용 texture 정리 | 출처 불명 PNG·JPEG 3개와 미사용 두 번째 texture resource를 제거하고 generated fictional planet 2:1 equirectangular PNG와 전체 창 capture를 사용 | 완료 | Debug/Release x64 load와 runtime visual을 확인했다. Input은 1774×887, capture는 1282×992다. Capture에 PNG text·EXIF·XMP·trailing data와 개인 식별자가 없다 |

## 유형

- 강의 원문 표현
- 유료 자료 또는 강의 화면 흔적
- 출처 불명 asset
- 계정 정보 또는 개인 정보
- 로컬 절대 경로
- 제출 대상별 기록
- draft 문구 또는 대화체

## 운영 기준

- 민감한 원문은 tracked Docs에 적지 않는다.
- 상세 검토 메모는 `local/publication`에 둔다.
- 완료된 redaction은 WorkLog에 요약만 남긴다.
