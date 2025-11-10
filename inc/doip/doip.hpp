/**
 * @file doip.hpp
 * @brief Brief description of the file.
 *
 * @version 1.0
 * @date 2025-11-10
 * @author Tran Dang Khoa
 * @copyright Copyright (c) 2025 K-Project
 */

#pragma once


class DoIPMgr
{
private:
    /**
     * @brief Short description of the function.
     *
     * @param param1 Description of param1.
     * @param param2 Description of param2.
     * @return Return description.
     * @retval Optional specific return value.
     */
    DoIPMgr() {};
    DoIPMgr(const DoIPMgr&) = delete; 
    DoIPMgr& operator=(const DoIPMgr&) = delete;
    DoIPMgr& operator=(const DoIPMgr&&) = delete;

public:
    static DoIPMgr& getInstance();
};

