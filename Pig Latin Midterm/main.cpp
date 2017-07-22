/*
 Andre Carrera
 26-707-7444
 CS 142 Fall 2015 Midterm 2 Exam.
 
 
 In converting a word to Pig Latin, there are two important cases:
 If the word starts with a vowel (“a”, “e”, “i”, “o” or “u”), then you just add “yay” to the end. For example, the word "is"
 would translate to "isyay".
 If the first letter is NOT a vowel then you 1) remove the first syllable from the beginning of the word, 2) put it at the end
 of the word and 3) add the suffix "ay". For this lab, we will define the first “syllable” as all leading consonants. For
 example, the word "stop" would translate to "opstay".
 
 
 
 test cases:
 Please enter a phrase to translate: (or opstay to stop) "This is goin' to check : everything that.. ..could.. go wrong with .this.
 Print words: "This is goin' to check : everything that.. ..could.. go wrong with .this.
 Here is the translation: "isthay isyay oingay' otay eckchay : everythingyay atthay.. ..ouldcay.. ogay ongwray ithway .isthay.
 
 Please enter a phrase to translate: (or opstay to stop) "I" am pretty sure It's even cheching for "Capitals".
 Print words: "I" am pretty sure It's even cheching for "Capitals".
 Here is the translation: "Iyay" amyay ettypray uresay It'yay' evenyay echingchay orfay "Apitalscay".
 
 Please enter a phrase to translate: (or opstay to stop) nly cnsnnt
 Print words: nly cnsnnt
 Here is the translation: nlyay cnsnntay
 
 Please enter a phrase to translate: (or opstay to stop) opstay
 ...All done!
 
 
 Please enter a phrase to translate: (or opstay to stop) This Midterm, was a ton of : work.
 Print words: This Midterm, was a ton of : work.
 Here is the translation: isthay Idtermmay, asway ayay ontay ofyay : orkway.
 
 Please enter a phrase to translate: (or opstay to stop) One hunderdred precent, would be #awesome.
 Print words: One hunderdred precent, would be #awesome.
 Here is the translation: Oneyay underdredhay ecentpray, ouldway ebay #awesomeyay.
 
 Please enter a phrase to translate: (or opstay to stop) aeiou.
 Print words: aeiou.
 Here is the translation: aeiouyay.

 Please enter a phrase to translate: (or opstay to stop) opstay
 ...All done!
 
 
 Please enter a phrase to translate: (or opstay to stop) Don't stop, until I tell you to ""stop"".
 Print words: Don't stop, until I tell you to ""stop"".
 Here is the translation: On'day' opstay, untilyay Iyay elltay ouyay otay ""opstay"".
 
 Please enter a phrase to translate: (or opstay to stop) .stop.
 Print words: .stop.
 Here is the translation: .opstay.
 
 Please enter a phrase to translate: (or opstay to stop) .stp.
 Print words: .stp.
 Here is the translation: .stpay.
 
 Please enter a phrase to translate: (or opstay to stop) opstay
 ...All done!
 

 */


#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

const int NOTFOUND = -1;//Global CONSTANTS.
const int FIRST = 0;
const int NEXT = 1;
const int BEFORE = 1;
const string YAYEND= "yay";
const string AYEND = "ay";

void printPhrase (vector <string> inputVector); //prints out the whole vector.


void makeLowerCase (string & pigWord);//makes all the characters in the word lowercase


void printPiglatin (vector <string> pigOutput); //prints out the whole vector.


int vowelCheck (unsigned long charLocation,string tempWord); //checks for vowels at the start of a word


void addConsenants (string & pigWord,  vector <char> & consenants, vector <char> punctuation);//adds the consenants to the end of the word.


void pigLatinForConsenants (vector <char> & consenants,string & pigWord, string & tempWord, unsigned long & charLocation, int & vowelFound, vector <string> & pigOutput, vector <char> punctuation);//puts anything that starts with consenants in pig latin


void puntuationFix (vector <char> & punctuation,string & pigWord, string & tempWord, unsigned long & charLocation, int vowelFound, vector <string> & pigOutput, vector <char> & consenants ); //puts anything inside of punctuation in pig latin


int main() {
    const string STOPCOMMAND = "opstay";


    vector <string> inputVector; //the vector of the whole line
    vector <string> pigOutput;
    vector <char> consenants;
    vector <char> punctuation;
    string tempWord = "";
    string pigWord = "";



    
    
    while (true) {//loop until user breaks.
        
        cout << "Please enter a phrase to translate: (or opstay to stop) "; //prompt user
        string userInput;
        getline(cin, userInput); //input whole line
        
        if (userInput == STOPCOMMAND ) { //if opstay, quit the program
            cout << "...All done!" << endl;
            break;
        }
        
        istringstream streamInput(userInput);
        string eachWord;
        while (streamInput >> eachWord ) {
            inputVector.push_back(eachWord);
        }
        
        
        cout << "Print words: ";
        printPhrase(inputVector); //print out the whole vector
        
        
        for (unsigned long wordcounter= FIRST; wordcounter< inputVector.size(); wordcounter++) {//checks each word
            tempWord = inputVector[wordcounter];
            
            unsigned long charLocation = FIRST; //resets to start at the first character
            
            int vowelFound = vowelCheck(charLocation, tempWord);//checks to see if it's a vowel.

            if (isalpha(tempWord[charLocation]) ==false ){//if it starts with puntuation
                
                puntuationFix( punctuation,pigWord,tempWord,charLocation, vowelFound, pigOutput, consenants );//puts it in pig latin

                pigOutput.push_back(pigWord);//sends it to the string vector
            }
            
            else if (vowelFound > NOTFOUND) {//if first letter is a vowel,
                for (unsigned long charCounter = FIRST; charCounter < tempWord.size(); charCounter++) {//loop through
                    if (isalpha( tempWord[charCounter]) == false  ) {//if character is not a letter
                        punctuation.push_back(tempWord[charCounter]); //then add it to the punctuation vector
                        
                    }
                    
                }
                string punEnd = ""; //clear the string
                for (unsigned long punCounter =FIRST; punCounter < punctuation.size(); punCounter++) {//string punEnd gets all in char vector of punctuation
                    punEnd = punEnd + punctuation[punCounter];
                }
                
                for (unsigned long charCounter = FIRST; charCounter < tempWord.size() - punctuation.size(); charCounter++) {//adds first letters to pigWord
                    pigWord = pigWord + tempWord[charCounter];
                }
                
                pigWord = pigWord + YAYEND + punEnd;//then add a yay to the end

                pigOutput.push_back(pigWord);//sends to string vector
                punctuation.clear();//resests the vector fo puntuation
            }
            else if (vowelFound == NOTFOUND && isalpha(tempWord[FIRST]) ==true ) { //if it's not a vowel but a consenant
                
                
                pigLatinForConsenants (consenants,pigWord, tempWord, charLocation, vowelFound, pigOutput, punctuation );// sets consenants to pig latin

                pigOutput.push_back(pigWord);
                
            }
            
            
            consenants.clear();//clear the consenants vector
            
            
            pigWord = "";//clear the pig word.
            
        }
        
        cout << "Here is the translation: ";
        printPiglatin(pigOutput);//print out the vector of strings

        cout << endl;
        
        pigOutput.clear(); //resets the vector for output.
        inputVector.clear(); //resets the vector for input.
        
    }
    return 0;
}
void printPhrase (vector <string> inputVector) //prints out the whole vector.
{
    for (int counter = FIRST; counter < inputVector.size(); counter++) {
        cout << inputVector [counter] << " "; //prints it out one word at a time.
        
    }
    cout << endl;
}

void makeLowerCase (string & pigWord)
{
    for (int character = FIRST; character < pigWord.length(); character++) {
        pigWord[character] = tolower(pigWord[character]); // Convert each character to lowercase
    }
}
void printPiglatin (vector <string> pigOutput) //prints out the whole vector.
{
    for (int counter = FIRST; counter < pigOutput.size(); counter++) {
        cout << pigOutput [counter] << " "; //prints it out one word at a time.
        
    }
    cout << endl;
}

int vowelCheck (unsigned long charLocation,string tempWord) //checks for vowels at the start of a word
{
    const char VOWELS [] = {'a','e','i','o','u','A','E','I','O','U'};
    const int VOWELSIZE = 10;
    int index = -1 ;
    double CAST = 1.0;
    for (int counter = FIRST; counter< VOWELSIZE; counter++) { //goes through the vowels one at a time
        if (VOWELS[counter] == tempWord[charLocation]) {
            index =charLocation*CAST;
            break;
        }
    }
    return index;
}

void addConsenants (string & pigWord,  vector <char> & consenants, vector <char> punctuation){//adds the consenants to the end of the word.
    unsigned long wholeSize = pigWord.size()+ consenants.size() ;
    unsigned long consenantcounter = FIRST;
    for (unsigned long character = pigWord.size(); character < wholeSize ; character++) {
        
        pigWord = pigWord + consenants[consenantcounter];// then pigword gets the rest of the consenants on the end
        
        consenantcounter++;
    }
    
    
}

void pigLatinForConsenants (vector <char> & consenants,string & pigWord, string & tempWord, unsigned long & charLocation, int & vowelFound, vector <string> & pigOutput, vector <char> punctuation){//loop to set pigword to piglatin of the input
    punctuation.clear();
    for (unsigned long charCounter = FIRST; charCounter < tempWord.size(); charCounter++) {
        if (isalpha( tempWord[charCounter]) == false  ) {//if character is not a letter
            punctuation.push_back(tempWord[charCounter]); //then add it to the punctuation vector
            
        }
        
    }
    string punEnd = "";
    for (unsigned long character =FIRST; character < punctuation.size(); character++) {//string punStart gets all in char vector of punctuation
        punEnd = punEnd + punctuation[character];
    }
    
    
    for (unsigned long charCounter = FIRST; charCounter < tempWord.size() - punctuation.size(); charCounter++) {//check each letter of the word.
        
        
        consenants.push_back(tempWord[charCounter]);//then add that to the vector of consenants.
        bool firstUppercase = false;
        if (isupper(tempWord[charCounter])== true) {//if the first letter is capital
            firstUppercase = true;//then mark it.
        }
        charLocation = charLocation +NEXT; //set location to next chacter
        
        vowelFound = vowelCheck(charLocation, tempWord);//checks next character to see if it's a vowel
        if (vowelFound > NOTFOUND) {//if the next character is a vowel
            unsigned long pigcounter = FIRST;
            for (unsigned long character = charLocation; character < tempWord.size() - punctuation.size(); character++) {//if it finds a vowel.
                
                pigWord = pigWord + tempWord[character];// then pigword gets the rest of the letters up till the puntuation
                pigcounter++;
            }
            addConsenants (pigWord, consenants, punctuation);//adds the consenants to the end of the pigword.
            makeLowerCase (pigWord);
            if (firstUppercase == true) {
                pigWord[FIRST] = toupper(pigWord[FIRST]);
            }
            
            pigWord = pigWord + AYEND + punEnd;
            
            break;
        }
        else if (charCounter == tempWord.size() - BEFORE - punctuation.size() && vowelFound ==NOTFOUND){//if the last letter is still not a vowel
            
            addConsenants (pigWord, consenants, punctuation);//adds the consenants to the end of the pigword.
            
            pigWord = pigWord + AYEND  + punEnd;
            
            break;
        }
        
        
        
    }
}

void puntuationFix (vector <char> & punctuation,string & pigWord, string & tempWord, unsigned long & charLocation, int vowelFound, vector <string> & pigOutput, vector <char> & consenants )
{
    vector<char> PigVector;
    string punStart = "";
    string punEnd = "";
    
    
    for (unsigned long charCounter = FIRST; charCounter < tempWord.size(); charCounter++) {//check each letter of the word for puntuation
        
        charLocation = charCounter;
        if (isalpha(tempWord[charCounter]) == true) {//if it's a letter
            
            break;
        }
        else if (isalpha(tempWord[charCounter])== false){//if it's puntuation
            punctuation.push_back(tempWord[charCounter]);//then add that to the vector of puntuation.
            if (charCounter == tempWord.size() - BEFORE) {//if it doesn't go through the break.
                charLocation++;// go to the next one
            }
        }
        
    }
    for (unsigned long character =FIRST; character < punctuation.size(); character++) {//string punStart gets all in char vector of punctuation
        punStart = punStart + punctuation[character];
    }
    
    punctuation.clear();
    
    if (charLocation< tempWord.size()) {// if theres still characters left.
        for (unsigned long charCounter = charLocation; charCounter < tempWord.size(); charCounter++) {//check each letter of the word.
            
            if (isalpha(tempWord[charCounter]) == true) {//if it's a letter
                PigVector.push_back(tempWord[charCounter]);//then add that to the vector of letters.
                
            }
            else if (isalpha(tempWord[charCounter])== false){//if it's puntuation
                break;
                
            }
        }
        
        for (unsigned long character =FIRST; character < PigVector.size(); character++) {//string pigWord gets all in char vector of letters
            pigWord = pigWord  + PigVector[character];
        }
        unsigned long pigSize = pigWord.size();
        unsigned long tempCharLocation = punStart.size() + pigSize;// sets a temp location to the start of the new punctuation
        
        vowelFound = vowelCheck(charLocation, tempWord);//checks to see if it's a vowel.
        if (vowelFound > NOTFOUND) {//if charLocation letter is a vowel,
            pigWord = pigWord + YAYEND;//then add a yay to the end
            
            charLocation = tempCharLocation;
        }
        else if (vowelFound == NOTFOUND && isalpha(tempWord[charLocation]) ==true ) { //if it's not a vowel but a consenant
            
            string newTempWord = tempWord;//sets a new temporary word
            tempWord = pigWord;
            
            
            
            pigWord = "";//clear pig word
            charLocation = FIRST;
            pigLatinForConsenants (consenants,pigWord, tempWord, charLocation, vowelFound, pigOutput, punctuation );//goes through function
            charLocation = tempCharLocation;
            tempWord = newTempWord;
            
        }
        
        if (charLocation <tempWord.size() ) { //if the charLocation is not done checking
            for (unsigned long charCounter = charLocation; charCounter < tempWord.size(); charCounter++) {//check each letter of the word for puntuation
                
                punctuation.push_back(tempWord[charCounter]);//then add the rest to the vector of consenants.
                
            }
            
            for (unsigned long character =FIRST; character < punctuation.size(); character++) {//string punStart gets all in char vector of punctuation
                punEnd = punEnd + punctuation[character];
                
            }
            
            punctuation.clear();
            
            
        }
    }
    
    pigWord = punStart + pigWord + punEnd;
    
    
}

