:: please ensure file opened with GBK encoding !
@echo off
:: 启用变量延迟
setlocal enabledelayedexpansion

:: 使用 gbk 编码
chcp 936 > NUL

title 算命大师
set /p str=请输入日期，格式为 year/month/day，如 1999/7/19  

for /f "tokens=1,2,3,* delims=/" %%a in ("%str%") do (
    set year=%%a
    set month=%%b
    set day=%%c
)

if %year% leq 0   echo 无效输入 goto end
if %month% leq 0  echo 无效输入 & goto end
if %month% geq 32 echo 无效输入 & goto end
if %day% leq 0    echo 无效输入 & goto end
if %day% geq 32   echo 无效输入 & goto end

:: 输出生肖
set zodiac=猴鸡狗猪鼠牛虎兔龙蛇马羊
set /a yy=%year%%%12
echo 你属!zodiac:~%yy%,1!

:: 输出星座
if %day% leq 9 (set /a monthAndDay="%month%0%day%" ) else (set /a monthAndDay="%month%%day%")
if %monthAndDay% leq 119 echo 摩羯座 & goto end
if %monthAndDay% leq 218 echo 水瓶座 & goto end
if %monthAndDay% leq 320 echo 双鱼座 & goto end
if %monthAndDay% leq 419 echo 白羊座 & goto end
if %monthAndDay% leq 520 echo 金牛座 & goto end
if %monthAndDay% leq 621 echo 双子座 & goto end
if %monthAndDay% leq 722 echo 巨蟹座 & goto end
if %monthAndDay% leq 822 echo 狮子座 & goto end
if %monthAndDay% leq 922 echo 处女座 & goto end
if %monthAndDay% leq 1023 echo 天秤座 & goto end
if %monthAndDay% leq 1122 echo 天蝎座 & goto end
if %monthAndDay% leq 1221 echo 射手座 & goto end
echo 摩羯座 & goto end

:end
pause
