#include "randomnoun.h"

RandomNoun::RandomNoun() {
    GetRandomNounFromFile();
}

std::string RandomNoun::GetWord() {
    return word_;
}

void RandomNoun::GetRandomNounFromFile() {
    // Open file
    std::ifstream file;
    file.open("data/nounlist.txt");
    if (!file.is_open()) {
        return;
    }

    // Generate random number (file has 4554 words)
    int random_number = rand() % 4555;
    // Use count to know which word to get
    int count = 1;

    // Go through file
    while (file >> word_) {
        if (count == random_number) {
            return;
        }
        count++;
    }
}