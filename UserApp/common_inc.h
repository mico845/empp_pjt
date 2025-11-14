#pragma once

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------- C Scope ---------------------------*/

[[noreturn]] void Main();

#ifdef __cplusplus
}

/*---------------------------- C++ Scope ---------------------------*/

    #include <empp.hpp>
using namespace empp::stm32h7;

#endif
