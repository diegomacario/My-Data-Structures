#include <string>
#include <iostream>
#include <cctype>

using namespace std;

// 1) No vowels means no change.
// 2) Starts with a vowel means add "way" at the end of the string.
// 3) Starts with a consonant means:
//    - Extract the string of consonants up to the first vowel.
//    - Move that collection of consonants to the end of the string.
//    - Add "ay" to the end of the string.

bool isVowel(char letter)
{
    switch(letter)
    {
    case 'a': case 'e': case 'i': case 'o': case 'u':
    case 'A': case 'E': case 'I': case 'O': case 'U':
        return true;
    default:
        return false;
    }
}

void convertWordToPigLatin(string & word)
{
    if (isVowel(word[0]))
    {
        word += "way";
        return;
    }
    else
    {
        for (int i = 1; i < word.length(); ++i)
        {
            if (isVowel(word[i]))
            {
                word = word.substr(i) + word.substr(0, i) + "ay";
                return;
            }
        }
    }
}

string convertSentenceToPigLatin(const string & sentence)
{
    string sentenceInPigLatin;
    string word;

    bool parsingWord = false;
    int  startOfWord;

    for (int i = 0; i < sentence.length(); ++i)
    {
        if (isalpha(sentence[i]))
        {
            if (!parsingWord)
            {
                startOfWord = i;
                parsingWord = true;
            }
        }
        else
        {
            if (parsingWord)
            {
                word = sentence.substr(startOfWord, i - startOfWord);
                convertWordToPigLatin(word);
                sentenceInPigLatin += word;
                parsingWord = false;
            }

            sentenceInPigLatin += sentence[i]; // Copy whitespace and punctuation.
        }
    }

    if (parsingWord)
    {
        word = sentence.substr(startOfWord, sentence.length() - startOfWord);
        convertWordToPigLatin(word);
        sentenceInPigLatin += word;
        parsingWord = false;
    }

    return sentenceInPigLatin;
}

int main(int argc, char * argv[])
{
    cout << "Welcome to the Pig Latin converter!" << '\n';
    cout << "Please write a sentence and press Enter:" << '\n';

    string sentence;
    getline(cin, sentence);

    cout << "Your sentence is Pig Latin is:" << '\n';
    cout << convertSentenceToPigLatin(sentence) << '\n';

    int x;
    cin >> x;

    return 0;
}
