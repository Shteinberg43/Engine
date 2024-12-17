#include <iostream>
#include <fstream>
#include "Subject.h"
#include "Engine.h"

std::string read_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    std::ostringstream content;
    content << file.rdbuf();
    return content.str();
}

void write_to_file(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    file << content;
}

int main() {
    Subject subj;

    Wrapper replace_wrapper(&subj, &Subject::replace_words, { {"text", ""}, {"old_word", ""}, {"new_word", ""} });
    Wrapper find_wrapper(&subj, &Subject::find_phrases, { {"text", ""}, {"phrase", ""} });
    Wrapper capitalize_words_wrapper(&subj, &Subject::capitalize_words, { {"text", ""} });
    Wrapper capitalize_sentences_wrapper(&subj, &Subject::capitalize_sentences, { {"text", ""} });
    Wrapper number_sentences_wrapper(&subj, &Subject::number_sentences, { {"text", ""} });

    Engine engine;
    engine.register_command("replace_words", &replace_wrapper);
    engine.register_command("find_phrases", &find_wrapper);
    engine.register_command("capitalize_words", &capitalize_words_wrapper);
    engine.register_command("capitalize_sentences", &capitalize_sentences_wrapper);
    engine.register_command("number_sentences", &number_sentences_wrapper);

    std::cout << engine.execute("replace_words", { {"text", "hello world"}, {"old_word", "world"}, {"new_word", "universe"} }) << std::endl;
    std::cout << engine.execute("find_phrases", { {"text", "hello apple world "}, {"phrase", "apple world"} }) << std::endl;
    std::cout << engine.execute("capitalize_words", { {"text", "hello world"} }) << std::endl;
    std::cout << engine.execute("capitalize_sentences", { {"text", "hello. world! this is test."} }) << std::endl;
    std::cout << engine.execute("number_sentences", { {"text", "This is sentence one.This is sentence two."} }) << std::endl;

    try {
        std::string input_text = read_from_file("input.txt");
        std::string result = engine.execute("replace_words", { {"text", input_text}, {"old_word", "apple"}, {"new_word", "melon"} });
        write_to_file("output.txt", result);
        std::cout << "Processing completed. Check output.txt for results." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}