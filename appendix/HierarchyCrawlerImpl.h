#ifndef FDTD_CORE_IO_HIERARCHY_CRAWLER_IMPL_H_
#define FDTD_CORE_IO_HIERARCHY_CRAWLER_IMPL_H_

namespace Fdtd {
namespace Core {
namespace IO {

class HierarchyCrawlerImpl
{
public:

    virtual ~HierarchyCrawlerImpl() {}
    virtual bool enterStream() = 0;
    virtual bool leaveStream() = 0;
    virtual bool enterSection(const std::string& name, int level, void*& data) = 0;
    virtual bool leaveSection(const std::string& name, int level, void* data) = 0;
    virtual bool enterAnonymousSection(int idx, int level, void*& data) = 0;
    virtual bool leaveAnonymousSection(int idx, int level, void* data) = 0;
    virtual void utilizeDataPointer(void* ptr) = 0;
};

} // namespace IO
} // namespace Core
} // namespace Fdtd
#endif // FDTD_CORE_IO_HIERARCHY_CRAWLER_IMPL_H_
