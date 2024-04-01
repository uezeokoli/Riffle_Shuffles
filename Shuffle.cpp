// /****************************************************************************************
// *  Shufffle.cpp
// *  Displays the amount of riffle shuffles to needed until back to orignial order
// *****************************************************************************************/
#include<iostream>
#include<string>
#include<stdexcept>
#include <fstream>
#include"List.h"

using namespace std;

//riffle shuffle
void shuffle(List& D){
    List left;
    int left_cards = D.length()/2;
    D.moveFront();
    // cout<<"originial = " << D<<endl;
    for(int i = 0; i < left_cards; i++){
        left.insertBefore(D.moveNext());
        D.eraseBefore();
    }
    // cout<<"without left = " << D<<endl;
    // cout<< "left ="<<left<<endl;
    D.moveNext();
    left.moveFront();
    // cout<<"left pos = " << left.position()<< " leftCards = " << left_cards<<endl;
    while (left.position()<left_cards){
        D.insertAfter(left.moveNext());
        D.moveNext();
        if (D.position()==D.length()){
            break;
        }
        D.moveNext();
    }
    // cout<<"shuffled = " << D<<endl;
    // cout<<endl;
}
int main(int argc, char *argv[]){
    if (argc != 2){
        fprintf(stderr, "Invalid number of command line arguments\n");
        exit(EXIT_FAILURE);
    }
    List D, Sorted;
    int shuffles = 1;
    string outfile = "out";
    outfile += argv[1];
    outfile += ".txt";
    int decks = atoi(argv[1]);
    
    fstream my_file;             //openning output file
    my_file.open(outfile, ios::out);  //ios::out specifies openning a file for writing

    my_file << "deck size       shuffle count\n------------------------------\n";


    for (int cards = 1; cards<=decks; cards++){
        my_file <<" " <<cards << "\t\t\t\t ";
        for (int i = 0; i < cards; i++){
            D.insertBefore(i);
        }
        Sorted = D;
        shuffle(D);
        while(true){
            if (D == Sorted){
                my_file << shuffles <<endl;
                break;
            }
            shuffle(D);
            shuffles++;
        }

        shuffles = 1;
        D.clear();
        Sorted.clear();

    }
    my_file.close();

}
