#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "Deck.h"
#include "Card.h"


void print_option_menu();
void cycle_current_deck(Deck flash_card_deck);

// https://www.boost.org/doc/libs/1_63_0/doc/html/property_tree/reference.html#header.boost.property_tree.json_parser_hpp
// http://www.cochoy.fr/boost-property-tree/ 

using namespace std;
namespace pt = boost::property_tree; // Short alias for this namespace

#define dbgln(x) cout << #x << ": " << (x) << endl;
#define dbg(x) cout << #x << ": " << (x) << "   ";

// Purpose: Main
int main()
{
   std::string default_file_name{ "defaultcards.json" };

   std::cout << "Welcome! Please type the name of the Deck you would like to access. (defaultcards.json is run by default).\n";
   std::string file_response{};
   std::cin >> file_response;
   if (true) { file_response = default_file_name; }; // THIS IS WHERE YOU CAN ADD OTHER FILE NAMES EVENTUALLY @@@@@
   Deck flash_card_deck{}; //YOU CANNOT DO THIS: Deck flash_card_deck(); (this is an example of "c++'s most confusing parse")
   try
   {
      flash_card_deck.load_deck(file_response);
      std::cout << "Cards loaded successfully\n";
   }
   catch (const std::exception& e)
   { // caught by reference to base
      std::cout << "Error loading cards: " << e.what() << "\n";
      cin.ignore();
      exit(1); // Exit the program now with an non-zero exit code, indicating a problem
   }

   char user_input{  };

   while (!(user_input == 'q' || user_input == 'Q')) {
      print_option_menu();
      cin >> user_input;
      switch (user_input) {

      case 'X':
      case 'x':
         if (flash_card_deck.empty() == true) { cout << "Deck is empty\n"; }
         else cycle_current_deck(flash_card_deck);
         break;
      case 'C':
      case 'c':
         cout << "------------------------------------------\nPrinting All Flash Cards in Deck\n";
         flash_card_deck.print_deck();
         cout << "------------------------------------------\nPrinted All Flash Cards in Deck\n";
         break;

      case 'F':
      case 'f':
         cout << "Loading Flash Card Deck\n";
         break;

      case 'H':
      case 'h':
         system("CLS"); // this is not a 'portable' solution @@@@ SHOULD I USE THIS?
         cout << "Help Selected!\n";
         break;

      case 'Q':
      case 'q':
         cout << "Exiting Program. Thank you!\n";
         break;
      }
   }
}
void print_option_menu() {
   cout << "Hello! Please select an option:" << endl;
   cout << "X:      Start Flash Card Excersizes" << endl;
   cout << "C:      Print All Flash Cards in Current Deck" << endl;
   cout << "F:      Load Different Flash Card Deck " << endl;
   cout << "H:      Program Help (TBI)" << endl;
   cout << "Q:      Exit the Program" << endl;
   return;
}
void cycle_current_deck(Deck flash_card_deck) {
   system("CLS");
   char user_input{};
   for (const auto& card : flash_card_deck.deck) {
      std::cout << "Please indicate if your provided answer to the question was Correct or Not:" << std::endl;
      std::cout << "Press 0 if Correct, 1 if Incorrect\n\n\n" << std::endl;
      cin.get() >> user_input; // this is getting ignored??
      card.second->print_id();
      card.second->print_question();

      cin.get() >> user_input;
      card.second->print_ans();
      cin.get() >> user_input;
      system("CLS");
   }
   cout << "Exiting cycle_current_deck" << endl;
}