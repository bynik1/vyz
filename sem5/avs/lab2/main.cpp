#include <iostream>
#include <fstream>
#include <cxxopts.hpp>

int main(int argc, char* argv[]) {
    cxxopts::Options options("MyProgram", "Программа для чтения файла и вывода его содержимого");
    options.add_options()
        ("f,file", "Путь к файлу", cxxopts::value<std::string>());

    std::string filePath;

    try {
        auto result = options.parse(argc, argv);
        if (result.count("file")) {
            filePath = result["file"].as<std::string>();
        } else {
            std::cerr << "Необходимо указать путь к файлу через --file или -f." << std::endl;
            return 1;
        }
    } catch (const cxxopts::OptionException& e) {
        std::cerr << "Ошибка парсинга аргументов: " << e.what() << std::endl;
        return 1;
    }

    std::ifstream fileStream(filePath);
    if (fileStream) {
        std::cout << "Содержимое файла " << filePath << ":" << std::endl;
        std::cout << fileStream.rdbuf();
    } else {
        std::cerr << "Не удалось открыть файл: " << filePath << std::endl;
        return 1;
    }

   // Чтение команд из стандартного ввода
    std::string input;
    while (true) {
        std::cout << "Введите команду ('exit' для завершения программы): ";
        std::getline(std::cin, input);
        if (input == "exit") {
            std::cout << "Программа завершает работу по команде пользователя." << std::endl;
            break;
        } else {
            std::cout << "Вы ввели: " << input << std::endl;
            // В этом месте можно добавить другие обработки для введенных команд
        }
    }


    return 0;
}
