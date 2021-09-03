#pragma once
#include <map>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Card.h"
class Deck
{
public:
   std::map<std::string, Card> deck; // Use make_shared<> to allocate memory

   void load_deck(std::string deck_file_name); //bool indicates if it successfully loaded deck
   void print_deck();
};

