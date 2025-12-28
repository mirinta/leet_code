#include <string>
#include <vector>

/**
 * Design an algorithm to encode a list of strings to a string. The encoded string is then sent over
 * the network and is decoded back to the original list of strings.
 *
 * Machine 1 (sender) has the function:
 *
 * string encode(vector<string> strs) {
 *   // ... your code
 *   return encoded_string;
 * }
 *
 * Machine 2 (receiver) has the function:
 *
 * vector<string> decode(string s) {
 *   //... your code
 *   return strs;
 * }
 *
 * So Machine 1 does: string encoded_string = encode(strs);
 *
 * and Machine 2 does: vector<string> strs2 = decode(encoded_string);
 *
 * strs2 in Machine 2 should be the same as strs in Machine 1.
 *
 * Implement the encode and decode methods.
 *
 * You are not allowed to solve the problem using any serialize methods (such as eval).
 *
 * ! 1 <= strs.length <= 200
 * ! 0 <= strs[i].length <= 200
 * ! strs[i] contains any possible characters out of 256 valid ASCII characters.
 */

class Codec {
public:
    // Encodes a list of strings to a single string.
    std::string encode(std::vector<std::string>& strs)
    {
        std::string s;
        for (const auto& str : strs) {
            s.append(str);
            s.append(kDelimiter);
        }
        return s;
    }

    // Decodes a single string to a list of strings.
    std::vector<std::string> decode(std::string s)
    {
        std::vector<std::string> strs;
        int i = 0;
        int j = s.find(kDelimiter, i);
        while (j != std::string::npos) {
            strs.push_back(s.substr(i, j - i));
            i = j + kDelimiter.size();
            j = s.find(kDelimiter, i);
        }
        return strs;
    }

private:
    const std::string kDelimiter = "☆"; // non-ASCII
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.decode(codec.encode(strs));