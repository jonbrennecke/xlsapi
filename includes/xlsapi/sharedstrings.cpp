#include "sharedstrings.h"
#include "../sys/sys.hpp"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>

// TODO simple hack to fix inclusion error of sys namespace
namespace sys {
    std::string terminal(std::string command);
}

/* Constructor */
SharedStrings::SharedStrings(std::string path)
{
	// unzip the file 'xl/sharedString.xml' from the xlsx zip archive at 'path' 
    std::string result = sys::terminal("unzip -p " + path + " xl/sharedStrings.xml");
    std::vector<char> sstrings_xml(result.begin(), result.end());
    sstrings_xml.push_back('\0');

    // we use the rapidxml library to construct a DOM from the xml file
    rapidxml::xml_document<> doc;
    doc.parse<rapidxml::parse_declaration_node | rapidxml::parse_no_data_nodes>(&sstrings_xml[0]);

    rapidxml::xml_node<>* sst = doc.first_node("sst");
    rapidxml::xml_node<>* si = sst->first_node("si");

    // loop through the list of strings
    while (si != NULL)
    {
    	rapidxml::xml_node<>* t = si->first_node("t");
    	this->strings.push_back(std::string(t->value()));
        si = si->next_sibling("si");
    }
}

/* return the string at index */
std::string SharedStrings::index(int i)
{
    // return "here";
	return this->strings[i];
}