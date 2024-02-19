#include <iostream>
#include <fstream>
#include <string>
#include "Workstation.h"

namespace sdds
{
  std::deque<CustomerOrder> g_pending{};
  std::deque<CustomerOrder> g_completed{};
  std::deque<CustomerOrder> g_incomplete{};

  Workstation::Workstation(const std::string str) : Station(str) {}

  void Workstation::fill(std::ostream &os)
  {

    if (!m_orders.empty())
    {

      m_orders.front().fillItem(*this, os);
    }
  }

  bool Workstation::attemptToMoveOrder()
  {
    if (!m_orders.empty() && (m_orders.front().isItemFilled(getItemName()) || getQuantity() == 0))
    {
      if (m_pNextStation != nullptr)
      {
        *m_pNextStation += std::move(m_orders.front());
      }
      else
      {
        if (m_orders.front().isOrderFilled())
        {
          g_completed.push_back(std::move(m_orders.front()));
        }
        else
        {
          g_incomplete.push_back(std::move(m_orders.front()));
        }
      }
      m_orders.pop_front();
      return true;
    }
    return false;
  }

  void Workstation::setNextStation(Workstation *station)
  {
    if (station != nullptr)
    {
      m_pNextStation = station;
    };
  }
  Workstation *Workstation::getNextStation() const
  {
    return m_pNextStation;
  }

  void Workstation::display(std::ostream &os) const
  {
    os << getItemName() << " --> ";
    if (m_pNextStation != nullptr)
    {
      os << m_pNextStation->getItemName();
    }
    else
    {
      os << "End of Line";
    }
    os << std::endl;
  }

  Workstation &Workstation::operator+=(CustomerOrder &&newOrder)
  {
    m_orders.push_back(std::move(newOrder));
    return *this;
  }
}