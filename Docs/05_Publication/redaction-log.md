# Redaction Log

이 문서는 public 후보로 옮기기 전에 제거하거나 재작성해야 할 항목을 기록한다. 민감한 원문은 이 문서에 직접 적지 않는다.

## 기록표

| ID | 대상 | 유형 | 조치 | 상태 | 비고 |
| --- | --- | --- | --- | --- | --- |
| RD-001 | public README 후보 | 강의 기반 표현 가능성 | 공개용 문장으로 재작성 | 예정 | 후보 확정 후 수행 |
| RD-002 | `02_Bloom` input/result | generated asset 출처와 실행 증거 연결 | 사용자 직접 생성과 외부 자료 미복제를 확인하고 metadata·개인 식별자 검수 및 실행 입력과 tracked input의 SHA-256 일치를 기록 | 완료 | Input과 tracked input SHA-256 일치. Input APP1 metadata 제거와 decoded pixel 유지, Result PNG metadata와 육안 검사 완료. 생성 날짜, prompt 원문, provenance screenshot과 작업용 원본은 선택 기록으로 분류 |
| RD-003 | WorkLog 요약 | local/GitHub draft 흔적 | 게시 전 문체와 민감 정보 제거 | 예정 | Issue/PR 작성 전 수행 |
| RD-004 | `Step10 Texturing` input/result | 출처 불명 texture 교체 | 출처 불명 JPEG를 제거하고 사용자 직접 생성 석재 PNG와 재촬영한 전체 창 capture를 사용 | 완료 | 외부 image 직접 입력·pixel 복제 없음. 실행 입력과 tracked input SHA-256 일치. 입력·capture PNG의 text/EXIF/XMP 정보와 개인 식별자 없음 |

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
