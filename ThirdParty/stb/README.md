# stb headers

이 폴더는 image load/write 재현성을 위해 archive repo에 포함한 STB single-header files를 보관합니다.

## Included files

| File | Version | Note |
| --- | --- | --- |
| `stb_image.h` | v2.30 | public domain image loader |
| `stb_image_write.h` | v1.16 | public domain image writer |

## Usage

Part1 예제 중 `stb_image.h` 또는 `stb_image_write.h`를 include하는 프로젝트는 `ThirdParty/stb`를 `AdditionalIncludeDirectories`에 추가합니다.

## Source

The headers identify the STB project as `http://nothings.org/stb` and state public domain usage in the file headers. They were copied from the local vcpkg installed headers to make clean archive checkouts build without relying on a global include path.
