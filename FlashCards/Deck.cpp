#include "Deck.h"

void Deck::load_deck(std::string deck_file_name) {
   
   namespace pt = boost::property_tree; // Short alias for this namespace

   pt::ptree root; // Creates a property tree called root
   pt::read_json(deck_file_name, root); // Uses boost library to load JSON file into ptree

   std::cout << "=================Starting Loading Deck=================\n";
   for (pt::ptree::value_type& card : root.get_child("cards"))
   {
      //Loading info from JSON file
      Card new_card{};
      new_card = new_card.load_card(card);
      // Putting info into deck map
      std::shared_ptr<Card> new_card_ptr = std::make_shared<Card>(new_card); // This uses the copy constructor?, can also be moved potentially
      deck.insert(std::pair<std::string, std::shared_ptr<Card>>(new_card_ptr->id, new_card_ptr));
   }
   std::cout << "=================Finished Loading Deck=================\n";
}

void Deck::print_deck() {
   for (auto& card : deck) {
      card.second->print_card();
   }
}