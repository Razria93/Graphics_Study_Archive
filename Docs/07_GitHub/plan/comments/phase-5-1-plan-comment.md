## Phase 5-1 완료 기록

## 완료 내용

- `Part4_Chapter14-20`의 Chapter14 `Ex1401_Basic`부터 `Ex1408_BitonicSort`까지를 Debug x64 기준으로 재검증했다.
- `Ex1402`, `Ex1404`부터 `Ex1407`까지의 centered client-visible screenshot 5개를 tracked capture asset으로 승격했다.
- `Ex1403_MatVecMult`, `Ex1405_ConsumeAppendBuffer`, `Ex1408_BitonicSort`의 stdout evidence와 `Ex1407_IndirectArguments` code evidence를 상세 Demo와 GitHub body 후보에 연결했다.
- Chapter14 [Demo Issue #29](https://github.com/Razria93/Graphics_Study_Archive/issues/29)와 [PR #30](https://github.com/Razria93/Graphics_Study_Archive/pull/30)을 연결했다.

## 검증

- `Part4_Chapter14-20/Examples.sln` Debug x64 build: 경고 0개, 오류 0개
- `Ex1401`부터 `Ex1408`까지 Debug x64 run과 exit code: 성공
- `Ex1403` CPU/GPU matrix-vector compare, `Ex1405` append count, `Ex1408` element count별 CPU/GPU sort compare: 확인
- `Ex1402`, `Ex1404`부터 `Ex1407`까지 PNG full format, dimensions, taskbar-free centered client-visible capture와 text metadata chunk 없음: 확인
- Demo index, 상세 Demo, GitHub body와 Markdown validator: 통과

## 남은 제한

- Release 현재 재검증은 후속 범위로 둔다.
- `Ex1401_Basic`은 local screenshot 후보만 있으며 desktop 재촬영 후 tracked 승격 여부를 판단한다.
- `Ex1406`과 `Ex1407`의 시간 변화는 video 후보지만 현재 본문은 static screenshot과 code evidence 중심으로 유지한다.
- Chapter15부터 Chapter20까지 재검증과 Demo 확장은 별도 후속 범위다.

## Related PR

- [PR #30](https://github.com/Razria93/Graphics_Study_Archive/pull/30) - Part4 Chapter14 Compute Shader evidence 문서화와 capture 승격