#include "Deck.h"

void Deck::load_deck(std::string deck_file_name) {
   
   namespace pt = boost::property_tree; // Short alias for this namespace

   pt::ptree root; // Creates a property tree called root
   pt::read_json(deck_file_name, root); // Uses boost library to load JSON file into ptree

   std::cout << "=================Starting Loading Deck=================\n";
   for (pt::ptree::value_type& card : root.get_child("cards"))
   {
      Card new_card{ }; // Uses default constructor
      std::string new_id{ card.second.get<std::string>("id", "<no id>") };
      new_card.id = new_id;

      // Print out the lines of the question (for each string variable in the JSON)
      for (pt::ptree::value_type& question_elem : card.second.get_child("question"))
      {
         // FOR loop goes through each string in the array of strings (need to push each one on the vector)
         const auto& question_line{ question_elem.second.data() };
         new_card.question.push_back(question_line);
      }

      // Print out the lines of the answer (for each string variable in the JSON)
      for (pt::ptree::value_type& answer_elem : card.second.get_child("answer"))
      {
         // FOR loop goes through each string in the array of strings (need to push each one on the vector)
         const auto& answer_line{ answer_elem.second.data() };
         new_card.answer.push_back(answer_line);
      }
      deck.insert(std::pair<std::string, Card>(new_card.id, new_card));
   }
   std::cout << "=================Finished Loading Deck=================\n";
}

void Deck::print_deck() {
   for (auto& card : deck) {
      card.second.print_card();
   }
}