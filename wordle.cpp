#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void findAll(std::string in, const std::string& floating, std::set<std::string>& words, const std::set<std::string>& dict, int pos);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> words;
   // set<char> charHolder;
   set<int> posHolder;
    int wordSize = in.size();
    set<int>::iterator it;
    set<std::string>::iterator it2;
   // int pos = -1;

    //checking to se if there are any dashes
    bool dash = false;

    if(in.empty()){
        return words;
    }
    for(unsigned i =0; i<in.size(); ++i){
        
        if(in.at(i)=='-'){
            dash = true;
            posHolder.insert(i);

        }
        
    }
    if(!dash){
        words.insert(in);
        return words;
    }

   
    //at this point we know that there are dashes
   // bool hasChars;
    for(it = posHolder.begin(); it != posHolder.end();++it){
        cout<<"running "<<endl;
        findAll(in, floating, words, dict, *it);
    }
    // //test
       for(it2 = words.begin(); it2 != words.end();++it2){
        cout<<*it2<<endl;
       }


   return words;


    
    

}

// Define any helper functions here
void findAll(std::string in, const std::string& floating, std::set<std::string>& words, const std::set<std::string>& dict, int pos){    
    if(in.size()==0){
        return;
    }
    if(in[pos]=='z'){
        return;
    }


    if(in[pos]=='-'){
        in[pos] = 'a';
    }

    // if(pos!=in.size()-1){
    //     findAll(in, floating, words, pos+1);
    // }
    int counter;
    if(dict.find(in)!=dict.end()){
        for(int i =0; i<floating.size(); i++){
            if(in.find(floating[i])){
                ++counter;
                cout<<"counter working "<<endl;
            }
        }
        if(counter==floating.size()){
            cout<<"counter: "<<counter<<endl;
            words.insert(in);
        }
    }
    in[pos]++;
    findAll(in, floating, words, dict, pos);


}