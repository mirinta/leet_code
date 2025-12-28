#include <map>

/**
 * Definition for polynomial singly-linked list.
 */
struct PolyNode {
    int coefficient, power;
    PolyNode* next;
    PolyNode() : coefficient(0), power(0), next(nullptr) {};
    PolyNode(int x, int y) : coefficient(x), power(y), next(nullptr) {};
    PolyNode(int x, int y, PolyNode* next) : coefficient(x), power(y), next(next) {};
};

/**
 * A polynomial linked list is a special type of linked list where every node represents a term in a
 * polynomial expression.
 *
 * Each node has three attributes:
 *
 * coefficient: an integer representing the number multiplier of the term. The coefficient of the
 * term 9x^4 is 9.
 *
 * power: an integer representing the exponent. The power of the term 9x^4 is 4.
 *
 * next: a pointer to the next node in the list, or null if it is the last node of the list.
 *
 * The polynomial linked list must be in its standard form: the polynomial must be in strictly
 * descending order by its power value. Also, terms with a coefficient of 0 are omitted.
 *
 * Given two polynomial linked list heads, poly1 and poly2, add the polynomials together and return
 * the head of the sum of the polynomials.
 *
 * PolyNode format:
 *
 * The input/output format is as a list of n nodes, where each node is represented as its
 * [coefficient, power]. For example, the polynomial 5x^3 + 4x - 7 would be represented as:
 * [[5,3],[4,1],[-7,0]].
 *
 * ! 0 <= n <= 10^4
 * ! -10^9 <= PolyNode.coefficient <= 10^9
 * ! PolyNode.coefficient != 0
 * ! 0 <= PolyNode.power <= 10^9
 * ! PolyNode.power > PolyNode.next.power
 */

class Solution {
public:
    PolyNode* addPoly(PolyNode* poly1, PolyNode* poly2)
    {
        return approach2(poly1, poly2);
    }

private:
    PolyNode* approach2(PolyNode* poly1, PolyNode* poly2)
    {
        PolyNode vHead;
        auto* node = &vHead;
        while (poly1 && poly2) {
            if (poly1->power == poly2->power) {
                const int sum = poly1->coefficient + poly2->coefficient;
                if (sum != 0) {
                    node->next = new PolyNode(sum, poly1->power);
                    node = node->next;
                }
                poly1 = poly1->next;
                poly2 = poly2->next;
            } else if (poly1->power > poly2->power) {
                node->next = poly1;
                poly1 = poly1->next;
                node = node->next;
            } else {
                node->next = poly2;
                poly2 = poly2->next;
                node = node->next;
            }
        }
        if (!poly1) {
            node->next = poly2;
        } else {
            node->next = poly1;
        }
        return vHead.next;
    }

    PolyNode* approach1(PolyNode* poly1, PolyNode* poly2)
    {
        std::map<int, int, std::greater<>> map;
        traverse(map, poly1);
        traverse(map, poly2);
        PolyNode vHead;
        auto* node = &vHead;
        for (const auto& [power, coefficient] : map) {
            if (coefficient == 0)
                continue;

            node->next = new PolyNode(coefficient, power);
            node = node->next;
        }
        return vHead.next;
    }

    void traverse(std::map<int, int, std::greater<>>& map, PolyNode* head)
    {
        while (head) {
            map[head->power] += head->coefficient;
            head = head->next;
        }
    }
};