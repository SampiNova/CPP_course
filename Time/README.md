# Time (5, 6, 7.1 задания)

### Структура проекта
В папке репозитория есть поддиректория time. В ней лежат файлы библиотеки Time, содержащей и классы Watch тоже.

В примерах команд для сборки, все исполняемые файлы и make скрипты будут собираться в папку build. При необходимости замените build на ваше название.
В ней будут лежать все файлы, создаваемые cmake, в том числе исполняемый файл main и статическая библиотека Time.

### Сборка и запуск проекта
В сборке участвуют два CMakeLists.txt. Главный, находящийся в папке репозитория, собирает проект и вызывает сборку библиотки Time (папка time).

Все команды необходимо выполнять, находясь в папке репозитория.

Для сборки проекта выполните команды ниже:
Внимание: В коде используется сторонняя библиотека gtests, по умолчанию с сборочнм файле (./test/CMakeLists.txt) установлен флаг GET_GTESTS=ON, если этот флаг ON, то выполняется скачивание и подключение библиотеки из git-репозитория. Если `gtest/gtest.h` у вас уже находится в PATH, то вы можете выключить установку из интернета указав `-DGET_GTESTS=OFF` в качестве аргумента в первой команде ниже.
```
cmake -S. -B build
cmake --build build
```
Для сборки без скачивания гугл тестов:
```
cmake -S. -B build -DGET_GTESTS=OFF
cmake --build build
```
Если необходимо собрать код с использованием конкретного компилятора, выполниите:
```
cmake -S. -B build -G "<название компилятора>"
cmake --build build
```
Если нет необходимости собирать код с юнит-тестами, добавте в команду `-DMAKE_TEST=OFF`:
```
cmake -S. -B build -G "<название компилятора>" -DMAKE_TEST=OFF
cmake --build build
```

В результате сборки будет создана статическая библиотека Time.a по пути ./build/time, а исполняемый файл main будет находится по пути ./build.
Для запуска кода необходимо выполнить `./build/main` в командной строке.
Для запуска юнит-тестов выполните `./build/test/test`, либо `ctest`. Если необходимо запустить одну нужную группу тестов, можно выполнить `ctest -R <интересующая вас группа тестов>` (Например `ctest -R Constructor`). Можно добавить `-V` для более подробного вывода результатов тестирования.


