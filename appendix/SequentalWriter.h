#ifndef FDTD_CORE_IO_SEQUENTAL_WRITER_H_
#define FDTD_CORE_IO_SEQUENTAL_WRITER_H_

#include <ostream>
#include <string>
#include <stack>
#include "HierarchyCrawler.h"

namespace Fdtd {
namespace Core {
namespace IO {

class SequentalWriterImpl;

class SequentalWriter: public HierarchyCrawler
{
public:

    explicit SequentalWriter(
        const std::string& fileName,
        SequentalWriterImpl* impl=0);

    ~SequentalWriter();
    void close();

    void putValue(const std::string& name, int value);
    void putValue(const std::string& name, unsigned int value);
    void putValue(const std::string& name, float value);
    void putValue(const std::string& name, double value);
    void putValue(const std::string& name, const std::string& value);
    void putValue(const std::string& name, const std::wstring& value);

private:

    std::string          m_fileName;
    SequentalWriterImpl* m_impl;
};

} // namespace IO
} // namespace Core
} // namespace Fdtd
#endif // FDTD_CORE_IO_SEQUENTAL_WRITER_H_
