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
void findAll(const std::string& in, std::set<std::string>& words, const std::set<std::string>& dict, int pos, std::string& temp);
bool isThere(char floating,std::string in,int pos );
void permute(string& in, int start, int end, set<std::string>& combo, const std::string& floating, int idx);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<std::string> words;
    set<std::string> combo;
   // set<char> charHolder;
  // set<int> fixed;
    int wordSize = in.size();
    set<int>::iterator it;
    set<std::string>::iterator it2;
   // int pos = -1;

    //checking to se if there are any dashes
    string newIn = in;

    bool dash = false;

    if(in.empty()){
        return words;
    }




        //cout<<"segfault check"<<endl;
        permute(newIn,0,newIn.size()-1, combo,floating, 0);
       //cout<<"combo insert"<<endl;



    // for(int i =0; i<floating.size(); ++i){
    //     posHolder.erase(posHolder.find(floating[i]));
    // }

    int pos = 0;
    for(set<std::string>::iterator it = combo.begin(); it != combo.end(); ++it){
      //cout<<"it: "<<*it<<endl;
       string temp = *it;
       string temp2 = temp;
        findAll(temp, words, dict,pos, temp2);
    }

   

   return words;


    
    

}

// Define any helper functions here
void findAll(const std::string& in, std::set<std::string>& words, const std::set<std::string>& dict, int pos, std::string& temp){
   //string temp = in;
   //cout<<"test"<<endl; 
       if(pos==in.size()){
        return;
    }


   bool dash = false;
    for(unsigned i =0; i<in.size(); i++){
        
        if(in.at(i)=='-'){
            dash = true;
        }   
       
    }
    if(!dash){
        if(dict.find(in)!=dict.end())
        words.insert(in);
    }
   



    if(in[pos]=='-'){
        if(temp[pos]=='-'){
            temp[pos]='a'-1;

        }
        while(temp[pos]<'z'){
            temp[pos]++;
          // cout<<temp<<endl;
            if(dict.find(temp)!=dict.end()){
            
                words.insert(temp);
            }
            findAll(in,words,dict,pos+1,temp);
        }
                    temp[pos] = 'a'-1  ;

    }
    else{
    findAll(in,words,dict,pos+1,temp);

    }
   
   // for(int i =0; i<in.size(); ++i){
//             if(temp[pos]=='-'){
//                 if(temp[pos]=='-'){
//                     temp[pos]='a';
//                 }
//                 else{
//                     temp[pos]++;
//                 }
          
//         }
        
//             findAll(in,words,dict,pos+1,temp);

//             if(in[pos]=='-'){

//                 while(temp[pos]<'z'){
//                     if(temp[pos]!='a'){
//                     ++temp[pos];
//                      if(dict.find(temp)!=dict.end()){
//                        // cout<<"temp: "<<temp<<endl;
//                         words.insert(temp);
//                     }
//                     }
//                     else{
//                      if(dict.find(temp)!=dict.end()){
//                        // cout<<"temp: "<<temp<<endl;
//                         words.insert(temp);
//                     } 
//                     ++temp[pos];

//                     }
                 

//                 }

//             }


//   //  }
 

   
}


void permute(string& in, int start, int end, set<std::string>&combo, const::string& floating, int idx){
    string temp = in;
    int counter=0;
    if(floating.size()==0){
        combo.insert(in);
    }
    if(idx >= floating.size()){
        //cout<<"in: "<<in<<endl;
        return;
    }

    else{

        for(int i = start; i<in.size(); ++i){
           if(temp[i]=='-'){
           // counter++;
            temp[i]=floating[idx];
        

                permute(temp, start,end,combo,floating,idx+1);
                if(temp.size()==in.size() && idx==floating.size()-1){
                //cout<<"permute: "<<temp<<endl;
                    combo.insert(temp);
                }
                temp[i] = '-';
           }
           
        }
    } 
    //cout<<"counter: "<<counter<<endl;
    
}


// -i-- dn
//-id-
//nid-
//-idn
//-i-d