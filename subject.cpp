#include "Subject.h"

std::string Subject::replace_words(const ArgsMap& args) {
    std::string text = args.at("text");
    std::string old_word = args.at("old_word");
    std::string new_word = args.at("new_word");

    size_t pos = 0;
    while ((pos = text.find(old_word, pos)) != std::string::npos) {
        text.replace(pos, old_word.length(), new_word);
        pos += new_word.length();
    }
    return text;
}

std::string Subject::find_phrases(const ArgsMap& args) {
    std::string text = args.at("text");
    std::string phrase = args.at("phrase");
    return (text.find(phrase) != std::string::npos) ? "Found" : "Not Found";
}

std::string Subject::capitalize_words(const ArgsMap& args) {
    std::string text = args.at("text");
    std::istringstream stream(text);
    std::string word, result;

    while (stream >> word) {
        word[0] = std::toupper(word[0]);
        result += word + " ";
    }

    if (!result.empty()) {
        result.pop_back(); // Delete last space
    }

    return result;
}

std::string Subject::capitalize_sentences(const ArgsMap& args) {
    std::string text = args.at("text");
    bool capitalize_next = true;

    for (char& ch : text) {
        if (capitalize_next && std::isalpha(ch)) {
            ch = std::toupper(ch);
            capitalize_next = false;
        }
        if (ch == '.' || ch == '!' || ch == '?') {
            capitalize_next = true;
        }
    }

    return text;
}

std::string Subject::number_sentences(const ArgsMap& args) {
    std::string text = args.at("text");
    std::istringstream stream(text);
    std::ostringstream result;
    std::string sentence;
    size_t counter = 1;

    while (std::getline(stream, sentence, '.')) {
        if (!sentence.empty()) {
            result << counter++ << ". " << sentence << ".\n";
        }
    }

    return result.str();
}
