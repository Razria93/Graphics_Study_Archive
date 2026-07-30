# Intersection

## 목적

Ray와 sphere의 교차를 quadratic equation으로 판정하고, 유효한 hit distance를 선택하는 개념을 설명한다. Step4의 sphere drawing 결과가 어떤 기하 판정에서 나오는지 이해하기 위한 개념 정본으로 사용한다.

## 책임 범위

이 문서는 ray-sphere intersection의 일반 원리와 root 선택을 다룬다. Step4의 구체적인 class와 함수는 Example README로, build/run/capture 사실은 Verification으로, 구현 선택과 시각 결과는 상세 Demo로 위임한다.

## 개념 흐름

Ray의 parametric 식을 sphere의 implicit equation에 대입하면 `t`에 대한 quadratic equation이 된다. Discriminant로 교차 가능성을 판정하고, 두 root 중 ray origin 앞에 있는 가장 가까운 값을 선택해 hit point와 normal을 계산한다.

## 핵심 개념

### Discriminant

중심 `c`, 반지름 `r`인 sphere와 ray `p(t) = o + t d`의 관계는 다음 식으로 정리한다.

```text
|o + t d - c|² = r²
```

이를 `a t² + b t + c = 0` 형태로 전개한다. Discriminant가 음수이면 real root가 없으므로 ray는 sphere를 지나지 않는다. 0이면 접하고, 양수이면 두 교점 후보가 생긴다.

### Valid Hit Distance

교점 후보가 있더라도 `t`가 음수이면 ray 진행 방향의 뒤쪽에 있다. 두 root 중 가장 가까운 양수 값을 선택하면 origin 앞에서 처음 만나는 표면을 얻는다.

선택한 `t`로 hit point를 계산하고, sphere center에서 hit point로 향하는 vector를 normalize해 surface normal을 구한다. Step4는 이 hit 정보와 distance를 lighting 대신 diagnostic color에 사용한다.

## 데모 연결

Step4 Demo는 miss, 접선 또는 내부 판정, 일반 hit를 서로 다른 diagnostic 결과로 표시한다. 실제 quadratic 계산과 결과 변환은 연결된 source에서 확인한다.

## 한계

- triangle과 임의 mesh intersection은 다루지 않는다.
- acceleration structure와 다중 object closest-hit 탐색은 포함하지 않는다.
- numerical robustness와 epsilon 정책은 Step4 범위를 넘어선다.

## 관련 문서

- Example: [Step4 DrawingSphere README](../../../Part1_Chapter03/03_Raytracing_Step4_DrawingSphere/README.md)
- Verification: [`Docs/02_Verification/Part1_Chapter03/verification-index.md`](../../02_Verification/Part1_Chapter03/verification-index.md)
- Demo: [`Docs/03_Demos/Part1_Chapter03/04_DrawingSphere.md`](../../03_Demos/Part1_Chapter03/04_DrawingSphere.md)
- Related Topic: [Ray](Ray.md)
