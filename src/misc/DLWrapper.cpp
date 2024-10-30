#include <misc/DLWrapper.hpp>
#include <exceptions/DLopenFailure.hpp>

misc::DLWrapper::DLWrapper(const std::basic_string_view<char> &path)
{
    auto res = dlopen(path.data(), RTLD_LAZY);

    //USING NULL instead of nullptr for portability (null is defined in header and nullptr in language), if null value change, nullptr value may not change
    if (res == NULL) // NOLINT(modernize-use-nullptr)
        throw arcade::exceptions::DLopenFailure(dlerror(), path.data(), "RTLD_LAZY");
    this->_handle = res;
}

misc::DLWrapper::~DLWrapper()
{
    dlclose(this->_handle);
}
