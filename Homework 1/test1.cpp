//
//  test1.cpp
//  CS 32 Project 1
//
//  Created by Stephen Chu on 4/12/20.
//  Copyright © 2020 Steven Chu. All rights reserved.
//

    #include "newSet.h"
     #include <string>
     #include <iostream>
     #include <cassert>
     using namespace std;

     void test()
     {
         Set ss;
         assert(ss.insert("roti"));
         assert(ss.insert("pita"));
         assert(ss.size() == 2);
         assert(ss.contains("pita"));
         ItemType x = "laobing";
         assert(ss.get(0, x)  &&  x == "pita");
         assert(ss.get(1, x)  &&  x == "roti");
     }

     int main()
     {
         test();
         cout << "Passed all tests" << endl;
     }
