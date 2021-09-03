#pragma once
#include <vector>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree; // Short alias for this namespace

struct Card {
   std::string id;
   std::vector <std::string> question;
   std::vector <std::string> answer;

   //Card(pt::ptree::value_type& card);
   //Card();
   void const print_card();
   Card load_card(pt::ptree::value_type& card);
};