/*
MIT License

Copyright (c) 2018 Paul Salvador Inventado

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "catch.hpp"
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>

using namespace std;

string couttest(string progName, string input)
{
  FILE *fp = popen(("echo \""+ input +"\" | ./" + progName).c_str(), "r");
  char buf[1024];
  string output = "";
  while (fgets(buf, 1024, fp)) {
    output += buf;
  }
  pclose(fp);  
  return output;
}

string to_string_double(double val, const int prec = 2)
{
    std::ostringstream out;
    out << fixed << setprecision(prec) << val;
    return out.str();
}

TEST_CASE ("Time calculator", "[timecalc]")
{
  string output = "";
  string expected= "";
  srand (time(NULL));
  int randNum=0;
  string randNumStr="";
  string val="";

  SECTION("Days")
  {
    for(int i = 0; i < 10; i++)
    {
      
      randNum = rand() % 2147397247 + 86400;
      randNumStr = to_string(randNum);
      val = to_string(randNum / 86400);
      output  = couttest("timecalc", randNumStr);
      expected = "Please enter the number of seconds to convert: " + randNumStr + " seconds is around " + val + " days";
        CHECK (output == expected);      
    }
  }
  SECTION("Hours")
  {
    for(int i = 0; i < 10; i++)
    {     
      randNum = rand() % 82800 + 3600;
      randNumStr = to_string(randNum);
      val = to_string(randNum / 3600);
      output  = couttest("timecalc", randNumStr);
      expected = "Please enter the number of seconds to convert: " + randNumStr + " seconds is around " + val + " hours";
        CHECK (output == expected);      
    }    
  }
  SECTION("Minutes")
  {
    for(int i = 0; i < 10; i++)
    {
      randNum = rand() % 3540 + 60;
      randNumStr = to_string(randNum);
      val = to_string(randNum / 60);
      output  = couttest("timecalc", randNumStr);
      expected = "Please enter the number of seconds to convert: " + randNumStr + " seconds is around " + val + " minutes";
        CHECK (output == expected);      
    } 
  }
  SECTION("Seconds")
  {
    for(int i = 0; i < 10; i++)
    {
      randNum = rand() % 60;
      randNumStr = to_string(randNum);
      val = to_string(randNum);
      output  = couttest("timecalc", randNumStr);
      expected = "Please enter the number of seconds to convert: You inputted " + randNumStr + " seconds";
        CHECK (output == expected);      
    } 
  }
}

TEST_CASE ("Minimum/Maximum", "[minmax]")
{
  string output = "";
  string expected = "";
  srand (time(NULL));

  SECTION ("Random pair test")
  {
    int randNum1, 
        randNum2;
    string  larger,
            input;
    for(int i = 0; i < 10; i++){
      randNum1 =  rand() % 2147483647;
      randNum2 =  rand() % 2147483647;
      larger = to_string(randNum1 > randNum2 ? randNum1 : randNum2);
      input = to_string(randNum1) + " " + to_string(randNum2);
      output = couttest("minmax", input);
      expected = "Please enter the first number: Please enter the second number: The larger number is: " + larger;
      CHECK( output == expected);
    }
    
  }
}

TEST_CASE("Geometry Calculator", "[geomcalc]")
{
  string output ="";
  string expected = "Geometry calculator\n1. Calculate the Area of a Circle\n";
         expected+= "2. Calculate the Area of a Rectangle\n3. Calculate the Area of a Triangle\n";
         expected+= "4. Quit\nEnter your choice (1-4): ";
  srand (time(NULL));
  const double PI = 3.14159;
  
  SECTION ("Circle")
  {
    for(int i = 0; i < 10; i++)
    {
      double randNum =  static_cast<double>(rand())/65535;
      string randNumStr = to_string_double(randNum);
      randNum = atof(randNumStr.c_str());
      double areaCirc = PI * randNum * randNum;
      output = couttest("geomcalc", "1 " + randNumStr);

      string expectedTemp = expected + "What is the radius of the circle? The area of the circle is " + to_string_double(areaCirc);
      CHECK(output == expectedTemp); 
    }
  }
  SECTION ("Rectangle")
  {
    for(int i = 0; i < 10; i++)
    {
      double randNum1 =  static_cast<double>(rand())/65535;
      double randNum2 =  static_cast<double>(rand())/65535;
      string randNumStr1 = to_string_double(randNum1);
      string randNumStr2 = to_string_double(randNum2);
      randNum1 = atof(randNumStr1.c_str());
      randNum2 = atof(randNumStr2.c_str());
      double areaRect = randNum1 * randNum2;
      output = couttest("geomcalc", "2 " + randNumStr1 + " " + randNumStr2);

      string expectedTemp = expected + "What is the length of the rectangle? What is the width of the rectangle? The area of the rectangle is " + to_string_double(areaRect);
      CHECK(output == expectedTemp); 
    }
  }
  SECTION ("Triangle")
  {
    for(int i = 0; i < 10; i++)
    {
      double randNum1 =  static_cast<double>(rand())/65535;
      double randNum2 =  static_cast<double>(rand())/65535;
      string randNumStr1 = to_string_double(randNum1);
      string randNumStr2 = to_string_double(randNum2);
      randNum1 = atof(randNumStr1.c_str());
      randNum2 = atof(randNumStr2.c_str());
      double areaTri = 0.5 * randNum1 * randNum2;
      output = couttest("geomcalc", "3 " + randNumStr1 + " " + randNumStr2);

      string expectedTemp = expected + "What is the base of the triangle? What is the height of the triangle? The area of the triangle is " + to_string_double(areaTri);
      CHECK(output == expectedTemp); 
    }
  }
  SECTION ("Goodbye")
  {
    output = couttest("geomcalc", "4");
    string expectedTemp = expected + "Good bye!";
    CHECK(output == expectedTemp);
  }
  SECTION ("Invalid input")
  {
    for(int i = 0; i < 10; i++)
    {
      char randChar = rand()%74 + 53;    
      output = couttest("geomcalc", to_string(randChar));
      string expectedTemp = expected + "Invalid input. Please rerun the program.";
      CHECK(output == expectedTemp);
    }
  }

}

TEST_CASE ("Aggregate functions", "[aggreg]")
{
  string output = "";
  string expected = "Please enter a series of integers. Input -99 to indicate the end of the series.\n";
  srand (time(NULL));

  SECTION("Random inputs")
  {
    for(int i = 0; i < 10; i++)
    {
      int randCount = rand() % 50;
      int sum = 0;
      string randNumSeries = "";
      for(int count = 0; count < randCount; count++)
      {
        int randNum = rand() % 2147483647;  
        randNumSeries+= to_string(randNum) + " ";
        sum += randNum;
      }
      randNumSeries+= "-99";
      output = couttest("aggreg", randNumSeries);
      string expectedTemp = expected + "Series count: " + to_string(randCount) + "\n";
      expectedTemp += "Series sum: " + to_string(sum);
      CHECK (output == expectedTemp);
    }
  }
}

TEST_CASE ("Enhanced Aggregate functions", "[enaggreg]")
{
  string output = "";
  string expected = "Please enter a series of integers. Input -99 to indicate the end of the series.\n";
  srand (time(NULL));

  SECTION("Random inputs")
  {
    for(int i = 0; i < 10; i++)
    {
      int randCount = rand() % 50 + 2;
      int sum = 0;
      int min = -1;
      int max = -1;
      string randNumSeries = "";
      for(int count = 1; count < randCount; count++)
      {
        int randNum = rand() % 10000;  
        randNumSeries+= to_string(randNum) + " ";
        sum += randNum;
        if(min == -1 || min > randNum)
          min = randNum;
        if(max == -1 || max < randNum)
          max = randNum;
      }
      double average = sum * 1.0 / (randCount-1); // compenstate for loop start at 1
      randNumSeries+= "-99";
      output = couttest("enaggreg", randNumSeries);
      string expectedTemp = expected + "Series count: " + to_string(randCount-1) + "\n"; // compenstate for loop start at 1
      expectedTemp += "Series sum: " + to_string(sum) + "\n";
      expectedTemp += "Series min: " + to_string(min) + "\n";
      expectedTemp += "Series max: " + to_string(max) + "\n";
      expectedTemp += "Series average: " + to_string_double(average);
      CHECK (output == expectedTemp);
    }
  }

  SECTION ("Zero inputs")
  {
    output = couttest("enaggreg", "-99");
    string expectedTemp = expected + "Series count: 0\n";
    expectedTemp += "Series sum: 0\n";
    expectedTemp += "Series min: NA\n";
    expectedTemp += "Series max: NA\n";
    expectedTemp += "Series average: NA";
    CHECK (output == expectedTemp);
  }
}
/*TEST_CASE ("Sample problem")
{
  string output ="";
  SECTION ("Input 2")
  {
    output = couttest("even", "2");
    CHECK (output == "Enter a number: 2 is even");
  }
  SECTION ("Input 7")
  {
    output = couttest("even", "7");
    CHECK (output == "Enter a number: 7 is not even");
  }
  SECTION ("Input -10")
  {
    output = couttest("even", "-10");
    CHECK (output == "Enter a number: -10 is even");
  }
}

TEST_CASE ("Problem 1 Unit test")
{
  string output = "";
  SECTION ("Input 5, 1")
  {
    output = couttest("prob1", "5 1");
    CHECK( output == "Please enter the first number: Please enter the second number: The larger number is: 5" );
  }
  SECTION ("Input 1, 5")
  {
    output = couttest("prob1", "1 5");
    CHECK( output == "Please enter the first number: Please enter the second number: The larger number is: 5" );
  }
  SECTION ("Input -1, 10")
  {
    output = couttest("prob1", "-1 10");
    REQUIRE( output == "Please enter the first number: Please enter the second number: The larger number is: 10" );
  }
  SECTION ("Input -5, -1")
  {
    output = couttest("prob1", "-5 -1");
    CHECK( output == "Please enter the first number: Please enter the second number: The larger number is: -1" );
  }
}

TEST_CASE ("Problem 2 Unit test")
{
  string output = "";
  SECTION ("Input 2008")
  {
    output = couttest("prob2", "2008");
    CHECK(output == "Enter a year: In 2008 February has 29 days.");
  }
  SECTION ("Input 2009")
  {
    output = couttest("prob2", "2009");
    CHECK(output == "Enter a year: In 2009 February has 28 days.");
  }
  SECTION ("Input 2000")
  {
    output = couttest("prob2", "2000");
    CHECK(output == "Enter a year: In 2000 February has 29 days.");
  }
  SECTION ("Input 2100")
  {
    output = couttest("prob2", "2100");
    CHECK(output == "Enter a year: In 2100 February has 28 days.");
  }
}

TEST_CASE("Problem 3 Unit test")
{
  string output ="";
  string expected = "Geometry calculator\n1. Calculate the Area of a Circle\n";
         expected+= "2. Calculate the Area of a Rectangle\n3. Calculate the Area of a Triangle\n";
         expected+= "4. Quit\nEnter your choice (1-4):";

  SECTION ("Input 1 5")
  {
    output = couttest("prob3", "1 5");
    expected += "What is the radius of the circle? The area of the circle is 15.7076";
    CHECK(output == expected);
  }
  SECTION ("Input 2 3 4")
  {
    output = couttest("prob3", "2 3 4");
    expected += "What is the length of the rectangle? What is the width of the rectangle? The area of the rectangle is 12";
    CHECK(output == expected);
  }
  SECTION ("Input 3 5 3")
  {
    output = couttest("prob3", "3 5 3");
    expected += "What is the base of the triangle? What is the height of the triangle? The area of the triangle is 7.5";
    CHECK(output == expected);
  }
  SECTION ("Input 4")
  {
    output = couttest("prob3", "4");
    expected += "Good bye!";
    CHECK(output == expected);
  }
  SECTION ("Input a")
  {
    output = couttest("prob3", "a");
    expected += "Invalid input. Please rerun the program.";
    CHECK(output == expected);
  }
}
*/