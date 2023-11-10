cmake_minimum_required(VERSION 3.22)

# Подключаем модуль FetchContent
include(FetchContent)

# Создаем каталог для внешних зависимостей (может быть неактивным, так как папка не используется)
# set(EXTERNAL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external)

# Добавляем и настраиваем библиотеку cxxopts
FetchContent_Declare(
  cxxopts
  GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git     # Указываем репозиторий CxxOpts
  GIT_TAG v2.2.1                                            # Устанавливаем тег версии
  GIT_SHALLOW TRUE                                          # Выполняем "плоское" клонирование
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}                         # Задаем префикс для сгенерированных файлов
)

FetchContent_MakeAvailable(cxxopts)  # Активируем и собираем библиотеку CxxOpts