#include <iostream>
#include <fstream>
#include <string>
#include "queue.h"
#include "linearlist.h"
#define N 5757
using namespace std;

struct wordInfo{
    string word;
    int nextWord;
    LinearList <int> adjList;
};

int wordIndex(wordInfo[N], string);
int hamming(string, string);

int main() {

    Queue<int> Q;
    wordInfo wordList[N];
    //reading the file content into a string array
    ifstream file;
    file.open("sgb-words");
    string tmp;
    int count = 0;
    while (getline(file, tmp)) {
        wordList[count].word = tmp;
        wordList[count].nextWord = -1;
        count++;
    }
    file.close();

    //finding words with hamming distance one and adding them to the list

    for(int i = 1; i < N; i++){
        for(int j=0; j < i; j++) {
         if(hamming(wordList[i].word, wordList[j].word)==1){
             wordList[j].adjList.insert(0,i);
             wordList[i].adjList.insert(0,j);
         }
        }
    }


    //asking users to input two words
    string word1, word2;
    cin >> word1 >> word2;

    int w1Index = wordIndex(wordList, word1);
    int w2Index = wordIndex(wordList, word2);
    int w;

    if (w1Index == -2 or w2Index == -2){
        cout << "Word not found." << endl;
        return 1;
    }
    else {
        wordList[w1Index].adjList.clear();
        Q.enqueue(w2Index);
        while (!Q.isEmpty()) {
            w = Q.dequeue();

            for (int i = 0; i < wordList[w].adjList.size(); i++){
                int v = wordList[w].adjList[i];
                if ((wordList[v].nextWord == -1) and (v != w2Index)) {
                    wordList[v].nextWord = w;
                    Q.enqueue(v);
                }
            }
        }

        if (wordList[w1Index].nextWord != -1) {
            wordList[w1Index].adjList.insert(wordList[w1Index].adjList.size(), w1Index);
            w = wordList[w1Index].nextWord;
            while (w != -1) {
                wordList[w1Index].adjList.insert(wordList[w1Index].adjList.size(), w);
                w = wordList[w].nextWord;
            }
        }
    }
        if(wordList[w1Index].adjList.isEmpty()){
            cout << "No word ladder exists." << endl;
        }
        else{
            cout << "The word ladder is:" << endl;
            for(int i= 0 ; i < wordList[w1Index].adjList.size(); i++){
                cout << wordList[wordList[w1Index].adjList[i]].word << endl;
            }
        }
    return 0;
}


int wordIndex(wordInfo w[N], string str){
    for(int i=0; i<N;i++){
        if(w[i].word ==str){
            return i;
        }
    }
    return -2;
}

int hamming(string str1, string str2) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (str1[i] != str2[i]) {
            count++;
        }
    }
    return count;
}
