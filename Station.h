

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <string>

namespace sdds
{
  class Station
  {
    int m_id{0};
    std::string m_itemName{""};
    size_t m_serialNum{0};
    size_t m_currentStock{0};
    std::string m_desc{""};

    static size_t m_widthField;
    static size_t id_generator;

  public:
    Station() = default;
    Station(const std::string &line);
    const std::string &getItemName() const;
    size_t getNextSerialNumber();
    size_t getQuantity() const;
    void updateQuantity();
    void display(std::ostream &os, bool full) const;
  };
  std::string removeSpaces(std::string str);
}

#endif