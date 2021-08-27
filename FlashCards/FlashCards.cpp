#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// https://www.boost.org/doc/libs/1_63_0/doc/html/property_tree/reference.html#header.boost.property_tree.json_parser_hpp
// http://www.cochoy.fr/boost-property-tree/ 

using namespace std;
namespace pt = boost::property_tree; // Short alias for this namespace

#define dbgln(x) cout << #x << ": " << (x) << endl;
#define dbg(x) cout << #x << ": " << (x) << "   ";

std::string default_file_name{ "defaultcards.json" };

// Purpose: Load the flash cards into memory
void loadCards()
{
   // Create a root
   pt::ptree root;

   // Load the json file in this ptree
   pt::read_json(default_file_name, root);

   // Load each card
   for (pt::ptree::value_type& card : root.get_child("cards"))
   {
      cout << "==================================" << endl;
      string id{ card.second.get<std::string>("id", "<no id>") };
      dbgln(id);

      // Print out the lines of the question
      for (pt::ptree::value_type& question_elem : card.second.get_child("question"))
      {
         const auto& question_line{ question_elem.second.data() };
         dbgln(question_line);
      }

      // Print out the lines of the answer 
      for (pt::ptree::value_type& answer_elem : card.second.get_child("answer"))
      {
         const auto& answer_line{ answer_elem.second.data() };
         dbgln(answer_line);
      }

      string answer{ card.second.get<std::string>("answer", "<no answer>") };
      dbgln(answer);
   }
}

// Purpose: Main
int main()
{
   try
   {
      loadCards();
   }

   catch (const std::exception& e)
   { // caught by reference to base
      std::cout << "Error loading cards: " << e.what() << "\n";
      cin.ignore();
      exit(1); // Exit the program now with an non-zero exit code, indicating a problem
   }
}
