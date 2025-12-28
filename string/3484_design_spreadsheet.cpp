#include <string>
#include <vector>

/**
 * A spreadsheet is a grid with 26 columns (labeled from 'A' to 'Z') and a given number of rows.
 * Each cell in the spreadsheet can hold an integer value between 0 and 105.
 *
 * Implement the Spreadsheet class:
 *
 * - Spreadsheet(int rows) Initializes a spreadsheet with 26 columns (labeled 'A' to 'Z') and the
 * specified number of rows. All cells are initially set to 0.
 *
 * - void setCell(String cell, int value) Sets the value of the specified cell. The cell reference
 * is provided in the format "AX" (e.g., "A1", "B10"), where the letter represents the column (from
 * 'A' to 'Z') and the number represents a 1-indexed row.
 *
 * - void resetCell(String cell) Resets the specified cell to 0.
 *
 * - int getValue(String formula) Evaluates a formula of the form "=X+Y", where X and Y are either
 * cell references or non-negative integers, and returns the computed sum.
 *
 * Note: If getValue references a cell that has not been explicitly set using setCell, its value is
 * considered 0.
 *
 * ! 1 <= rows <= 10^3
 * ! 0 <= value <= 10^5
 * ! The formula is always in the format "=X+Y", where X and Y are either valid cell references or
 * ! non-negative integers with values less than or equal to 10^5.
 * ! Each cell reference consists of a capital letter from 'A' to 'Z' followed by a row number
 * ! between 1 and rows.
 * ! At most 10^4 calls will be made in total to setCell, resetCell, and getValue.
 */

class Spreadsheet {
public:
    Spreadsheet(int rows) : grid(rows + 1, std::vector<int>(26, 0)) {}

    void setCell(const std::string& cell, int value)
    {
        grid[stoi(1, cell.size() - 1, cell)][cell[0] - 'A'] = value;
    }

    void resetCell(const std::string& cell)
    {
        setCell(cell, 0);
    }

    int getValue(const std::string& formula)
    {
        const auto index = formula.find('+');
        return parse(1, index - 1, formula) + parse(index + 1, formula.size() - 1, formula);
    }

private:
    int parse(int lo, int hi, const std::string& s)
    {
        if (std::isalpha(s[lo]))
            return grid[stoi(lo + 1, hi, s)][s[lo] - 'A'];

        return stoi(lo, hi, s);
    }

    int stoi(int lo, int hi, const std::string& s)
    {
        int result = 0;
        while (lo <= hi) {
            result = result * 10 + (s[lo] - '0');
            lo++;
        }
        return result;
    }

private:
    std::vector<std::vector<int>> grid;
};

/**
 * Your Spreadsheet object will be instantiated and called as such:
 * Spreadsheet* obj = new Spreadsheet(rows);
 * obj->setCell(cell,value);
 * obj->resetCell(cell);
 * int param_3 = obj->getValue(formula);
 */