#include "Card.h"
#define dbgln(x) std::cout << #x << ": " << (x) << std::endl;

void const Card::print_card() {

   std::cout << "\n-----------\n";
   std::cout << "ID: ";
   dbgln(id);

   std::cout << "Question: ";
   for (const auto& ques : question) {
      dbgln(ques);
   }

   std::cout << "Answer: ";
   for (const auto& ans : answer) {
      dbgln(ans);
   }
}