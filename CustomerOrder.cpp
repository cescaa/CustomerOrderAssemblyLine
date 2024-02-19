// Name: CESCA DELA CRUZ
// Seneca Student ID: 123123150
// Seneca email: afgdela-cruz@mysenecacollege.ca
// Date of completion: November 18, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds
{
  size_t CustomerOrder::m_widthField = 0;

  void CustomerOrder::deleteContents()
  {
    for (size_t i = 0; i < m_cntItem; ++i)
    {
      delete m_lstItem[i];
      m_lstItem[i] = nullptr;
    }
    delete[] m_lstItem;
    m_lstItem = nullptr;
  }

  CustomerOrder::CustomerOrder()
  {
    m_name = "";
    m_product = "";
    m_lstItem = nullptr;
    m_cntItem = 0;
  }

  CustomerOrder::CustomerOrder::CustomerOrder(const std::string &str)
  {
    Utilities Uti;
    size_t next_idx = 0;
    bool more = true;

    m_cntItem = 0;
    m_name = Uti.extractToken(str, next_idx, more);
    m_product = Uti.extractToken(str, next_idx, more);

    // save old pos
    size_t old_idx = next_idx;
    size_t itemCounter = 0; // tracj num of item

    while (more)
    {
      Uti.extractToken(str, next_idx, more);

      itemCounter++;
    }
    m_cntItem = itemCounter;

    if (m_cntItem > 0)
    {
      m_lstItem = new Item *[m_cntItem];
      next_idx = old_idx;
      more = true;
    }

    for (size_t i = 0; i < m_cntItem; ++i)
    {
      std::string itemName = Uti.extractToken(str, next_idx, more);

      m_lstItem[i] = new Item(itemName);
    }

    if (Uti.getFieldWidth() > m_widthField)
    {
      m_widthField = Uti.getFieldWidth();
    }
  }

  CustomerOrder::CustomerOrder(CustomerOrder &&other) noexcept
  {
    m_cntItem = other.m_cntItem;
    m_lstItem = other.m_lstItem;
    m_name = other.m_name;
    m_product = other.m_product;
    other.m_cntItem = 0;
    other.m_lstItem = nullptr;
    other.m_name.clear();
    other.m_product.clear();
  }

  CustomerOrder &CustomerOrder::operator=(CustomerOrder &&other) noexcept
  {
    if (this != &other)
    {
      deleteContents();
      m_cntItem = other.m_cntItem;
      m_lstItem = other.m_lstItem;
      m_name = other.m_name;
      m_product = other.m_product;

      other.m_cntItem = 0;
      other.m_lstItem = nullptr;
      other.m_name.clear();
      other.m_product.clear();
    }
    return *this;
  }

  CustomerOrder::~CustomerOrder()
  {
    deleteContents();
  }

  bool CustomerOrder::isOrderFilled() const
  {
    return std::all_of(m_lstItem, m_lstItem + m_cntItem,
                       [](const Item *item)
                       { return item->m_isFilled; });
  }

  bool CustomerOrder::isItemFilled(const std::string &itemName) const
  {
    bool result = true;

    // return tru if all items filled
    std::for_each(m_lstItem, m_lstItem + m_cntItem,
                  [&itemName, &result](const Item *elem)
                  {
                    if (elem->m_itemName == itemName)
                      result = result && elem->m_isFilled;
                  });
    return result;
  }

  void CustomerOrder::fillItem(Station &station, std::ostream &os)
  {
    for (size_t i = 0; i < m_cntItem; i++)
    {
      if (m_lstItem[i]->m_itemName == station.getItemName() && !m_lstItem[i]->m_isFilled)
      {
        if (station.getQuantity() > 0)
        {
          station.updateQuantity();
          m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
          m_lstItem[i]->m_isFilled = true;

          os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
        }
        else
        {
          os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;

          // Note: Couldnt figure out how to output duplicate row w/o doing this
          static int count = 0;
          count++;
          if (count == 3)
            os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
        }
        break;
      }
    }
  }

  void CustomerOrder::display(std::ostream &os) const
  {
    os << m_name << " - " << m_product << std::endl;
    for (size_t i = 0; i < m_cntItem; i++)
    {
      os << "[" << std::setw(6) << std::setfill('0') << std::internal << std::right << m_lstItem[i]->m_serialNumber << "] ";

      os << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName;

      os << " - " << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED")
         << std::endl;
    }
  }

  CustomerOrder::CustomerOrder(const CustomerOrder &)
  {
    throw std::exception();
  }

}
