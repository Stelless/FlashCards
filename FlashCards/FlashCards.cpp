#include <iostream>
#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Deck.h"
#include "Card.h"


// https://www.boost.org/doc/libs/1_63_0/doc/html/property_tree/reference.html#header.boost.property_tree.json_parser_hpp
// http://www.cochoy.fr/boost-property-tree/ 

using namespace std;
namespace pt = boost::property_tree; // Short alias for this namespace

#define dbgln(x) cout << #x << ": " << (x) << endl;
#define dbg(x) cout << #x << ": " << (x) << "   ";

std::string default_file_name{ "defaultcards.json" };

// Purpose: Main
int main()
{
   Deck flash_card_deck{}; //YOU CANNOT DO THIS Deck flash_card_deck(); (this is an example of "c++'s most confusing parse")
   try
   {
      flash_card_deck.load_deck(default_file_name);
      std::cout << "Cards loaded successfully\n";
   }
   catch (const std::exception& e)
   { // caught by reference to base
      std::cout << "Error loading cards: " << e.what() << "\n";
      cin.ignore();
      exit(1); // Exit the program now with an non-zero exit code, indicating a problem
   }

   flash_card_deck.print_deck();
}
