#ifndef BINARY_FILEHANDLER_H
#define BINARY_FILEHANDLER_H

#include "List.h"
#include <string>
#include <fstream>

using namespace std;

template <typename T>
struct BinaryFileHandler {

    string fileName;

    BinaryFileHandler(string path) {
        fileName = path;
    }
    
    bool writeBinaryFile(List<T> list) {

        fstream file;

        file.open(fileName, ios::out | ios::binary);

        if (file.fail()) {
            return false;
        }

        for (int i = 0; i < list.size; i++) {
            T element = list.get(i);
            file.write(reinterpret_cast<char *>(&element), sizeof(T));
        }

        file.close();

        return true;
    }

    List<T> readBinaryFile() {

        List<T> list;

        fstream file;

        file.open(fileName, ios::in | ios::binary);

        if (file.fail()) {
            return list;
        }

        T element;

        while(file.read(reinterpret_cast<char *>(&element), sizeof(T))) {
            list.add(element);
        }

        file.close();


        return list;
    }

    bool appendElementToFile(T element) {
        
        fstream file;

        file.open(fileName, ios::out | ios::app | ios::binary);

        if (file.fail()) {
            return false;
        }

        file.write(reinterpret_cast<char *>(&element), sizeof(T));

        file.close();

        return true;
    }

    T getElementFromFile(int index) {

        fstream file;

        file.open(fileName, ios::in | ios::binary);

        if (file.fail()) {
            return T();
        }

        file.seekg(index * sizeof(T), ios::beg);

        T element;

        file.read(reinterpret_cast<char *>(&element), sizeof(T));

        file.close();

        return element;
    }

    bool removeElementFromFile(int index) {

        fstream file;

        List<T> list = readBinaryFile();

        if (index < 0 || index >= list.size) {
            return false;
        }

        list.remove(index);

        return writeBinaryFile(list);
        
    }

    int getFileSize() {

        fstream file;

        file.open(fileName, ios::in | ios::binary);

        if (file.fail()) {
            return -1;
        }

        file.seekg(0, ios::end);
        int fileSize = file.tellg();
        file.close();

        return fileSize;
    }


   


};

 bool binaryFileExists(string fileName) {

        fstream file;

        file.open(fileName, ios::in | ios::binary);

        if (file.fail()) {
            return false;
        }

        file.close();

        return true;
    }

#endif /* MYHEADER_H */