Write-Host "=== Spectral Norm: Fast-Math Benchmark ===" -ForegroundColor Green

# C version
Write-Host "`nC (gcc -O3):" -ForegroundColor Cyan
$sw = [System.Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt 10; $i++) { & './c/spectral_c.exe' | Out-Null }
$sw.Stop()
$c_time = $sw.ElapsedMilliseconds / 10
Write-Host "Per run: $($c_time)ms"

# C with fast-math
Write-Host "`nC (gcc -O3 -ffast-math):" -ForegroundColor Cyan
$null = & gcc -O3 -ffast-math './c/main.c' -o './c/spectral_c_fast.exe' -lm 2>&1
$sw = [System.Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt 10; $i++) { & './c/spectral_c_fast.exe' | Out-Null }
$sw.Stop()
$c_fast_time = $sw.ElapsedMilliseconds / 10
Write-Host "Per run: $($c_fast_time)ms"

# BMB fast-math
Write-Host "`nBMB (opt fast-math):" -ForegroundColor Cyan
$sw = [System.Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt 10; $i++) { & './bmb/spectral_fastmath.exe' | Out-Null }
$sw.Stop()
$bmb_fast_time = $sw.ElapsedMilliseconds / 10
Write-Host "Per run: $($bmb_fast_time)ms"

# Comparison
Write-Host "`n=== Comparison ===" -ForegroundColor Yellow
Write-Host "BMB fast-math / C: $([math]::Round($bmb_fast_time / $c_time * 100, 1))%"
Write-Host "BMB fast-math / C fast-math: $([math]::Round($bmb_fast_time / $c_fast_time * 100, 1))%"
Write-Host "C fast-math / C: $([math]::Round($c_fast_time / $c_time * 100, 1))%"
