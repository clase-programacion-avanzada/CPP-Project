#ifndef TEXT_FILEHANDLER_H
#define TEXT_FILEHANDLER_H

#include "List.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

struct TextFileHandler {

    string fileName;

    TextFileHandler(string path) {
        fileName = path;
    }

    List<string> readLines() {

        List<string> lines;
        
        fstream file;
        
        file.open(fileName, ios::in);
        
        if (file.fail()) {
            return lines;
        }
        string line;

        while (getline(file, line)) {
            lines.add(line);
        }

        file.close();

        return lines;

    }

    bool writeLines(List<string> lines, unsigned int mode = ios::out) {

        fstream file;

        file.open(fileName, mode);

        if (file.fail()) {
            return false;
        }

        for (int i = 0; i < lines.size; i++) {
            
            if(i != 0) {
                file << endl;
            }

            file << lines.get(i);
        }

        file.close();

        return true;

    }

    bool writeSingleLine(string line, unsigned int mode = ios::out | ios::app) {

        fstream file;

        file.open(fileName, mode);

        if (file.fail()) {
            return false;
        }

        file << line;

        file.close();

        return true;

    }

};

List<string> split(string line, char delimiter) {
        
        List<string> tokenList;
        //split line into tokens
        //stringstream is a stream class to operate on strings.
        stringstream ss(line);

        //see that ss.good() is used to check if the stream is good
        //it means that it checks if the stream has not reached the end of the line
        while (ss.good()) {
            //declare a string variable to store the token
            //a token is a string separated by a delimiter
            //i.e 1;1994;90;The Shawshank Redemption
            //  the delimiter is the semicolon (;)
            //  the tokens are: 1, 1994, 90, The Shawshank Redemption
            string token;
            //getline() is used to read a string from the stream
            //getline() extracts characters from the stream until it finds the delimiter character
            //and stores them in the string object 'token'
            getline(ss, token, delimiter);

            //add token to the tokenList
            tokenList.add(token);
        }

        return tokenList;

}

#endif /* MYHEADER_H */