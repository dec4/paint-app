#include <string>
#include <fstream>
#include <stdlib.h>

class RandomNoun {
public:
    // Default constructor generates random noun
    RandomNoun();
    // Getter for word_
    std::string GetWord();
private:
    // Stores random word
    std::string word_;
    // Method to get word from file
    void GetRandomNounFromFile();
};