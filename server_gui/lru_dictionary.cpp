#include "lru_dictionary.h"

static std::list<utility::string_t> m_List;
static std::map<utility::string_t, utility::string_t> m_dictionary;

LRU_Dictionary::LRU_Dictionary()
{

}

void LRU_Dictionary::insert(std::string key, std::string value)
{
    m_dictionary[key] = value;
    m_List.push_back(key);

    std::cout << "m_List.size()  " << m_List.size() << std::endl;

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {

        std::cout << "MAX_NUMBER_OF_ELEMENTS  " << MAX_NUMBER_OF_ELEMENTS << std::endl;

        m_dictionary.erase(m_List.front());

        std::cout << "m_List.front()  " << m_List.front() << std::endl;


        m_List.pop_front();
    }
}


void LRU_Dictionary::update(std::string key, std::string value)
{
    m_dictionary[key] = value;

    m_List.remove(key);

    m_List.push_back(key);

    std::cout << "m_List.size()  " << m_List.size() << std::endl;

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        std::cout << "MAX_NUMBER_OF_ELEMENTS  " << MAX_NUMBER_OF_ELEMENTS << std::endl;

        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }
}

void LRU_Dictionary::erase(std::string key)
{
    m_dictionary.erase(key);
}

std::string LRU_Dictionary::get(std::string key)
{
    m_List.remove(key);

    m_List.push_back(key);

    return m_dictionary[key];
}

bool LRU_Dictionary::find(std::string key)
{

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        std::cout << "MAX_NUMBER_OF_ELEMENTS  " << MAX_NUMBER_OF_ELEMENTS << std::endl;

        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }

    if(m_dictionary.find(key) != m_dictionary.end())
    {

        m_List.remove(key);

        m_List.push_back(key);

        return true;
    }

    return false;
}


field_map LRU_Dictionary::getAll()
{
    field_map answer;

    for (auto const & p : m_dictionary)
    {
        answer.push_back(make_pair(p.first, web::json::value(p.second)));
    }

    return answer;
}

std::size_t LRU_Dictionary::getNumberOfElements()
{
    return m_dictionary.size();
}

