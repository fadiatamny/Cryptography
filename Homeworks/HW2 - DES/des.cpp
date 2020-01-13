#include "des.hpp"
#pragma region tables
char table_ip[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7};

char table_ip_reverse[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25};

char table_pc_1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4};

char table_pc_2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32};

char table_e[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

char table_s[8][4][16] = {
    {{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
     {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
     {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
     {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
    {{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
     {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
     {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
     {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
    {{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
     {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
     {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
     {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
    {{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
     {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
     {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
     {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
    {{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
     {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
     {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
     {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
    {{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
     {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
     {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
     {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
    {{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
     {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
     {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
     {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
    {{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
     {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
     {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
     {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}

};

char table_p[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};
#pragma endregion

std::vector<unsigned char> ip(std::vector<unsigned char> block)
{
  std::vector<unsigned char> tempVector;
  for (int i = 0; i < 64; ++i)
  {
    tempVector.push_back(block[table_ip[i] - 1]);
  }
  return tempVector;
};

std::vector<unsigned char> ip_reverse(std::vector<unsigned char> block)
{
  std::vector<unsigned char> revTempVector;
  for (int i = 0; i < 64; ++i)
  {
    revTempVector.push_back(block[table_ip_reverse[i] - 1]);
  }
}

std::vector<unsigned char> shiftLeftTwice(std::vector<unsigned char> keyPart)
{
  std::vector<unsigned char> shiftKeyPart;
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 1; j < 28; ++j)
    {
      shiftKeyPart.push_back(keyPart[j] - 1);
    }
    shiftKeyPart.push_back(keyPart[0]);
    keyPart = shiftKeyPart;
    shiftKeyPart.clear();
  }
  return keyPart;
}

std::vector<unsigned char> shiftLeftOnce(std::vector<unsigned char> keyPart)
{
  std::vector<unsigned char> shiftKeyPart;
  for (int j = 1; j < 28; ++j)
  {
    shiftKeyPart.push_back(keyPart[j] - 1);
  }
  shiftKeyPart.push_back(keyPart[0]);
  return shiftKeyPart;
}

std::vector<std::vector<unsigned char>> genKey(std::vector<unsigned char> key)
{
  std::vector<std::vector<unsigned char>> allkeys;
  std::vector<unsigned char> permKey;
  std::vector<unsigned char> leftKey;
  std::vector<unsigned char> rightKey;
  std::vector<unsigned char> comKey;
  std::vector<unsigned char> finKey;

  for (int i = 0; i < 56; ++i)
  {
    permKey.push_back(key[table_pc_1[i] - 1]);
  }
  for (int i = 0; i < 56; ++i)
  {
    if (i < 28)
    {
      leftKey.push_back(permKey[i]);
    }
    else
    {
      rightKey.push_back(permKey[i]);
    }
  }
  for (int i = 0; i < 16; ++i)
  {
    if (i == 0 || i == 1 || i == 8 || i == 15)
    {
      leftKey = shiftLeftOnce(leftKey);
      rightKey = shiftLeftOnce(rightKey);
    }
    else
    {
      leftKey = shiftLeftTwice(leftKey);
      rightKey = shiftLeftTwice(rightKey);
    }

    for (int i = 0; i < 2; ++i)
    {
      for (int j = 0; j < 28; ++j)
      {
        if (i == 0)
        {
          comKey.push_back(leftKey[j]);
        }
        else
        {
          comKey.push_back(rightKey[j]);
        }
      }
    }

    for (int i = 0; i < 48; ++i)
    {
      finKey.push_back(comKey[table_pc_2[i] - 1]);
    }

    allkeys.push_back(finKey);

    finKey.clear();
    comKey.clear();
  }

  return allkeys;
}

std::vector<unsigned char> Xor(std::vector<unsigned char> a, std::vector<unsigned char> b)
{
  std::vector<unsigned char> result;
  int size = b.size();
  for (int i = 0; i < size; ++i)
  {
    if (a[i] != b[i])
    {
      result.push_back('1');
    }
    else
    {
      result.push_back('0');
    }
  }
  return result;
}

int convertBinToDec(std::vector<unsigned char> binnum)
{
  std::string temp(binnum.begin(), binnum.end());
  int res = std::stoi(temp,0,2);
        std::cout << res << " " << temp << std::endl;

  return res;
}

std::vector<unsigned char> convertDecToBin(int decnum)
{
  std::vector<unsigned char> binnum;
  while (decnum > 0)
  {
    binnum.push_back(decnum % 2);
    decnum = decnum / 2;
  }
  return binnum;
}

std::vector<unsigned char> encryptBlock(const std::vector<unsigned char> &block, const std::vector<unsigned char> &key)
{
  //initialPermutation
  std::vector<std::vector<unsigned char>> allkeys;
  std::vector<unsigned char> tempblock = ip(block);
  std::vector<unsigned char> rightblock;
  std::vector<unsigned char> leftblock;
  std::vector<unsigned char> res;
  std::vector<unsigned char> ciphertxt;
  std::vector<unsigned char> combindtxt;
  //split left and right
  for (int i = 0; i < 64; ++i)
  {
    if (i < 32)
    {
      leftblock.push_back(tempblock[i]);
    }
    else
    {
      rightblock.push_back(tempblock[i]);
    }
  }

  // genkey
  allkeys = genKey(key);

  //foreach 16 keys
  for (int i = 0; i < 16; ++i)
  {
    std::vector<unsigned char> rightExpend;
    for (int i = 0; i < 48; ++i)
    {
      rightExpend.push_back(rightblock[table_e[i] - 1]);
    }

    std::vector<unsigned char> xorRes = Xor(allkeys[i], rightExpend);

    for (int i = 0; i < 8; ++i)
    {
      std::vector<unsigned char> row1;
      row1.push_back(xorRes[i * 6]);
      row1.push_back(xorRes[i * 6 + 5]);
      int row = convertBinToDec(row1);
      std::vector<unsigned char> col1;
      col1.push_back(xorRes[i * 6 + 1]);
      col1.push_back(xorRes[i * 6 + 2]);
      col1.push_back(xorRes[i * 6 + 3]);
      col1.push_back(xorRes[i * 6 + 4]);
      int col = convertBinToDec(col1);
      int val = table_s[i][row][col];
      res = convertDecToBin(val);
      std::cout << row << " " << col << std::endl;
    }
            std::cout << "soome message"<< std::endl;

    std::vector<unsigned char> perm2;
    for (int i = 0; i < 32; ++i)
    {
      perm2.push_back(res[table_pc_2[i] - 1]);
    }
                std::cout << "soome message"<< std::endl;

    leftblock = xorRes;
    if (i < 15)
    {
      std::vector<unsigned char> temp = rightblock;
      rightblock = xorRes;
      leftblock = temp;
    }
  }
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 32; ++j)
    {
      if (i == 0)
      {
        combindtxt.push_back(leftblock[j]);
      }
      else
      {
        combindtxt.push_back(rightblock[j]);
      }
    }
  }
  for (int i = 0; i < 64; ++i)
  {
    ciphertxt.push_back(combindtxt[table_ip_reverse[i] - 1]);
  }
  return ciphertxt;

  //  f(r,k). right = f xor l
  //
  // return right+left;
}

std::vector<unsigned char> decryptBlock(const std::vector<unsigned char> &block, const std::vector<unsigned char> &key)
{
  //initialPermutation
  std::vector<std::vector<unsigned char>> allkeys;
  std::vector<unsigned char> tempblock = ip(block);
  std::vector<unsigned char> rightblock;
  std::vector<unsigned char> leftblock;
  std::vector<unsigned char> res;
  std::vector<unsigned char> decrptxt;
  std::vector<unsigned char> combindtxt;
  std::vector<std::vector<unsigned char>> revallkeys;
  //split left and right
  for (int i = 0; i < 64; ++i)
  {
    if (i < 32)
    {
      leftblock.push_back(tempblock[i]);
    }
    else
    {
      rightblock.push_back(tempblock[i]);
    }
  }

  // genkey
  allkeys = genKey(key);
  for (int i = 15; i >= 0; --i)
  {
    revallkeys.push_back(allkeys[i]);
  }

  //foreach 16 keys
  for (int i = 0; i < 16; ++i)
  {
    std::vector<unsigned char> rightExpend;
    for (int i = 0; i < 48; ++i)
    {
      rightExpend.push_back(rightblock[table_e[i] - 1]);
    }
    std::vector<unsigned char> xorRes = Xor(revallkeys[i], rightExpend);

    for (int i = 0; i < 8; ++i)
    {
      std::vector<unsigned char> row1;
      row1.push_back(xorRes[i * 6]);
      row1.push_back(xorRes[i * 6 + 5]);
      int row = convertBinToDec(row1);
      std::vector<unsigned char> col1;
      col1.push_back(xorRes[i * 6 + 1]);
      col1.push_back(xorRes[i * 6 + 2]);
      col1.push_back(xorRes[i * 6 + 3]);
      col1.push_back(xorRes[i * 6 + 4]);
      int col = convertBinToDec(col1);
      int val = table_s[i][row][col];
      res = convertDecToBin(val);
    }
    std::vector<unsigned char> perm2;
    for (int i = 0; i < 32; ++i)
    {
      perm2.push_back(res[table_pc_2[i] - 1]);
    }
    leftblock = xorRes;
    if (i < 15)
    {
      std::vector<unsigned char> temp = rightblock;
      rightblock = xorRes;
      leftblock = temp;
    }
  }
  for (int i = 0; i < 2; ++i)
  {
    for (int j = 0; j < 32; ++j)
    {
      if (i == 0)
      {
        combindtxt.push_back(leftblock[j]);
      }
      else
      {
        combindtxt.push_back(rightblock[j]);
      }
    }
  }
  for (int i = 0; i < 64; ++i)
  {
    decrptxt.push_back(combindtxt[table_ip_reverse[i] - 1]);
  }
  return decrptxt;
}
