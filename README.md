#  3D Рендерер с нуля

## Описание

Данный репозиторий состоит из основных двух частей: библиотеки для
отрисовки 3D объектов (лежит в `libs/YAR/`) и тестирующего её приложения
(лежит в `src/`).

## YAR - Yet Another Renderer

На данный момент библиотека предоставляет средства для отрисовки любого набора
трёхмерных объектов, а также даёт пользователю возможность управлять перемещением
камеры по миру.

## Инструкция по сборке и запуску

### Зависимости

Для гарантированной работы проекта на операционной системе Линукс необходимо
наличие следующих библиотек:

* freetype
* x11
* xrandr
* udev
* opengl
* flac
* ogg
* vorbis
* vorbisenc
* vorbisfile
* openal
* pthread

(Они необходимы для библиотеки SFML, которую приложение использует для отображения
результатов работы библиотеки)

### Сборка 

```
git clone --recurse-submodules https://github.com/SphericalPotatoInVacuum/3D_Renderer.git
cd 3D_Renderer
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

### Запуск

```
./build/app
```

## Документация

Документация к библиотеке находится по этой [ссылке](https://sphericalpotatoinvacuum.github.io/3D_Renderer/)
