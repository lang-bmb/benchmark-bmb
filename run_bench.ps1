param(
    [string]$Executable,
    [int]$Runs = 5
)

Write-Host "=== Benchmark: $Executable ==="
$times = @()

foreach ($i in 1..$Runs) {
    $sw = [Diagnostics.Stopwatch]::StartNew()
    & $Executable | Out-Null
    $sw.Stop()
    $ms = $sw.ElapsedMilliseconds
    $times += $ms
    Write-Host "Run $i : $ms ms"
}

$sorted = $times | Sort-Object
$median = $sorted[[int]($Runs/2)]
$min = $times | Measure-Object -Minimum | Select-Object -ExpandProperty Minimum
$max = $times | Measure-Object -Maximum | Select-Object -ExpandProperty Maximum
$avg = [math]::Round(($times | Measure-Object -Average | Select-Object -ExpandProperty Average), 2)

Write-Host "---"
Write-Host "Median: $median ms"
Write-Host "Min: $min ms"
Write-Host "Max: $max ms"
Write-Host "Avg: $avg ms"
