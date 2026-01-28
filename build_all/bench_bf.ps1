$warmup = 5
$runs = 15

Write-Host "=== Brainfuck Benchmark (15 runs, 5 warmup) ==="
Write-Host ""

Write-Host "C Version:"
1..$warmup | ForEach-Object { ./brainfuck_c.exe | Out-Null }
$cTimes = @()
1..$runs | ForEach-Object { $cTimes += (Measure-Command { ./brainfuck_c.exe | Out-Null }).TotalMilliseconds }
$cTimes = $cTimes | Sort-Object
$cMedian = $cTimes[[int]($runs/2)]
Write-Host "  Min: $([math]::Round($cTimes[0], 2))ms  Median: $([math]::Round($cMedian, 2))ms  Max: $([math]::Round($cTimes[$runs-1], 2))ms"

Write-Host ""
Write-Host "BMB Original (decimal):"
1..$warmup | ForEach-Object { ./brainfuck_bmb.exe | Out-Null }
$bTimes = @()
1..$runs | ForEach-Object { $bTimes += (Measure-Command { ./brainfuck_bmb.exe | Out-Null }).TotalMilliseconds }
$bTimes = $bTimes | Sort-Object
$bMedian = $bTimes[[int]($runs/2)]
Write-Host "  Min: $([math]::Round($bTimes[0], 2))ms  Median: $([math]::Round($bMedian, 2))ms  Max: $([math]::Round($bTimes[$runs-1], 2))ms"

Write-Host ""
Write-Host "BMB Bitpack:"
1..$warmup | ForEach-Object { ./brainfuck_bitpack.exe | Out-Null }
$pTimes = @()
1..$runs | ForEach-Object { $pTimes += (Measure-Command { ./brainfuck_bitpack.exe | Out-Null }).TotalMilliseconds }
$pTimes = $pTimes | Sort-Object
$pMedian = $pTimes[[int]($runs/2)]
Write-Host "  Min: $([math]::Round($pTimes[0], 2))ms  Median: $([math]::Round($pMedian, 2))ms  Max: $([math]::Round($pTimes[$runs-1], 2))ms"

Write-Host ""
Write-Host "=== Summary ==="
Write-Host "C:              $([math]::Round($cMedian, 2))ms (baseline)"
Write-Host "BMB Original:   $([math]::Round($bMedian, 2))ms ($([math]::Round($bMedian / $cMedian * 100, 0))% of C)"
Write-Host "BMB Bitpack:    $([math]::Round($pMedian, 2))ms ($([math]::Round($pMedian / $cMedian * 100, 0))% of C)"
