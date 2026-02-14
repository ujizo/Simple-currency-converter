# 💱 Simple Currency Converter

**Версия 1.4 | Платформа: Windows 64-bit | Лицензия: MIT**

*Профессиональное решение для конвертации валют с актуальными рыночными курсами*

[![Версия](https://img.shields.io/badge/Version-1.4-blue)](https://github.com/ujizo/Simple-currency-converter/releases)
[![Платформа](https://img.shields.io/badge/Platform-Windows_64--bit-lightgrey)]()
[![Статус](https://img.shields.io/badge/Status-Stable-brightgreen)]()

---

## 🎯 Обзор продукта

**Simple Currency Converter** - это профессиональное программное обеспечение для конвертации валют, разработанное для операционной системы Windows. Приложение обеспечивает доступ к актуальным рыночным курсам 158 мировым валют с периодичностью обновления 5 минут.

**Ключевые преимущества:**
- ✨ Готовое к использованию решение - не требует компиляции
- 🔒 Устойчивость к некорректному вводу данных
- 🌐 Актуальные курсы через API moneyconvert.net
- 📦 Полностью портативное - не требует установки
- 🛡️ Отсутствие скрытых системных требований

---

## 📥 Быстрый старт

### Вариант 1: Использование готового дистрибутива (рекомендуется)

**Шаг 1.** Загрузите дистрибутив:

| Формат | Размер | Ссылка |
|--------|--------|--------|
| ZIP | 7.18 МБ | [converter1.4.zip](https://github.com/ujizo/Simple-currency-converter/releases/download/converterfinal/converter1.4.zip) |
| RAR | 5.84 МБ | [converter1.4.rar](https://github.com/ujizo/Simple-currency-converter/releases/download/converterfinal/converter1.4.rar) |

**Шаг 2.** Извлеките содержимое архива в выбранный каталог.

**Шаг 3.** Запустите исполняемый файл `converter.exe`.

---

## 🔨 Сборка из исходного кода

### Предварительные требования

Для компиляции приложения из исходного кода требуется среда **MSYS2 с MinGW-w64**.

**Процесс установки среды разработки:**

1. Загрузите MSYS2 с [официального сайта](https://www.msys2.org/)
2. Установите в `C:\msys64`
3. Запустите **MSYS2 MinGW 64-bit**
4. Выполните обновление пакетов:
   ```bash
   pacman -Syu
   pacman -Su
   ```

5. Установите необходимые компоненты:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   pacman -S mingw-w64-x86_64-curl
   pacman -S mingw-w64-x86_64-nlohmann-json
   pacman -S mingw-w64-x86_64-git
   ```

### Процесс компиляции

**1. Клонирование репозитория:**
```bash
git clone https://github.com/ujizo/Simple-currency-converter.git
cd Simple-currency-converter
```

**2. Базовая компиляция:**
```bash
g++ -std=c++11 main.cpp converter.cpp api.cpp cache.cpp -o converter.exe -lcurl
```

**3. Статическая компиляция (автономный исполняемый файл):**
```bash
g++ -std=c++11 *.cpp -o converter.exe -static -static-libgcc -static-libstdc++ -lws2_32 -lbcrypt -lwldap32 -lz -lcrypt32 -ladvapi32 -liphlpapi -lcurl
```
**4. Если ошибка комплияции:**
```bash
g++ -std=c++11 *.cpp -o converter.exe -lcurl
```

### Формирование дистрибутива
Для создания полного дистрибутива с динамическими библиотеками выполните:
```
# Создание каталога
mkdir -p release

# Копирование исполняемого файла
cp converter.exe release/

# Копирование зависимостей В ТУ ЖЕ ПАПКУ
cp /mingw64/bin/libcurl-4.dll release/
cp /mingw64/bin/libgcc_s_seh-1.dll release/
cp /mingw64/bin/libstdc++-6.dll release/
cp /mingw64/bin/libwinpthread-1.dll release/
cp /mingw64/bin/libbrotlidec.dll release/
cp /mingw64/bin/libbrotlicommon.dll release/
cp /mingw64/bin/libnghttp2-14.dll release/
cp /mingw64/bin/libnghttp3-9.dll release/
cp /mingw64/bin/libngtcp2-16.dll release/
cp /mingw64/bin/libngtcp2_crypto_ossl-0.dll release/
cp /mingw64/bin/libcares-2.dll release/
cp /mingw64/bin/libidn2-0.dll release/
cp /mingw64/bin/libunistring-5.dll release/
cp /mingw64/bin/libpsl-5.dll release/
cp /mingw64/bin/libssh2-1.dll release/
cp /mingw64/bin/libzstd.dll release/
cp /mingw64/bin/libssl-3-x64.dll release/
cp /mingw64/bin/libcrypto-3-x64.dll release/
cp /mingw64/bin/libintl-8.dll release/
cp /mingw64/bin/libiconv-2.dll release/
cp /mingw64/bin/zlib1.dll release/

```batch
@echo off
converter.exe
pause
```


### Зависимости

- Компилятор с поддержкой C++11
- Библиотека libcurl
- Библиотека nlohmann/json для обработки JSON

---
