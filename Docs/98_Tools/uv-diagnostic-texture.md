# UV Diagnostic Texture

`scripts/new-uv-diagnostic-texture.ps1`은 image texture 입력이 필요한 예제에서 외부 자료 대신 사용할 수 있는 진단용 PNG를 직접 생성한다.

## 책임

- UV 상하좌우 방향을 구분할 수 있는 비대칭 corner marker를 만든다.
- Barycentric UV 보간과 triangle seam을 확인할 수 있는 checker와 gradient를 만든다.
- Bilinear filtering을 관찰할 수 있는 중심 target과 대각선 표식을 만든다.
- 외부 image, text, logo, watermark와 개인정보를 입력으로 사용하지 않는다.

Asset 출처와 승격 기준은 [Assets Policy](../06_Policies/assets-policy.md)를 따른다. Capture 생성과 검수는 [Example Window Capture](example-window-capture.md)를 따른다.

## 사용법

```powershell
powershell -NoProfile -ExecutionPolicy Bypass `
  -File Docs/98_Tools/scripts/new-uv-diagnostic-texture.ps1 `
  -OutputPath local/uv-diagnostic.png `
  -Size 1024
```

출력에는 절대 경로, dimensions, pixel format과 SHA-256이 표시된다.

## 진단 요소

| 요소 | 확인 대상 |
| --- | --- |
| Red·green·blue·yellow corner | UV 상하좌우 방향 |
| 8×8 checker | 확대와 bilinear filtering |
| 수평·수직 gradient | Attribute 보간 연속성 |
| 중심 target | 중심 좌표와 filtering |
| 반대 대각선 | 방향 식별과 pattern 연속성 |
| 서로 다른 edge color | Wrap 경계와 UV 범위 |

Square를 두 triangle으로 나누는 주 대각선에는 별도 선을 그리지 않는다. 이 영역에서 checker와 gradient가 끊기지 않아야 seam이 없는 것으로 판단할 수 있다.

## 재현성 확인

같은 `Size`로 다시 생성한 파일의 SHA-256을 tracked input과 비교한다.

```powershell
Get-FileHash `
  local/uv-diagnostic.png `
  -Algorithm SHA256
```

파일을 의도적으로 편집했다면 hash 불일치 원인을 기록한다. PNG를 `Docs/_assets` 또는 public 후보에 사용하기 전에는 dimensions, metadata, watermark와 개인 식별자를 다시 확인한다.
