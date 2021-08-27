#include "Card.h"
#define dbgln(x) std::cout << #x << ": " << (x) << std::endl;
//Card::Card(std::string _id) : id{ _id } {
//   //question.push_back("Default Question");
//   // answer.push_back("Default Answer");
//}
//
//Card::Card(std::string _id, std::vector<std::string> _question, std::vector<std::string> _answer) : id{ _id } {
// // need to make deep copies of vectors that are passed in
//   question = _question;
//   answer = _answer;
//}
//
void const Card::print_card() {
   std::cout << "\n---\nID: " << std::endl;
   dbgln(id);

   std::cout << "\n---\nQuestion: " << std::endl;
   for (const auto& ques : question) {
      dbgln(ques);
   }

   std::cout << "\n---\nAnswer: " << std::endl;
   for (const auto& ans : answer) {
      dbgln(ans);
   }
}