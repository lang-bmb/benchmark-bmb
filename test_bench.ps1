$BMB = "D:/data/lang-bmb/target/release/bmb.exe"
$RUNTIME = "D:/data/lang-bmb/runtime/libruntime_mingw.a"
$BUILD_DIR = "D:/data/lang-bmb/ecosystem/benchmark-bmb/build_test"

New-Item -ItemType Directory -Force -Path $BUILD_DIR | Out-Null

# Test just the 4 benchmarks we care about
$benchmarks = @("sorting", "brainfuck", "json_parse", "lexer")

foreach ($name in $benchmarks) {
    $cSrc = "./benches/real_world/$name/c/main.c"
    $bmbSrc = "./benches/real_world/$name/bmb/main.bmb"

    Write-Host "[$name] Building..." -NoNewline

    # Build C
    $cExe = "$BUILD_DIR/${name}_c.exe"
    clang -O3 $cSrc -o $cExe 2>&1 | Out-Null

    # Build BMB
    $bmbIR = "$BUILD_DIR/${name}_bmb.ll"
    $bmbExe = "$BUILD_DIR/${name}_bmb.exe"
    & $BMB build --aggressive $bmbSrc --emit-ir -o $bmbIR 2>&1 | Out-Null
    clang -O3 -target x86_64-pc-windows-gnu $bmbIR $RUNTIME -o $bmbExe 2>&1 | Out-Null

    Write-Host " Running..." -NoNewline

    # Warmup
    & $cExe | Out-Null
    & $bmbExe | Out-Null

    # Measure
    $cTimes = @()
    $bTimes = @()
    for ($i = 0; $i -lt 5; $i++) {
        $cTimes += (Measure-Command { & $cExe | Out-Null }).TotalMilliseconds
        $bTimes += (Measure-Command { & $bmbExe | Out-Null }).TotalMilliseconds
    }

    $cAvg = ($cTimes | Measure-Object -Average).Average
    $bAvg = ($bTimes | Measure-Object -Average).Average
    $ratio = [math]::Round(($bAvg / $cAvg) * 100)

    $status = if ($ratio -lt 100) { "FAST" } elseif ($ratio -le 103) { "OK" } else { "SLOW" }
    Write-Host (" {0,3}% - {1}" -f $ratio, $status)
}
