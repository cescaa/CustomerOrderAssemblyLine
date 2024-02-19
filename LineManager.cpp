#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "LineManager.h"
#include "Utilities.h"

namespace sdds
{

  LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
  {

    std::ifstream fo(file);
    if (!fo)
    {
      throw std::string("Unable to open ") + file;
    }
    else
    {
      std::string row, s_curr, s_nex;
      while (std::getline(fo, row))
      {
        Utilities Uti;
        sdds::Utilities::setDelimiter('|');
        size_t nextPos = 0;
        bool more = true;

        s_curr = Uti.extractToken(row, nextPos, more);
        Workstation *curr_w = *std::find_if(stations.begin(), stations.end(),
                                            [&](Workstation *p_stat)
                                            { return p_stat->getItemName() == s_curr; });
        m_activeLine.push_back(curr_w);

        if (more)
        {
          s_nex = Uti.extractToken(row, nextPos, more);
          Workstation *w_next = *std::find_if(stations.begin(), stations.end(),
                                              [&](Workstation *p_station)
                                              { return p_station->getItemName() == s_nex; });
          curr_w->setNextStation(w_next);
        }
      }

      if (!m_activeLine.empty())
      {
        std::vector<Workstation *> tw;
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *stat)
                      { tw.push_back(stat); });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation *stat)
                      { std::remove(tw.begin(), tw.end(), stat->getNextStation()); });
        m_firstStation = tw[0];
      }
      m_cntCustomerOrder = g_pending.size();
    }
  }

  void LineManager::reorderStations()
  {
    m_activeLine.clear();

    Workstation *curr = m_firstStation;

    while (curr)
    {
      m_activeLine.push_back(curr);
      curr = curr->getNextStation();
    }
  }

  bool LineManager::run(std::ostream &os)
  {

    static size_t c = 0;
    ++c;
    os << "Line Manager Iteration: " << c << std::endl;

    if (!g_pending.empty())
    {
      *m_firstStation += std::move(g_pending.front());
      g_pending.pop_front();
    }

    std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation *obj)
                  { obj->fill(os); });

    std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation *obj)
                  { obj->attemptToMoveOrder(); });

    return g_pending.empty() && (g_completed.size() + g_incomplete.size() == m_cntCustomerOrder);
  }

  void LineManager::display(std::ostream &os) const
  {
    if (!m_activeLine.empty())
    {
      for (auto &e : m_activeLine)
        e->display(os);
    }
  }
}
