$cExe = "D:/data/lang-bmb/ecosystem/benchmark-bmb/build_test/fib_c.exe"
$bmbExe = "D:/data/lang-bmb/ecosystem/benchmark-bmb/build_test/fib_bmb.exe"

Write-Host "Warming up..."
& $cExe | Out-Null
& $bmbExe | Out-Null

Write-Host "Running 5 times each..."
$cTimes = @()
$bTimes = @()
for ($i = 0; $i -lt 5; $i++) {
    $cTime = (Measure-Command { & $cExe | Out-Null }).TotalMilliseconds
    $bTime = (Measure-Command { & $bmbExe | Out-Null }).TotalMilliseconds
    $cTimes += $cTime
    $bTimes += $bTime
    Write-Host ("  C: {0:F1} ms, BMB: {1:F1} ms" -f $cTime, $bTime)
}
$cAvg = ($cTimes | Measure-Object -Average).Average
$bAvg = ($bTimes | Measure-Object -Average).Average
Write-Host ("Average - C: {0:F1} ms, BMB: {1:F1} ms" -f $cAvg, $bAvg)
$ratio = [math]::Round(($bAvg / $cAvg) * 100)
Write-Host "Ratio: $ratio%"
