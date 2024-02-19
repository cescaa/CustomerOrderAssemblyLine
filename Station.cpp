// Name: CESCA DELA CRUZ
// Seneca Student ID: 123123150
// Seneca email: afgdela-cruz@mysenecacollege.ca
// Date of completion: dec 6, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds
{
  size_t Station::m_widthField = 0;
  size_t Station::id_generator = 0;

  Station::Station(const std::string &line)
  {
    m_id = 1 + id_generator++;
    Utilities uti;
    size_t next_pos = 0;
    bool more = true;
    m_itemName = uti.extractToken(line, next_pos, more);
    m_serialNum = std::stoul(uti.extractToken(line, next_pos, more));
    m_currentStock = std::stoul(uti.extractToken(line, next_pos, more));

    if (m_widthField < uti.getFieldWidth())
    {
      m_widthField = uti.getFieldWidth();
    }
    m_desc = uti.extractToken(line, next_pos, more);
  }

  const std::string &Station::getItemName() const
  {
    return m_itemName;
  }

  size_t Station::getNextSerialNumber()
  {
    m_serialNum++;

    size_t sn = m_serialNum - 1;
    return sn;
  }

  size_t Station::getQuantity() const
  {
    return m_currentStock;
  }

  void Station::updateQuantity()
  {
    m_currentStock--;
  }

  void Station::display(std::ostream &os, bool full) const
  {

    os << std::left << "00" << m_id << " | ";
    os << std::setw(m_widthField) << std::left << std::setfill(' ') << m_itemName << " | ";
    os << std::setw(6) << std::setfill('0') << std::right << m_serialNum << " | ";

    if (full)
    {
      {
        os << std::setw(4) << std::right << std::setfill(' ') << m_currentStock << " | ";
      }
      os << std::left << removeSpaces(m_desc);
    }
    os << std::endl;
  }

  std::string removeSpaces(std::string str)
  {
    if (str.length() > 0)
    {
      size_t sIdx = str.find_first_not_of(" ");
      size_t eIdx = str.find_last_not_of(" ");

      str = str.substr(sIdx, eIdx - sIdx + 1);
    }
    return str;
  }

}
