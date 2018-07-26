#include <core/core.h>
#include <core/epoc/hal.h>

#include <common/algorithm.h>
#include <common/log.h>

#include <common/e32inc.h>
#include <e32err.h>

#include <core/epoc/des.h>

#define REGISTER_HAL_FUNC(op, hal_name, func) \
    funcs.emplace(op, std::bind(&##hal_name::##func, this, std::placeholders::_1, std::placeholders::_2))

#define REGISTER_HAL(sys, cage, hal_name) \
    sys->add_new_hal(cage, std::make_shared<##hal_name>(sys))

namespace eka2l1::epoc {
    hal::hal(eka2l1::system *sys)
        : sys(sys) {}

    int hal::do_hal(uint32_t func, int *a1, int *a2) {
        auto func_pair = funcs.find(func);

        if (func_pair == funcs.end()) {
            return -1;
        }

        return func_pair->second(a1, a2);
    }

    /*! \brief Kernel HAL cagetory. 
     * Contains HAL of drivers, memory, etc...
     */
    struct kern_hal : public eka2l1::epoc::hal {
        /*! \brief Get the size of a page. 
         *
         * \param a1 The pointer to the integer destination, supposed to
         *           contains the page size.
         * \param a2 Unused.
         */
        int page_size(int *a1, int *a2) {
            *a1 = static_cast<int>(sys->get_memory_system()->get_page_size());
            return KErrNone;
        }

        int memory_info(int *a1, int *a2) {
            TDes8 *buf = reinterpret_cast<TDes8 *>(a1);
            TMemoryInfoV1 memInfo;

            memInfo.iTotalRamInBytes = common::MB(512);
            memInfo.iRomIsReprogrammable = false;
            memInfo.iMaxFreeRamInBytes = common::MB(512);
            memInfo.iFreeRamInBytes = common::MB(512);
            memInfo.iTotalRomInBytes = sys->get_rom_info().header.rom_size;
            memInfo.iInternalDiskRamInBytes = memInfo.iTotalRomInBytes; // This value is appr. the same as rom.

            std::string dat;
            dat.resize(sizeof(memInfo));

            memcpy(dat.data(), &memInfo, sizeof(memInfo));

            buf->Assign(sys, dat);

            return KErrNone;
        }

        kern_hal(eka2l1::system *sys)
            : hal(sys) {
            REGISTER_HAL_FUNC(EKernelHalPageSizeInBytes, kern_hal, page_size);
            REGISTER_HAL_FUNC(EKernelHalMemoryInfo, kern_hal, memory_info);
        }
    };

    void init_hal(eka2l1::system *sys) {
        REGISTER_HAL(sys, 0, kern_hal);
    }

    int do_hal(eka2l1::system *sys, uint32_t cage, uint32_t func, int *a1, int *a2) {
        hal_ptr hal_com = sys->get_hal(cage);

        if (!hal_com) {
            LOG_TRACE("HAL cagetory not found or unimplemented: 0x{:x} (for function: 0x{:x})",
                cage, func);

            return KErrNotFound;
        }

        int ret = hal_com->do_hal(func, a1, a2);

        if (ret == -1) {
            LOG_WARN("Unimplemented HAL function, cagetory: 0x{:x}, function: 0x{:x}",
                cage, func);
        }

        return ret;
    }
}