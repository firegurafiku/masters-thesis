#include "HdfWriterImpl.h"
#include "Format.h"

namespace Fdtd {
namespace Formats {
namespace Binary {

using namespace Fdtd::Core;

HdfWriterImpl::HdfWriterImpl()
{
    m_fileHid = 0;
}

HdfWriterImpl::~HdfWriterImpl()
{
}

void HdfWriterImpl::attachOutput(const std::string& fileName)
{
    m_fileHid = H5Fcreate(fileName.c_str(),
        H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

    m_singleDataspaceId = H5Screate(H5S_SCALAR);
    m_varcharDatatypeId = H5Tcopy(H5T_C_S1);
    H5Tset_size(m_varcharDatatypeId, H5T_VARIABLE);

    m_varcharFiletypeId = H5Tcopy(H5T_FORTRAN_S1);
    H5Tset_size(m_varcharFiletypeId, H5T_VARIABLE);
}

void HdfWriterImpl::detachOutput()
{
    H5Tclose(m_varcharFiletypeId);
    H5Tclose(m_varcharDatatypeId);
    H5Sclose(m_singleDataspaceId);
    H5Fclose(m_fileHid);
}

bool HdfWriterImpl::enterStream()
{
    if (m_fileHid<0) return false;
    else
    {
        m_stack.push(m_fileHid);
        return true;
    }
}

bool HdfWriterImpl::leaveStream()
{
    m_stack.pop();
    return true;
}

bool HdfWriterImpl::enterSection(const std::string& name, int level, void*& data)
{
    (void)level;
    (void)data;

    hid_t hid = H5Gcreate(m_stack.top(), name.c_str(),
                    H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    if (hid<0) return false;
    else
    {
        m_stack.push(hid);
        return true;
    }
}

bool HdfWriterImpl::leaveSection(const std::string& name, int level, void* data)
{
    (void)name;
    (void)level;
    (void)data;

    herr_t status = H5Gclose(m_stack.top());
    if (status<0) return false;
    else
    {
        m_stack.pop();
        return true;
    }
}

bool HdfWriterImpl::enterAnonymousSection(int idx, int level, void*& data)
{
    return enterSection(Text::format(idx), level, data);
}

bool HdfWriterImpl::leaveAnonymousSection(int idx, int level, void* data)
{
    return leaveSection(Text::format(idx), level, data);
}

void HdfWriterImpl::utilizeDataPointer(void* ptr)
{
    (void)ptr;
    ; // Освобождать память нам не нужно, этим займется деструктор.
}

static bool internalPutValue(
    hid_t groupId,
    hid_t dataspaceId,
    hid_t fileDatatypeId,
    hid_t memoryDatatypeId,
    const std::string& name,
    const void* val)
{
    hid_t datasetId = H5Dcreate(groupId, name.c_str(), fileDatatypeId,
                          dataspaceId, H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    herr_t status = H5Dwrite(datasetId, memoryDatatypeId, H5S_ALL,
                          H5S_ALL, H5P_DEFAULT, val);

    H5Dclose(datasetId);
    return status>=0;
}

bool HdfWriterImpl::putValue(const std::string& name, const int val)
{
    hid_t groupId = m_stack.top();
    return internalPutValue(groupId, m_singleDataspaceId,
                            H5T_STD_I32LE, H5T_NATIVE_INT, name, &val);
}

bool HdfWriterImpl::putValue(const std::string& name, const unsigned int val)
{
    hid_t groupId = m_stack.top();
    return internalPutValue(groupId, m_singleDataspaceId,
                            H5T_STD_U32LE, H5T_NATIVE_UINT, name, &val);
}

bool HdfWriterImpl::putValue(const std::string& name, const float val)
{
    hid_t groupId = m_stack.top();
    return internalPutValue(groupId, m_singleDataspaceId,
                            H5T_IEEE_F32LE, H5T_NATIVE_FLOAT, name, &val);
}

bool HdfWriterImpl::putValue(const std::string& name, const double val)
{
    hid_t groupId = m_stack.top();
    return internalPutValue(groupId, m_singleDataspaceId,
                            H5T_IEEE_F64LE, H5T_NATIVE_DOUBLE, name, &val);
}

bool HdfWriterImpl::putValue(const std::string& name, const std::string& val)
{
    const char* buf = val.c_str();
    hid_t groupId = m_stack.top();
    return internalPutValue(groupId, m_singleDataspaceId, m_varcharFiletypeId,
                            m_varcharDatatypeId, name, &buf);
}

bool HdfWriterImpl::putValue(const std::string& name, const std::wstring& val)
{
    (void)name;
    (void)val;

    // TODO: stub (Сначала нужно реализовать Fdtd::Core::Encodings)
    return false;
}

} // namespace Binary
} // namespace Formats
} // namespace Fdtd

