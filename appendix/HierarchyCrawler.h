#ifndef FDTD_CORE_IO_HIERARCHY_CRAWLER_H_
#define FDTD_CORE_IO_HIERARCHY_CRAWLER_H_

#include <string>
#include <stack>
#include "SequentalException.h"
#include "SequentalStackEntry.h"

namespace Fdtd {
namespace Core {
namespace IO {

class HierarchyCrawlerImpl;

class HierarchyCrawler
{
public:

    explicit HierarchyCrawler(HierarchyCrawlerImpl* impl);
    ~HierarchyCrawler();

    void enterStream();
    void leaveStream();
    void enterSection(const std::string& name);
    void enterSection();
    void leaveSection(const std::string& name);
    void leaveSection();
    bool entered() const { return m_entered; }
    size_t level() const { return m_stack.size(); }

protected:

    void raiseException();

private:

    typedef std::stack<SequentalStackEntry> SectionsStack;

    HierarchyCrawlerImpl* m_impl;
    SectionsStack         m_stack;
    bool                  m_entered;
};

} // namespace IO
} // namespace Core
} // namespace Fdtd
#endif // FDTD_CORE_IO_HIERARCHY_CRAWLER_H_
