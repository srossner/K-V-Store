#include "fifo_dictionary.h"

static std::list<utility::string_t> m_List;
static std::map<utility::string_t, utility::string_t> m_dictionary;

FIFO_Dictionary::FIFO_Dictionary()
{

}

void FIFO_Dictionary::insert(std::string key, std::string value)
{
    m_dictionary[key] = value;
    m_List.push_back(key);


    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        std::cout << "MAX_NUMBER_OF_ELEMENTS  " << MAX_NUMBER_OF_ELEMENTS << std::endl;

        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }

}

void FIFO_Dictionary::update(std::string key, std::string value)
{
    m_dictionary[key] = value;

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }
}

void FIFO_Dictionary::erase(std::string key)
{
    m_dictionary.erase(key);
    m_List.remove(key);
}

std::string FIFO_Dictionary::get(std::string key)
{
    return m_dictionary[key];
}

bool FIFO_Dictionary::find(std::string key)
{
    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }

    return (m_dictionary.find(key) != m_dictionary.end());
}


field_map FIFO_Dictionary::getAll()
{
    field_map answer;

    for (auto const & p : m_dictionary)
    {
        answer.push_back(make_pair(p.first, web::json::value(p.second)));
    }

    return answer;
}

std::size_t FIFO_Dictionary::getNumberOfElements()
{
    return m_dictionary.size();
}

