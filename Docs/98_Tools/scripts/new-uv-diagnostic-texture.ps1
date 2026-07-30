param(
    [Parameter(Mandatory = $true)]
    [string]$OutputPath,

    [ValidateRange(256, 4096)]
    [int]$Size = 1024
)

$ErrorActionPreference = "Stop"

Add-Type -AssemblyName System.Drawing

$resolvedOutput = [System.IO.Path]::GetFullPath($OutputPath)
$outputDirectory = [System.IO.Path]::GetDirectoryName($resolvedOutput)

if (-not [string]::IsNullOrWhiteSpace($outputDirectory)) {
    [System.IO.Directory]::CreateDirectory($outputDirectory) | Out-Null
}

Add-Type -TypeDefinition @'
using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.Runtime.InteropServices;

public static class UvDiagnosticTextureGenerator
{
    public static void Generate(string outputPath, int size)
    {
        using (var bitmap = new Bitmap(size, size, PixelFormat.Format24bppRgb))
        {
            var rectangle = new Rectangle(0, 0, size, size);
            var data = bitmap.LockBits(
                rectangle,
                ImageLockMode.WriteOnly,
                PixelFormat.Format24bppRgb);

            try
            {
                int stride = Math.Abs(data.Stride);
                var pixels = new byte[stride * size];
                int cellSize = Math.Max(1, size / 8);
                int markerSize = Math.Max(16, size / 10);
                int borderSize = Math.Max(4, size / 128);
                int diagonalWidth = Math.Max(3, size / 192);
                double center = (size - 1) / 2.0;
                double outerRadius = size * 0.105;
                double innerRadius = size * 0.045;

                for (int y = 0; y < size; y++)
                {
                    double v = y / (double)(size - 1);

                    for (int x = 0; x < size; x++)
                    {
                        double u = x / (double)(size - 1);
                        int checker = (x / cellSize + y / cellSize) % 2;
                        int checkerOffset = checker == 0 ? 22 : -10;
                        int red = Clamp((int)(35 + 150 * u + checkerOffset));
                        int green = Clamp((int)(35 + 150 * v + checkerOffset));
                        int blue = Clamp(
                            (int)(155 - 75 * u + 55 * v + checkerOffset));

                        if (x < borderSize)
                        {
                            SetColor(ref red, ref green, ref blue, 255, 48, 48);
                        }
                        else if (x >= size - borderSize)
                        {
                            SetColor(ref red, ref green, ref blue, 48, 255, 96);
                        }
                        else if (y < borderSize)
                        {
                            SetColor(ref red, ref green, ref blue, 64, 128, 255);
                        }
                        else if (y >= size - borderSize)
                        {
                            SetColor(ref red, ref green, ref blue, 255, 224, 48);
                        }

                        if (x < markerSize && y < markerSize)
                        {
                            SetColor(ref red, ref green, ref blue, 255, 64, 64);
                        }
                        else if (x >= size - markerSize && y < markerSize)
                        {
                            SetColor(ref red, ref green, ref blue, 64, 255, 96);
                        }
                        else if (x < markerSize && y >= size - markerSize)
                        {
                            SetColor(ref red, ref green, ref blue, 64, 112, 255);
                        }
                        else if (x >= size - markerSize && y >= size - markerSize)
                        {
                            SetColor(ref red, ref green, ref blue, 255, 224, 64);
                        }

                        if (Math.Abs((size - 1 - x) - y) <= diagonalWidth)
                        {
                            SetColor(ref red, ref green, ref blue, 32, 32, 32);
                        }

                        double deltaX = x - center;
                        double deltaY = y - center;
                        double distance = Math.Sqrt(
                            deltaX * deltaX + deltaY * deltaY);

                        if (distance <= outerRadius)
                        {
                            SetColor(ref red, ref green, ref blue, 245, 245, 245);
                        }
                        if (distance <= innerRadius)
                        {
                            SetColor(ref red, ref green, ref blue, 24, 24, 24);
                        }

                        int offset = y * stride + x * 3;
                        pixels[offset] = (byte)blue;
                        pixels[offset + 1] = (byte)green;
                        pixels[offset + 2] = (byte)red;
                    }
                }

                Marshal.Copy(pixels, 0, data.Scan0, pixels.Length);
            }
            finally
            {
                bitmap.UnlockBits(data);
            }

            bitmap.Save(outputPath, ImageFormat.Png);
        }
    }

    private static int Clamp(int value)
    {
        return Math.Min(255, Math.Max(0, value));
    }

    private static void SetColor(
        ref int red,
        ref int green,
        ref int blue,
        int nextRed,
        int nextGreen,
        int nextBlue)
    {
        red = nextRed;
        green = nextGreen;
        blue = nextBlue;
    }
}
'@ -ReferencedAssemblies System.Drawing

$temporaryOutput = Join-Path (
    [System.IO.Path]::GetTempPath()
) ("uv-diagnostic-{0}.png" -f [guid]::NewGuid().ToString("N"))

try {
    [UvDiagnosticTextureGenerator]::Generate($temporaryOutput, $Size)
    [System.IO.File]::Copy($temporaryOutput, $resolvedOutput, $true)
}
finally {
    if (Test-Path -LiteralPath $temporaryOutput) {
        Remove-Item -LiteralPath $temporaryOutput -Force
    }
}

$hash = Get-FileHash -LiteralPath $resolvedOutput -Algorithm SHA256
$image = [System.Drawing.Image]::FromFile($resolvedOutput)

try {
    [pscustomobject]@{
        Path = $resolvedOutput
        Width = $image.Width
        Height = $image.Height
        PixelFormat = $image.PixelFormat.ToString()
        Sha256 = $hash.Hash
    }
}
finally {
    $image.Dispose()
}
