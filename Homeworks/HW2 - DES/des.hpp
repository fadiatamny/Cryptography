#pragma once
#include "includes.hpp"

std::vector<unsigned char> encryptBlock(const std::vector<unsigned char> &block, const std::vector<unsigned char> &key);
std::vector<unsigned char> decryptBlock(const std::vector<unsigned char> &block, const std::vector<unsigned char> &key);
