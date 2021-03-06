/* Copyright (c) 2015-2016, EPFL/Blue Brain Project
 * All rights reserved. Do not distribute without permission.
 * Responsible Author: Cyrille Favreau <cyrille.favreau@epfl.ch>
 *
 * This file is part of Brayns <https://github.com/BlueBrain/Brayns>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BRAYNS_LOG_H
#define BRAYNS_LOG_H

#include <boost/progress.hpp>
#include <chrono>
#include <iostream>
#define BRAYNS_ERROR std::cerr << "[ERROR] "
#define BRAYNS_WARN std::cerr << "[WARN ] "
#define BRAYNS_INFO std::cout << "[INFO ] "
#ifdef NDEBUG
#define BRAYNS_DEBUG \
    if (false)       \
    std::cout
#else
#define BRAYNS_DEBUG std::cout << "[DEBUG] "
#endif

#define BRAYNS_THROW(exc)                        \
    {                                            \
        BRAYNS_ERROR << exc.what() << std::endl; \
        throw exc;                               \
    }

#define BRAYNS_TIMER(__cmd)                                              \
    {                                                                    \
        std::chrono::high_resolution_clock::time_point __startTime;      \
        uint64_t __duration;                                             \
        __startTime = std::chrono::high_resolution_clock::now();         \
        __cmd;                                                           \
        __duration =                                                     \
            std::chrono::duration_cast<std::chrono::milliseconds>(       \
                std::chrono::high_resolution_clock::now() - __startTime) \
                .count();                                                \
        std::cout << "[TIMER] " << __duration << " ms" << std::endl;     \
    }

class Progress : public boost::progress_display
{
public:
    Progress(const std::string& message, const unsigned long expectedCount)
        : boost::progress_display(expectedCount, std::cout,
                                  "[INFO ] " + message + "\n[INFO ] ",
                                  "[INFO ] ", "[INFO ] ")
    {
    }
};

#endif
