#include <iostream>
#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Card.h"


// https://www.boost.org/doc/libs/1_63_0/doc/html/property_tree/reference.html#header.boost.property_tree.json_parser_hpp
// http://www.cochoy.fr/boost-property-tree/ 

using namespace std;
namespace pt = boost::property_tree; // Short alias for this namespace

#define dbgln(x) cout << #x << ": " << (x) << endl;
#define dbg(x) cout << #x << ": " << (x) << "   ";

std::string default_file_name{ "defaultcards.json" };

// Purpose: Load the flash cards into memory
void loadCards(map<std::string, Card>& deck)
{
   /*
   Some reading on Boost Property Trees -  https://www.boost.org/doc/libs/1_41_0/doc/html/property_tree.html
   */

   // Create a root
   pt::ptree root;

   // Load the json file in this ptree
   pt::read_json(default_file_name, root);

   // Load each card
   for (pt::ptree::value_type& card : root.get_child("cards"))
   {
      Card new_card{ }; // Uses default constructor
      cout << "==================================" << endl;
      std::string new_id{ card.second.get<std::string>("id", "<no id>") };
      new_card.id = new_id;
      //dbgln(new_card.get_id());

      // Print out the lines of the question (for each string variable in the JSON)
      for (pt::ptree::value_type& question_elem : card.second.get_child("question"))
      {
         // FOR loop goes through each string in the array of strings (need to push each one on the vector)
         const auto& question_line{ question_elem.second.data() };
         new_card.question.push_back(question_line);
         //dbgln(new_card.question.back());
      }

      // Print out the lines of the answer (for each string variable in the JSON)
      for (pt::ptree::value_type& answer_elem : card.second.get_child("answer"))
      {
         // FOR loop goes through each string in the array of strings (need to push each one on the vector)
         const auto& answer_line{ answer_elem.second.data() };
         new_card.answer.push_back(answer_line);
         //dbgln(new_card.answer.back());
      }
      //deck.emplace(new_id, new_card.question, new_card.answer);
      string answer{ card.second.get<std::string>("answer", "<no answer>") };
      //dbgln(answer);
      new_card.print_card();
      deck.insert(std::pair<std::string, Card>(new_id, new_card));
   }
}

// Purpose: Main
int main()
{

   std::map<std::string, Card> deck;
   try
   {
      loadCards(deck);
   }

   catch (const std::exception& e)
   { // caught by reference to base
      std::cout << "Error loading cards: " << e.what() << "\n";
      cin.ignore();
      exit(1); // Exit the program now with an non-zero exit code, indicating a problem
   }
}
