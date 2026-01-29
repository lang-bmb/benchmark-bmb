Write-Host "=== Spectral Norm Benchmark ===" -ForegroundColor Green

# C version
Write-Host "`nC (gcc -O3):" -ForegroundColor Cyan
$sw = [System.Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt 10; $i++) { & './c/spectral_c.exe' | Out-Null }
$sw.Stop()
$c_time = $sw.ElapsedMilliseconds / 10
Write-Host "Per run: $($c_time)ms"

# BMB native pointer
Write-Host "`nBMB native pointer:" -ForegroundColor Cyan
$sw = [System.Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt 10; $i++) { & './bmb/spectral_native.exe' | Out-Null }
$sw.Stop()
$bmb_ptr_time = $sw.ElapsedMilliseconds / 10
Write-Host "Per run: $($bmb_ptr_time)ms"

# BMB array_get/set
Write-Host "`nBMB array_get/set:" -ForegroundColor Cyan
$sw = [System.Diagnostics.Stopwatch]::StartNew()
for ($i = 0; $i -lt 10; $i++) { & './bmb/main_rebuilt.exe' | Out-Null }
$sw.Stop()
$bmb_arr_time = $sw.ElapsedMilliseconds / 10
Write-Host "Per run: $($bmb_arr_time)ms"

# Comparison
Write-Host "`n=== Comparison ===" -ForegroundColor Yellow
Write-Host "BMB native ptr / C: $([math]::Round($bmb_ptr_time / $c_time * 100, 1))%"
Write-Host "BMB array_get / C: $([math]::Round($bmb_arr_time / $c_time * 100, 1))%"
