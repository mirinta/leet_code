#include <map>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * You are given two string arrays, names and columns, both of size n. The ith table is represented
 * by the name names[i] and contains columns[i] number of columns.
 *
 * You need to implement a class that supports the following operations:
 *
 * - Insert a row in a specific table with an id assigned using an auto-increment method, where the
 * id of the first inserted row is 1, and the id of each new row inserted into the same table is one
 * greater than the id of the last inserted row, even if the last row was removed.
 *
 * - Remove a row from a specific table. Removing a row does not affect the id of the next inserted
 * row.
 *
 * - Select a specific cell from any table and return its value.
 *
 * - Export all rows from any table in csv format.
 *
 * Implement the SQL class:
 *
 * - SQL(String[] names, int[] columns)
 *
 *   - Creates the n tables.
 *
 * - bool ins(String name, String[] row)
 *
 *   - Inserts row into the table name and returns true.
 *
 *   - If row.length does not match the expected number of columns, or name is not a valid table,
 *     returns false without any insertion.
 *
 * - void rmv(String name, int rowId)
 *
 *   - Removes the row rowId from the table name.
 *
 *   - If name is not a valid table or there is no row with id rowId, no removal is performed.
 *
 * - String sel(String name, int rowId, int columnId)
 *
 *   - Returns the value of the cell at the specified rowId and columnId in the table name.
 *
 *   - If name is not a valid table, or the cell (rowId, columnId) is invalid, returns "<null>".
 *
 * - String[] exp(String name)
 *
 *   - Returns the rows present in the table name.
 *
 *   - If name is not a valid table, returns an empty array. Each row is represented as a string,
 *     with each cell value (including the row's id) separated by a ",".
 *
 * ! n == names.length == columns.length
 * ! 1 <= n <= 10^4
 * ! 1 <= names[i].length, row[i].length, name.length <= 10
 * ! names[i], row[i], and name consist only of lowercase English letters.
 * ! 1 <= columns[i] <= 10
 * ! 1 <= row.length <= 10
 * ! All names[i] are distinct.
 * ! At most 2000 calls will be made to ins and rmv.
 * ! At most 10^4 calls will be made to sel.
 * ! At most 500 calls will be made to exp.
 */

class SQL
{
public:
    SQL(std::vector<std::string>& names, std::vector<int>& columns)
        : columns(std::move(columns)), counts(names.size(), 0), tables(names.size())
    {
        for (int i = 0; i < names.size(); ++i) {
            nameToIdx[names[i]] = i;
        }
    }

    bool ins(std::string name, std::vector<std::string> row)
    {
        if (!nameToIdx.count(name))
            return false;

        const auto& idx = nameToIdx[name];
        if (row.size() != columns[idx])
            return false;

        tables[idx][++counts[idx]] = std::move(row);
        return true;
    }

    void rmv(std::string name, int rowId)
    {
        if (!nameToIdx.count(name))
            return;

        const auto& idx = nameToIdx[name];
        if (!tables[idx].count(rowId))
            return;

        tables[idx].erase(rowId);
    }

    std::string sel(std::string name, int rowId, int columnId)
    {
        static const std::string kNull{"<null>"};
        if (!nameToIdx.count(name))
            return kNull;

        const auto& idx = nameToIdx[name];
        if (!tables[idx].count(rowId))
            return kNull;

        columnId--;
        if (columnId < 0 || columnId >= columns[idx])
            return kNull;

        return tables[idx][rowId][columnId];
    }

    std::vector<std::string> exp(std::string name)
    {
        if (!nameToIdx.count(name))
            return {};

        const auto& idx = nameToIdx[name];
        std::vector<std::string> result;
        for (const auto& [id, strs] : tables[idx]) {
            std::string row = std::to_string(id);
            for (const auto& s : strs) {
                row.push_back(',');
                row.append(s);
            }
            result.push_back(std::move(row));
        }
        return result;
    }

private:
    std::vector<int> columns;
    std::vector<int> counts;
    std::unordered_map<std::string, int> nameToIdx;
    std::vector<std::map<int, std::vector<std::string>>> tables;
};

/**
 * Your SQL object will be instantiated and called as such:
 * SQL* obj = new SQL(names, columns);
 * bool param_1 = obj->ins(name,row);
 * obj->rmv(name,rowId);
 * string param_3 = obj->sel(name,rowId,columnId);
 * vector<string> param_4 = obj->exp(name);
 */
