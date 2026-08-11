# GraphicsLab Assets

이 폴더는 GraphicsLab이 실행 중 읽는 tracked shader와 재배포 가능한 asset을 둔다.

- build는 이 구조를 executable 옆 `Assets` 폴더로 복사한다.
- runtime path는 current working directory가 아니라 executable 위치를 기준으로 계산한다.
- 출처와 재배포 조건이 확인되지 않은 raw texture는 추가하지 않는다.
- shader와 replacement texture는 각 rendering milestone에서 검증한 뒤 추가한다.
