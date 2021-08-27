#pragma once
#include <vector>
#include <iostream>

struct Card {
   std::string id;
   std::vector <std::string> question;
   std::vector <std::string> answer;

   void const print_card();
};

//class Card
//{
//   // All cards have an ID, Question, Answer
//private:
//   std::string id;
//public:
//
//   std::vector<std::string> question; // Each string is a line of the question
//   std::vector<std::string> answer; // Each string is a line of the answer
//
//   Card(std::string _id); // Default constructor
//   Card(std::string _id, std::vector<std::string> _question, std::vector<std::string> _answer); // Constructor
//   ~Card() {}; // Destructor (MAKE VIRTUAL IF USING INHERITANCE).
//
//   void const print_card();
//
//   inline void set_id(const std::string new_id) {id = new_id;};
//   inline std::string const get_id() { return id; };
//
//};
//
