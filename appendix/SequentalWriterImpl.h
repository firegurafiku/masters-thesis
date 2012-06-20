#ifndef FDTD_CORE_IO_SEQUENTAL_WRITER_IMPL_H_
#define FDTD_CORE_IO_SEQUENTAL_WRITER_IMPL_H_

#include <string>
#include "HierarchyCrawlerImpl.h"

namespace Fdtd {
namespace Core {
namespace IO {

class SequentalWriterImpl: public HierarchyCrawlerImpl
{
public:

    virtual void attachOutput(const std::string& fileName) = 0;
    virtual void detachOutput() = 0;
    virtual bool putValue(const std::string& name, const int val) = 0;
    virtual bool putValue(const std::string& name, const unsigned int val) = 0;
    virtual bool putValue(const std::string& name, const float val) = 0;
    virtual bool putValue(const std::string& name, const double val) = 0;
    virtual bool putValue(const std::string& name, const std::string& val) = 0;
    virtual bool putValue(const std::string& name, const std::wstring& val) = 0;
};

} // namespace IO
} // namespace Core
} // namespace Fdtd
#endif // FDTD_CORE_IO_SEQUENTAL_WRITER_IMPL_H_
