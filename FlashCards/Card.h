#pragma once
#include <vector>
#include <iostream>

struct Card {
   std::string id;
   std::vector <std::string> question;
   std::vector <std::string> answer;

   void const print_card();
};