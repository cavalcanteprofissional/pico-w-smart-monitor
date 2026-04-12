@echo off
REM Script de build para Pico SDK v1.5.1

echo Configurando ambiente Pico SDK...

set PICO_SDK_PATH=C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\pico-sdk
set PATH=C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\cmake\bin;C:\Program Files\Raspberry Pi\Pico SDK v1.5.1\ninja;%PATH%

cd /d E:\EMBARCA\EmbarcaTech

echo Removendo build anterior...
if exist build rmdir /s /q build
mkdir build
cd build

echo Configurando projeto com CMake...
cmake -G Ninja -DPICO_SDK_PATH=%PICO_SDK_PATH% ..

if errorlevel 1 (
    echo.
    echo ERRO na configuracao do CMake!
    pause
    exit /b 1
)

echo Compilando projeto...
ninja

if errorlevel 1 (
    echo.
    echo ERRO na compilacao!
    pause
    exit /b 1
)

echo.
echo ==============================
echo Compilacao concluida!
echo Arquivo .uf2 gerado em: build\monitor_sensores_alerta.uf2
echo ==============================
echo.
pause