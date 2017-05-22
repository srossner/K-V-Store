#include "all_dictionary.h"


static std::map<utility::string_t, utility::string_t> m_dictionary;

All_Dictionary::All_Dictionary()
{

}

void All_Dictionary::insert(std::string key, std::string value)
{
    m_dictionary[key] = value;
}

void All_Dictionary::update(std::string key, std::string value)
{
    m_dictionary[key] = value;
}

void All_Dictionary::erase(std::string key)
{
    m_dictionary.erase(key);
}

std::string All_Dictionary::get(std::string key)
{
    return m_dictionary[key];
}

bool All_Dictionary::find(std::string key)
{
    return (m_dictionary.find(key) != m_dictionary.end());
}


field_map All_Dictionary::getAll()
{
    field_map answer;

    for (auto const & p : m_dictionary)
    {
        answer.push_back(make_pair(p.first, web::json::value(p.second)));
    }

    return answer;
}

std::size_t All_Dictionary::getNumberOfElements()
{
    return m_dictionary.size();
}

