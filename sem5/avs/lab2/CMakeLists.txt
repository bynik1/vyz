# CMakeLists.txt

# Указываем минимальную версию CMake
cmake_minimum_required(VERSION 3.22)

# Задаем имя проекта и его версию
project(
  HelloCmake
  VERSION 1.0
  LANGUAGES CXX
)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)#Эта строка добавляет дополнительные пути поиска модулей CMake. 
#Обычно используется для поиска пользовательских модулей с дополнительными командами CMake.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)#Эта строка определяет директорию, 


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

set(target_name app)  # Задаем имя цели (исполняемого файла) как "app"

# Добавляем исполняемый файл main.cpp
add_executable(app main.cpp)  # Создаем исполняемый файл "app" из "main.cpp"

target_sources(
  ${target_name}
  PRIVATE
    main.cpp
)  # Указываем исходные файлы, в данном случае "main.cpp"

# Линкуемся с библиотекой fts и библиотекой cxxopts
target_link_libraries(
  ${target_name}
    PRIVATE
      cxxopts
)  # Устанавливаем зависимости исполняемого файла "app"
