# 第 6 課：期末作品 —— `baseconv` 命令列進位轉換工具

## 0. 目標：做出這個

```
> .\baseconv.exe hex C8
十進位：200
十六進位：0xC8
八進位：0310
二進位：1100 1000

> .\baseconv.exe bin 102
錯誤：第 3 個字元 '2' 不是合法的 2 進位數字
```

**檔案：** `baseconv/baseconv.c`（起始模板已經放好，裡面有 TODO）
**測試：** `baseconv/tests/run_tests.ps1`（16 個自動測試，全部 PASS 就完成）

### 前 5 課的零件，各用在哪裡

| 零件 | 第幾課 | 在 baseconv 裡變成 |
|---|---|---|
| `hex_digit_value` | 4 | `digit_value`（多一個「這個進位能不能用」的檢查） |
| `value * 16 + d` | 5 | `value * base + d`（16 換成任何進位） |
| `print_binary_any` | 5 | `print_binary_grouped`（加上每 4 bit 空一格） |
| scanf 回傳值檢查、範圍檢查 | 2、3 | 非法字元、溢位檢查 |
| 結束碼 `return 1` | 4 | 0 = 成功、1 = 用法錯誤、2 = 數字錯誤 |

---

## 步驟 1：新觀念 —— 命令列參數 `argc` / `argv`

之前都用 scanf 讓使用者「執行後再輸入」。真正的命令列工具（像 `gcc`、`git`）是**執行時直接把資料寫在後面**：

```
git commit -m "訊息"
gcc -Wall hello.c
.\baseconv.exe hex C8
```

C 程式要接收這些，`main` 改成另一種標準寫法（第 4 課提過的第二種）：

```c
int main(int argc, char *argv[])
```

| 名稱 | 意思 | `.\baseconv.exe hex C8` 時 |
|---|---|---|
| `argc` | argument **count**：總共幾個字串 | 3 |
| `argv[0]` | 程式自己的名字 | 從 PowerShell 執行時是**完整路徑**，例如 `C:\...\baseconv.exe`（實測） |
| `argv[1]` | 第 1 個參數 | `"hex"` |
| `argv[2]` | 第 2 個參數 | `"C8"` |

**`argv` 就是一個「字串的陣列」**，`argv[1]` 是一個字串，用法跟第 5 課的 `char s[]` 完全一樣（`argv[2][0]` 就是 `'C'`）。
`char *argv[]` 裡的 `*` 是指標，下一個聊天室會講；現在只要知道 **`argv[i]` 是第 i 個字串**就夠了。

**先做這個實驗**——把 main 暫時改成印出所有參數：

```c
for (int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
}
```

### ⚠️ 怎麼執行有參數的程式

**Code Runner 的 ▶ 沒辦法傳參數**，要在終端機自己編譯、執行：

```
cd baseconv
gcc -Wall -Wextra -std=c17 baseconv.c -o baseconv.exe
.\baseconv.exe hex C8
```

**步驟 1 要寫的：** 參數數量不對（`argc != 3`）→ 呼叫 `print_usage()`，`return 1`。

---

## 步驟 2：新觀念 —— 用 `strcmp` 比較字串

想判斷 `argv[1]` 是不是 `"hex"`，直覺會寫：

```c
if (argv[1] == "hex")     // ❌ 錯！
```

**這樣比的是「兩個字串的地址」，不是內容**（第 5 課：陣列名稱代表開頭的地址）。兩個內容一樣的字串放在不同地方，地址不同，所以永遠不相等。

實測：執行 `.\eq.exe hex`，印出 `not same`；gcc `-Wall` 會警告 `comparison with string literal results in unspecified behavior`。

**正確做法：** 用 `<string.h>` 的 `strcmp`，它會一個字元一個字元比對：

```c
if (strcmp(argv[1], "hex") == 0) {    // 回傳 0 = 內容完全相同
    base = 16;
}
```

> `strcmp` 回傳 0 代表「相同」，這跟直覺相反，面試很愛考。（非 0 時，正負代表誰的字典順序比較前面。）

**步驟 2 要寫的：** 用 `if / else if` 判斷 `dec`→10、`hex`→16、`bin`→2、`oct`→8，都不是就印錯誤訊息 + 用法，`return 1`。

---

## 步驟 3：通用的 `parse_number` —— 一個函式處理所有進位

### 3-1. `digit_value`：從 `hex_digit_value` 改名就好

第 4 課的 `hex_digit_value` 內容**一個字都不用改**，只改名字（因為現在不只用在 hex）。

### 3-2. 關鍵想法：「這個數字在這個進位裡合法嗎？」

`digit_value('2')` 回傳 2，但二進位只能有 0 和 1！所以多一個檢查：

```
d == -1         → 根本不是數字（例如 'G'、'x'）
d >= base       → 是數字，但這個進位不能用（例如 二進位遇到 '2'、十進位遇到 'a'）
```

### 3-3. 核心公式：第 5 課的 16 換成 base

```c
value = value * base + d;
```

- 十進位 `"253"`：((0×10+2)×10+5)×10+3 = 253
- 二進位 `"1101"`：(((0×2+1)×2+1)×2+0)×2+1 = 13

**同一行程式，四種進位全部搞定**——這就是寫成「通用函式」的威力。

### 3-4. 新觀念：用 `long long` 回傳，`-1` 代表錯誤

結果最大到 4,294,967,295（`unsigned int` 最大值），而且還要有一個「錯誤訊號」。
- `int` 裝不下 42 億（第 2 課）
- `unsigned int` 沒有負數，-1 沒地方放

→ 回傳 **`long long`**：正常值 0 ～ 4,294,967,295 都裝得下，`-1` 拿來代表錯誤（第 4 課 `hex_digit_value` 的同一招）。

### 3-5. 新觀念：溢位檢查和 `#define`

使用者輸入 `4294967296`（多 1）會超過 32 bit。**每算完一位就檢查**：

```c
if (value > MAX_VALUE) { ... 錯誤 ... }
```

`MAX_VALUE` 在檔案最上面定義：

```c
#define MAX_VALUE 4294967295LL
```

`#define` 是「**取代**」：編譯前，前處理器會把程式裡所有 `MAX_VALUE` 換成 `4294967295LL`（第 2 課：編譯第一階段「前處理」）。好處是數字有名字、好讀，要改只改一個地方。（`LL` = long long 常數，第 4 課學過。）

### 3-6. `const char s[]` 是什麼？

`const` = 「這個函式保證不會修改 s」。PTT 作者的失敗教訓之一是「直接修改輸入資料」——加上 `const`，萬一不小心改到，**編譯器會直接報錯**（實測：`error: assignment of read-only location`）。

### 步驟 3 要寫的

```
parse_number(s, base)：
  1. s 是空字串（s[0] == '\0'）→ 印錯誤，回傳 -1
  2. value = 0
  3. 走過每個字元 s[i]（走到 '\0' 為止）：
       d = digit_value(s[i])
       d == -1 或 d >= base → 印「第 i+1 個字元 '?' 不是合法的 N 進位數字」，回傳 -1
       value = value * base + d
       value > MAX_VALUE → 印「數字太大」，回傳 -1
  4. 回傳 value
```

main 裡：`parse_number` 回傳 < 0 → `return 2`。

---

## 步驟 4：輸出

### 4-1. 十、十六、八進位：printf 就有

結果先轉成 `unsigned int`：

```c
unsigned int n = (unsigned int)result;    // 強制轉型（第 4 課 clock 那裡學過的 cast）
printf("十進位：%u\n", n);                 // unsigned 用 %u
printf("十六進位：0x%X\n", n);
printf("八進位：0%o\n", n);
```

### 4-2. 二進位：改造 `print_binary_any`

三個改動：

**① n = 0 的特例，換成 `do-while`**

第 5 課用 `if (n == 0)` 特別處理。更漂亮的寫法是 `do { } while (n > 0);`——**先做一次再檢查**，n = 0 時也會存進一個 0（第 3 課提過 do-while）。

**② 補 0 到 4 的倍數**

5 是 `101`，要顯示成 `0101`（湊滿一組 4 bit，對應 1 個 hex 數字）：

```c
while (count % 4 != 0) {      // 還不是 4 的倍數
    bits[count] = 0;          // 在最高位那邊補 0
    count++;
}
```

**③ 每 4 bit 空一格**

倒著印時，`i` 是「這是第幾位」（從 0 數）。當 `i` 是 4 的倍數、而且不是最後一位，印完就空一格：

```c
for (int i = count - 1; i >= 0; i--) {
    printf("%d", bits[i]);
    if (i % 4 == 0 && i != 0) {
        printf(" ");
    }
}
```

追蹤 200（`11001000`，count = 8）：印 i=7,6,5,4 → i=4 時 `4 % 4 == 0` → 空一格 → 印 i=3,2,1,0 → i=0 不空格。結果 `1100 1000` ✅

---

## 步驟 5：跑自動測試

在 `baseconv` 資料夾裡：

```
powershell -ExecutionPolicy Bypass -File tests\run_tests.ps1
```

它會自動編譯、跑 16 個測試，每個顯示 PASS 或 FAIL：

```
PASS  baseconv dec 200
PASS  baseconv hex C8
...
FAIL  baseconv bin 102  （預期結束碼 2 ...；實際結束碼 0）
結果：15 / 16 通過
```

**目標：16 / 16 通過。** 起始模板跑起來是 0 / 16——每完成一個步驟，PASS 就會變多。

> 這就是業界的**自動化測試**：每次改程式，一個指令就能確認有沒有改壞東西。履歷上也可以寫。

---

## 步驟 6：寫 `baseconv/README.md`

GitHub 上別人點進 `baseconv` 資料夾第一眼看到的就是它。至少要有：
1. 一句話說明這是什麼
2. 怎麼編譯、怎麼用（附輸出範例）
3. 支援什麼、限制是什麼（例如最大 0xFFFFFFFF、不支援負數）
4. 怎麼跑測試
5. **我學到了什麼**（用自己的話，3～5 點）

---

## 加分挑戰（選做）

1. 接受 `0x` 前綴：`baseconv hex 0xC8` 也能用（提示：如果 `s[0] == '0'` 而且 `s[1] == 'x'`，就從 `s + 2`……或從 i = 2 開始走）
2. 二進位輸入可以有空格以外的分隔，例如 `1100_1000`（遇到 `_` 就跳過）
3. 自動偵測：`baseconv 0xC8`、`baseconv 0b1100`、`baseconv 200` 只給一個參數時，從前綴判斷是哪種進位
4. 在 `run_tests.ps1` 加上你自己想到的測試案例

---

## 觀念題

1. `argc` 和 `argv` 是什麼？執行 `.\baseconv.exe hex C8` 時，`argc` 是多少？`argv[0]` 是什麼？
2. 為什麼不能用 `==` 比較兩個字串？`strcmp` 回傳 0 代表什麼？
3. `parse_number` 為什麼回傳 `long long`，不用 `int` 或 `unsigned int`？
4. `#define MAX_VALUE 4294967295LL` 在編譯的哪個階段被處理？它做了什麼？
5. 參數前面加 `const` 有什麼好處？

### 我的答案

1.
2.
3.
4.
5.
