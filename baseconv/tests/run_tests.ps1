# run_tests.ps1：baseconv 自動測試
# 用法（在 baseconv 資料夾裡執行）：powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1
# 每個測試：執行 baseconv，檢查「結束碼」和「輸出裡有沒有某段文字」

[Console]::OutputEncoding = [System.Text.Encoding]::UTF8
Set-Location (Split-Path $PSScriptRoot -Parent)

Write-Host "編譯 baseconv.c ..."
& gcc -Wall -Wextra -std=c17 baseconv.c -o baseconv.exe
if ($LASTEXITCODE -ne 0) {
    Write-Host "編譯失敗，請先修正錯誤" -ForegroundColor Red
    exit 1
}

# 格式：輸入的參數, 預期結束碼, 輸出裡必須出現的文字（多個用 | 分開）
$tests = @(
    @{ args = @("dec", "200");        code = 0; expect = "0xC8|0310|1100 1000" },
    @{ args = @("hex", "C8");         code = 0; expect = "200|0310|1100 1000" },
    @{ args = @("hex", "ff");         code = 0; expect = "255|0xFF|1111 1111" },
    @{ args = @("bin", "11001000");   code = 0; expect = "200|0xC8" },
    @{ args = @("oct", "310");        code = 0; expect = "200|0xC8" },
    @{ args = @("dec", "0");          code = 0; expect = "0x0|0000" },
    @{ args = @("dec", "5");          code = 0; expect = "0x5|0101" },
    @{ args = @("dec", "4294967295"); code = 0; expect = "0xFFFFFFFF|1111 1111 1111 1111 1111 1111 1111 1111" },
    @{ args = @("hex", "FFFFFFFF");   code = 0; expect = "4294967295" },
    @{ args = @("dec", "4294967296"); code = 2; expect = "" },
    @{ args = @("hex", "100000000");  code = 2; expect = "" },
    @{ args = @("dec", "12a");        code = 2; expect = "'a'" },
    @{ args = @("bin", "102");        code = 2; expect = "'2'" },
    @{ args = @("hex", "G1");         code = 2; expect = "'G'" },
    @{ args = @("abc", "5");          code = 1; expect = "" },
    @{ args = @();                    code = 1; expect = "" }
)

$pass = 0
foreach ($t in $tests) {
    $out = (& .\baseconv.exe @($t.args) | Out-String)
    $code = $LASTEXITCODE
    $ok = ($code -eq $t.code)
    if ($t.expect -ne "") {
        foreach ($e in $t.expect.Split("|")) {
            if (-not $out.Contains($e)) { $ok = $false }
        }
    }
    $name = "baseconv " + ($t.args -join " ")
    if ($ok) {
        $pass++
        Write-Host "PASS  $name" -ForegroundColor Green
    } else {
        Write-Host "FAIL  $name  （預期結束碼 $($t.code)、包含 '$($t.expect)'；實際結束碼 $code）" -ForegroundColor Red
        Write-Host $out
    }
}

Write-Host ""
Write-Host "結果：$pass / $($tests.Count) 通過"
if ($pass -ne $tests.Count) { exit 1 }
