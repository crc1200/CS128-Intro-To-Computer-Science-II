#include "functions.hpp"

#include <iostream>
#include <string>

std::string Space(std::string word, std::string full, unsigned int location) {
  if (word[word.size() - 1] == '-') {
    word.erase(word.size() - 1);
  }
  word += full[location];
  return word;
}

std::string U(char next) {
  if (next == 'i') {
    return "ooey-";
  } else {
    return "oo-";
  }
}

std::string O(char next) {
  if (next == 'i') {
    return "oy-";
  } else if (next == 'u') {
    return "ow-";
  } else {
    return "oh-";
  }
}

std::string I(char next) {
  if (next == 'u') {
    return "ew-";
  } else {
    return "ee-";
  }
}

std::string Check(std::string word) {
  if (word[word.size() - 1] == '-') {
    word.erase(word.size() - 1);
  }
  return word;
}
int ACheck(std::string word) {
  if (word[word.size() - 2] == 'e' || word[word.size() - 2] == 'w') {
    return 1;
  }
  return 0;
}
int UCheck(std::string word) {
  if (word[word.size() - 2] == 'y') {
    return 1;
  }
  return 0;
}
int OCheck(std::string word) {
  if (word[word.size() - 2] == 'w' || word[word.size() - 2] == 'y') {
    return 1;
  }
  return 0;
}
int ICheck(std::string word) {
  if (word[word.size() - 2] == 'w') {
    return 1;
  }
  return 0;
}
int ECheck(std::string word) {
  if (word[word.size() - 2] == 'y' || word[word.size() - 2] == 'o') {
    return 1;
  }
  return 0;
}

std::string E(char next) {
  if (next == 'u') {
    return "eh-oo-";
  }
  if (next == 'i') {
    return "ay-";
  } else {
    return "eh-";
  }
}

std::string W(std::string word, unsigned int index) {
  if (index == 0) {
    return "w";
  }
  if (tolower(word[index - 1]) == 'i' || tolower(word[index - 1]) == 'e') {
    return "v";
  } else {
    return "w";
  }
}

std::string A(char next) {
  if (next == 'i' || next == 'e') {
    return "eye-";
  }
  if (next == 'o' || next == 'u') {
    return "ow-";
  } else {
    return "ah-";
  }
}

std::string Base(std::string test) {
  std::string result;
  for (unsigned int i = 0; i < test.size(); i++) {
    switch (tolower(test[i])) {
    case 'a':
      result += A(tolower(test[i + 1]));
      i += ACheck(result);
      break;
    case 'e':
      result += E(tolower(test[i + 1]));
      i += ECheck(result);
      break;
    case 'i':
      result += I(tolower(test[i + 1]));
      i += ICheck(result);
      break;
    case 'o':
      result += O(tolower(test[i + 1]));
      i += OCheck(result);
      break;
    case 'u':
      result += U(tolower(test[i + 1]));
      i += UCheck(result);
      break;
    case 'w':
      result += W(result, i);
      break;
    case 'p': case 'k': case 'h': case 'l': case 'n': case 'm':
      result += tolower(test[i]);
      break;
    case ' ': case '\'':
      result = Space(result, test, i);
      break;
    default:
      return test + " contains a character not a part of the Hawaiian language.";
    }
  }
  return Check(result);
}
