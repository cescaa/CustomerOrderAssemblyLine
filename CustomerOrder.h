#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H
#include <string>
#include <vector>
#include "Station.h"

namespace sdds
{
  struct Item
  {
    std::string m_itemName;
    size_t m_serialNumber{0};
    bool m_isFilled{false};

    Item(const std::string &src) : m_itemName(src){};
  };

  class CustomerOrder
  {
    std::string m_name;
    std::string m_product;
    size_t m_cntItem;
    Item **m_lstItem;
    static size_t m_widthField;

  public:
    void deleteContents();
    CustomerOrder();
    CustomerOrder(const std::string &str);
    CustomerOrder(CustomerOrder &&) noexcept;
    CustomerOrder &operator=(CustomerOrder &&other) noexcept;
    ~CustomerOrder();
    bool isOrderFilled() const;
    bool isItemFilled(const std::string &itemName) const;
    void fillItem(Station &station, std::ostream &os);
    void display(std::ostream &os) const;
    CustomerOrder(const CustomerOrder &);
    CustomerOrder &operator=(const CustomerOrder &) = delete;
  };
}

#endif
