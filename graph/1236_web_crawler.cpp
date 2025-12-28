#include <string>
#include <unordered_set>
#include <vector>

/**
 * This is the HtmlParser's API interface.
 * You should not implement it, or speculate about its implementation
 */
class HtmlParser {
public:
    std::vector<std::string> getUrls(std::string url);
};

/**
 * Given a url startUrl and an interface HtmlParser, implement a web crawler to crawl all links that
 * are under the same hostname as startUrl.
 *
 * Return all urls obtained by your web crawler in any order.
 *
 * Your crawler should:
 *
 * - Start from the page: startUrl
 *
 * - Call HtmlParser.getUrls(url) to get all urls from a webpage of given url.
 *
 * - Do not crawl the same link twice.
 *
 * - Explore only the links that are under the same hostname as startUrl.
 *
 * As shown in the example url above, the hostname is example.org. For simplicity sake, you may
 * assume all urls use http protocol without any port specified. For example, the urls
 * http://leetcode.com/problems and http://leetcode.com/contest are under the same hostname, while
 * urls http://example.org/test and http://example.com/abc are not under the same hostname.
 *
 * The HtmlParser interface is defined as such:
 *
 * interface HtmlParser {
 *   Return a list of all urls from a webpage of given url.
 *   public List<String> getUrls(String url);
 * }
 *
 * Below are two examples explaining the functionality of the problem, for custom testing purposes
 * you'll have three variables urls, edges and startUrl. Notice that you will only have access to
 * startUrl in your code, while urls and edges are not directly accessible to you in code.
 *
 * Note: Consider the same URL with the trailing slash "/" as a different URL. For example,
 * "http://news.yahoo.com", and "http://news.yahoo.com/" are different urls.
 *
 * ! 1 <= urls.length <= 1000
 * ! 1 <= urls[i].length <= 300
 * ! startUrl is one of the urls.
 * ! Hostname label must be from 1 to 63 characters long, including the dots, may contain only the
 * ! ASCII letters from 'a' to 'z', digits  from '0' to '9' and the hyphen-minus character ('-'). !
 * ! The hostname may not start or end with the hyphen-minus character ('-').
 * ! See: https://en.wikipedia.org/wiki/Hostname#Restrictions_on_valid_hostnames
 * ! You may assume there're no duplicates in url library.
 */

class Solution {
public:
    std::vector<std::string> crawl(std::string startUrl, HtmlParser htmlParser)
    {
        dfs(htmlParser, startUrl, hostname(startUrl));
        return {visited.begin(), visited.end()};
    }

private:
    std::unordered_set<std::string> visited;

    std::string hostname(const std::string& url)
    {
        constexpr int start = 7;
        const int idx = std::min(url.size(), url.find('/', start));
        return url.substr(start, idx - start);
    }

    void dfs(HtmlParser& parser, const std::string& current, const std::string& targetHostname)
    {
        visited.insert(current);
        for (const auto& url : parser.getUrls(current)) {
            if (!visited.count(url) && hostname(url) == targetHostname) {
                dfs(parser, url, targetHostname);
            }
        }
    }
};