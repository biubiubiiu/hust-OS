:: please ensure file opened with GBK encoding !
@echo off
:: 启用变量延迟
setlocal enabledelayedexpansion

:: 使用 gbk 编码
chcp 936 > NUL

title 算命大师

:start
set /p str=请输入日期，格式为 year/month/day，如 1999/7/19  

for /f "tokens=1,2,3,* delims=/" %%a in ("%str%") do (
    set year=%%a
    set month=%%b
    set day=%%c
)

:: 错误提示信息
set error=请输入正确的日期

:: 闰年判断, flag=1 表示该年为闰年
set /a flag="^!(year %% 4) & ^!(^!(year %% 100)) | ^!(year %% 400)"

:: 日期合法性检测
if %year% leq 0   echo %error% & goto end
if %month% leq 0  echo %error% & goto end
if %month% geq 13 echo %error% & goto end
if %day%   leq 0  echo %error% & goto end

if %month% equ 1 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 3 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 4 if %day% geq 31 echo %error% & goto end else goto core
if %month% equ 5 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 6 if %day% geq 31 echo %error% & goto end else goto core
if %month% equ 7 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 8 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 9 if %day% geq 31 echo %error% & goto end else goto core
if %month% equ 10 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 11 if %day% geq 31 echo %error% & goto end else goto core
if %month% equ 12 if %day% geq 32 echo %error% & goto end else goto core
if %month% equ 2 if %flag% equ 1 if %day% geq 30 echo %error% & goto end else goto core
if %month% equ 2 if %flag% equ 0 if %day% geq 29 echo %error% & goto end else goto core

:core
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
goto start
