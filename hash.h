#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        unsigned long long w[5] = {0, 0, 0, 0, 0};
        size_t l = k.size();
        size_t chunkCount = (l + 5) / 6;

        for(size_t i = 0; i < chunkCount; i++){
            size_t start;
            if ((l - i * 6) >= 6){
                start = (l - i * 6) - 6;
            }
            else{
                start = 0;
            }
            std::string currBlock = k.substr(start, (l - i * 6) - start);
            int currPow = currBlock.size() - 1;
            unsigned long long store = 0;
            for (size_t j = 0; j < currBlock.size(); j++){
                unsigned long long convertedChar = letterDigitToNumber(currBlock[j]);
                store += convertedChar * static_cast<unsigned long long>(pow(36.0, currPow));
                currPow--;
            }
            w[static_cast<int>(4 - i)] = store;
        }
        unsigned long long output = 0;
        for (int i = 0; i < 5; i++){
            output += static_cast<unsigned long long>(rValues[i]) * w[i];
        }
        return static_cast<HASH_INDEX_T>(output);
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        if (isdigit(letter)){
            return static_cast<HASH_INDEX_T>((letter - '0') + 26);
        }
        letter = tolower(letter);
        return static_cast<HASH_INDEX_T>(letter - 'a');

        // Add code here or delete this helper function if you do not want it
        

    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
