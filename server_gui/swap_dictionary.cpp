#include "swap_dictionary.h"

static std::list<std::string> m_List;
static std::map<std::string, std::string> m_dictionary;

Swap_Dictionary::Swap_Dictionary()
{
    const int dir_err = system("mkdir swap_K_V_Server");
    if (-1 == dir_err)
    {
        std::cout << "Error creating directory swap_K_V_Server \n";
        exit(1);
    }
}

Swap_Dictionary::~Swap_Dictionary()
{
    const int dir_err = system("rm -r swap_K_V_Server");
    if (-1 == dir_err)
    {
        std::cout << ("Error deleting directory swap_K_V_Server \n");
    }
}

void Swap_Dictionary::insert(std::string key, std::string value)
{
    m_dictionary[key] = value;
    m_List.push_back(key);

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        std::ofstream file;
        file.open("./swap_K_V_Server/" + m_List.front());
        std::string str = m_dictionary[m_List.front()];
        file << str;
        file.close();

        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }
}

void Swap_Dictionary::update(std::string key, std::string value)
{
    m_dictionary[key] = value;
    m_List.remove(key);
    m_List.push_back(key);

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        std::ofstream file;
        file.open( "./swap_K_V_Server/" + m_List.front() );
        std::string str = m_dictionary[m_List.front()];
        file << str.c_str();
        file.close();

        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }
}

void Swap_Dictionary::erase(std::string key)
{
    m_dictionary.erase(key);
    m_List.remove(key);
}

std::string Swap_Dictionary::get(std::string key)
{
    m_List.remove(key);
    m_List.push_back(key);

    return m_dictionary[key];
}

bool Swap_Dictionary::find(std::string key)
{

    while ( m_List.size() > MAX_NUMBER_OF_ELEMENTS)
    {
        std::ofstream file;
        file.open( "./swap_K_V_Server/" + m_List.front() );
        file << m_dictionary[m_List.front()];
        file.close();
        m_dictionary.erase(m_List.front());
        m_List.pop_front();
    }

    if(m_dictionary.find(key) != m_dictionary.end())
    {
        m_List.remove(key);
        m_List.push_back(key);
        return true;
    }else{

        std::ifstream file("./swap_K_V_Server/" + key);
        if(file)
        {
            std::string str = "";
            std::string line = "";

            while ( std::getline(file,line) )
            {
                str = str + line + '\n';
            }
            file.close();

            insert(key, line);

            line = "rm ./swap_K_V_Server/" + key;


            const int dir_err = system( line.c_str());
            if (-1 == dir_err)
            {
                std::cout << "Error could not delete file swap_K_V_Server/" << key <<  "\n";
                exit(1);
            }


            return true;
        }
    }

    return false;
}

field_map Swap_Dictionary::getAll()
{
    field_map answer;

    for (auto const & p : m_dictionary)
    {
        answer.push_back(make_pair(p.first, web::json::value(p.second)));
    }
    return answer;
}

std::size_t Swap_Dictionary::getNumberOfElements()
{
    return m_dictionary.size();
}
