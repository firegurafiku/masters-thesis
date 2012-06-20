#ifndef FDTD_FORMATS_BINARY_HDF_WRITER_IMPL_H_
#define FDTD_FORMATS_BINARY_HDF_WRITER_IMPL_H_

#include <hdf5.h>
#include <stack>
#include "SequentalWriterImpl.h"

namespace Fdtd {
namespace Formats {
namespace Binary {

class HdfWriterImpl: public Fdtd::Core::IO::SequentalWriterImpl
{
public:

    explicit HdfWriterImpl();
    virtual ~HdfWriterImpl();
    virtual void attachOutput(const std::string& fileName);
    virtual void detachOutput();
    virtual bool enterStream();
    virtual bool leaveStream();
    virtual bool enterSection(const std::string& name, int level, void*& data);
    virtual bool leaveSection(const std::string& name, int level, void* data);
    virtual bool enterAnonymousSection(int idx, int level, void*& data);
    virtual bool leaveAnonymousSection(int idx, int level, void* data);
    virtual void utilizeDataPointer(void* ptr);
    virtual bool putValue(const std::string& name, const int val);
    virtual bool putValue(const std::string& name, const unsigned int val);
    virtual bool putValue(const std::string& name, const float val);
    virtual bool putValue(const std::string& name, const double val);
    virtual bool putValue(const std::string& name, const std::string& val);
    virtual bool putValue(const std::string& name, const std::wstring& val);

private:

    hid_t m_fileHid;
    hid_t m_singleDataspaceId;
    hid_t m_varcharDatatypeId;
    hid_t m_varcharFiletypeId;

    std::stack<hid_t> m_stack;
};

} // namespace Binary
} // namespace Formats
} // namespace Fdtd
#endif // FDTD_FORMATS_BINARY_HDF_WRITER_IMPL_H_