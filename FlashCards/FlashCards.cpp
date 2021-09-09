#include <iostream>
#include <conio.h>
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
      user_input = _getch();
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
   cout << "\nHello! Please select an option:" << endl;
   cout << "X:      Start Flash Card Excersizes" << endl;
   cout << "C:      Print All Flash Cards in Current Deck" << endl;
   cout << "F:      Load Different Flash Card Deck " << endl;
   cout << "H:      Program Help (TBI)" << endl;
   cout << "Q:      Exit the Program" << endl;
   return;
}
void cycle_current_deck(Deck flash_card_deck) {
   system("CLS");
   struct exercise_state {
      bool ex_is_active{ true };
      char user_input{};
      int num_cards_held{ 0 };
      int current_card_num{ 0 };

      void print_instructions() { std::cout << "After viewing the id & question please press enter to view the answer." << std::endl; }
      void print_ex_progress(std::map<std::string, std::shared_ptr<Card>> deck, std::map<std::string, std::shared_ptr<Card>> hold_deck) { std::cout << "Card: " << current_card_num << " out of: " << deck.size() << " cards." << " There are " << hold_deck.size() << " cards in the hold deck." << std::endl; }
      void print_key_option_menu() { std::cout << "[Q]: Exit, [0]: Hold Card, [Enter]: Proceed to Next Card" << std::endl; } // maybe implement?
      void print_hold_key_option_menu() { cout << "[Q]: Exit, [Enter]: Proceed to Next Card" << endl; }
      void print_hold_instructions() { std::cout << "Press '0' if you would like to hold this question to be reviewed at the end otherwise press 'enter' to remove it from the deck and show the next card." << std::endl; }
      void print_beg_hold_message() { std::cout << "Beginning hold deck cycle." << std::endl; }
      void print_hold_ex_progress(int current_index, std::map<std::string, std::shared_ptr<Card>> hold_deck) { cout << "Card: " << current_index << " out of: " << hold_deck.size() << " cards." << endl; }
      void print_final_report(std::map<std::string, std::shared_ptr<Card>> deck) { cout << "--- Final report. You reviewed : " << deck.size() << " questions." << " You held: " << num_cards_held << " questions to be reviwed again.\n" << endl; }
      void print_continue_message() { cout << "Press enter to continue" << endl; }
   };

   exercise_state e_state{ true };
   Deck hold_deck{};
   std::cin.ignore(256, '\n'); // clears the cin.get() cache? I have no idea -.- @@@@@@@@@@

   for (const auto& card : flash_card_deck.deck) {
      if (e_state.ex_is_active == true) {
         ++e_state.current_card_num;
         e_state.print_instructions();
         e_state.print_ex_progress(flash_card_deck.deck, hold_deck.deck);
         std::cout << "\n----------------------------------------------------------------" << std::endl;
         card.second->print_id();
         card.second->print_question();
         cin.get(); // This will 'pause' the exercise and allow time to answer the question.


         card.second->print_ans();
         std::cout << "----------------------------------------------------------------\n" << endl;
         e_state.print_hold_instructions();
         e_state.print_key_option_menu();
         e_state.user_input = _getch(); // 'pause' the exercise and wait for user input


         if (e_state.user_input == '0') {
            hold_deck.addCard(*card.second);
            ++e_state.num_cards_held;
         }
         else if (e_state.user_input == 'q' || e_state.user_input == 'Q') {
            e_state.ex_is_active = false;
            break;
         }
         system("CLS");
      }
   }
   if (e_state.ex_is_active == true) {
      e_state.print_final_report(flash_card_deck.deck);
      e_state.print_beg_hold_message();
      cin.get();

      //start hold loop here? -simplified version with no hold
      int card_index{ 0 };

      for (const auto& card : hold_deck.deck) {
         if (e_state.ex_is_active == true) {
            ++card_index;
            e_state.print_instructions();
            e_state.print_hold_ex_progress(card_index, hold_deck.deck);

            std::cout << "\n----------------------------------------------------------------" << std::endl;
            card.second->print_id();
            card.second->print_question();
            cin.get();

            card.second->print_ans();
            std::cout << "----------------------------------------------------------------\n" << endl;
            e_state.print_continue_message();
            e_state.print_hold_key_option_menu();

            e_state.user_input = _getch();
            if (e_state.user_input == 'q' || e_state.user_input == 'Q') {
               e_state.ex_is_active = false;
               break;
            }
            system("CLS");
         }
      }
   }
   cout << "Exiting cycle_current_deck, press enter to continue........." << endl;
   cin.get(); // 'pauses' before returniung to the main menu
   system("CLS");
}