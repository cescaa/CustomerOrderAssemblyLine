
#include <iostream>
#include <fstream>
#include <string>
#include "Utilities.h"

namespace sdds
{
  char Utilities::m_delimiter = ',';

  std::string Utilities::removeSpaces(std::string &str)
  {
    if (str.length() > 0)
    {
      size_t sIdx = str.find_first_not_of(" ");
      size_t eIdx = str.find_last_not_of(" ");
      str = str.substr(sIdx, eIdx - sIdx + 1);
    }
    return str;
  }

  void Utilities::setFieldWidth(size_t newWidth)
  {
    m_widthField = newWidth;
  }

  size_t Utilities::getFieldWidth() const
  {
    return m_widthField;
  }

  std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
  {
    std::string extToken = "";

    more = false;
    if (next_pos < static_cast<size_t>(str.length()))
    {

      size_t deliPos = str.find(m_delimiter, next_pos);

      if (deliPos != std::string::npos)
      {
        if (deliPos == next_pos)
        {
          throw std::exception();
        }
        else
        {
          extToken = str.substr(next_pos, deliPos - next_pos);
          extToken = removeSpaces(extToken);
          more = true;
          next_pos = deliPos + 1;
        }
      }
      else
      {
        more = false;
        extToken = str.substr(next_pos);
      }
    }
    if (m_widthField < extToken.length())
    {
      m_widthField = static_cast<size_t>(extToken.length());
    }
    return extToken;
  }

  void Utilities::setDelimiter(char newDelimiter)
  {
    m_delimiter = newDelimiter;
  }

  char Utilities::getDelimiter()
  {
    return m_delimiter;
  }

}