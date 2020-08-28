#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() 
#include "catch.hpp"
#include <vector>
#include <map>
#include <string>


using namespace std;



/*
 *
 *      sumByStride FUNCTION
 *
 *      given a vector of numbers and a stride (to iterate the vector)
 *      this function will add those values in the vector considering the next index per stride
 *
 *
 *
*/
int sumByStride( const vector<int> &v, int stride ) {

    // iterator to run a for loop every X values
    vector <int> ::const_iterator iter = v.begin();


    // addValues to receive values from iterator per stride
    int addValues = 0;
    for(iter = v.begin(); iter < v.end(); advance(iter,stride)){

                addValues += *iter;
    }


    return addValues;
}



/*
 *
 *
 *      histogram FUNCTION
 *
 *      given a vector of numbers of words this function verify the frequency, then append the
 *      words with frequency (based on frequency/ values order) from greatest to less frequent
 *      Example: [A:3][B:2][Z:1][T:1][L:1]
 *
 *
 */

string histogram( const vector<string> &v) {

    // st will get the final appended string after verified frequencies and ordered based on values
    string st = "";


    // countKeys will get keys and their frequency from vector v
    map <string,int> countKeys;

    for(int i = 0 ; i < v.size(); i++){
        countKeys[v[i]] += 1;
    }

    // creating a vector of keys (without repetition) to be used in the ordering
    vector <string> receiveKey;
    for(auto i: countKeys){
        receiveKey.push_back(i.first);
    }

    // PROCESS
    // 1. save the keys and values in two different vectors with same index
    // 2. sort numbers and swap numbers and keys based on numbers using bubble sort

    vector <string> key;
    vector <int> value;

    // tempValue and tempKey will receive value as appear
    // to be passed to the key and value vectors for pushback
    int tempValue;
    string tempKey;

    // 1. transfer from map to vectors keys and values
    for(int i=0; i<countKeys.size(); i++){

            tempKey = receiveKey[i];
            tempValue = countKeys[receiveKey[i]];

            key.push_back(tempKey);
            value.push_back(tempValue);
    }

    // 2. sort keys and values using bubble sort, based on values from greatest to the smallest
    bool swapped;
    do{
        swapped = false;
        for(int i = 0; i < (value.size()-1); i++){
            if(value[i] < value[i+1]){
                swap(key[i], key[i+1]);
                swap(value[i], value[i+1]);
                swapped = true;
            }
        }
    }while(swapped);

    // appending keys and values to st variable
    for(int i=0; i<countKeys.size(); i++){
        st = st + "[" + key[i] + ":" + to_string(value[i]) + "]";
    }

    return st;
}


TEST_CASE( "Testing the sumByStride() function", "[sumByStride]" ) {
    REQUIRE( sumByStride(vector<int> {10,20,30,40,50},2)  == 90);
    REQUIRE( sumByStride(vector<int> {10,20,30,40,50},3)  == 50);
    REQUIRE( sumByStride(vector<int> {10,40,30,20,40},3)  == 30);
    REQUIRE( sumByStride(vector<int> {10,20,30,40,50,10,20,30,40,50},3)  == 120);
}


TEST_CASE( "Testing the histogram() function", "[histogram]" ) {
    string tmp = histogram(vector<string> {"foca", "leon", "zorra", "foca", "perro", "perro", "perro"});
    REQUIRE( (tmp == "[perro:3][foca:2][zorra:1][leon:1]" ||
              tmp == "[perro:3][foca:2][leon:1][zorra:1]") );

    string granja = histogram(vector<string> {"caballo", "dinosaurio", "cocodrilo", "ballena", "dinosaurio", "caballo", "caballo", "perro"});
    REQUIRE( (granja == "[caballo:3][dinosaurio:2][ballena:1][perro:1][cocodrilo:1]" ||
            granja == "[caballo:3][dinosaurio:2][cocodrilo:1][ballena:1][perro:1]" ||
            granja == "[caballo:3][dinosaurio:2][cocodrilo:1][perro:1][ballena:1]" ||
            granja == "[caballo:3][dinosaurio:2][ballena:1][cocodrilo:1][perro:1]" ||
            granja == "[caballo:3][dinosaurio:2][perro:1][cocodrilo:1][ballena:1]" ||
            granja == "[caballo:3][dinosaurio:2][perro:1][ballena:1][cocodrilo:1]") );
}
