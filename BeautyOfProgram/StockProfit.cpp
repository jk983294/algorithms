#include "MyUtility.h"

/**
 * calculate difference between prices, which gives profit
 * then reduce to max sub-array problem
 */
int best_time_buy_sell_stock_only_once(vector<int> prices) {
    if (prices.size() <= 1) return 0;

    vector<int> profits;
    for (size_t i = 0; i < prices.size() - 1; ++i) {
        profits.push_back(prices[i + 1] - prices[i]);
    }

    int best = 0;
    int current = 0;
    for (size_t j = 0; j < profits.size(); ++j) {
        current = max(0, current + profits[j]);
        best = max(best, current);
    }
    return best;
}

/**
 * after you sell your stock, you cannot buy stock on next day. (ie, cool down 1 day)
 * for vector sells and buys, till index i, the buy / sell action must happen and must be the last action.
 * it may not happen at index i. It may happen at i - 1, i - 2, ... 0
 *
 * buys[i]: to make a decision whether to buy at i,
 * we either take a rest, by just using the old decision at i - 1,
 * or sell at/before i - 2, then buy at i, We cannot sell at i - 1, then buy at i, because of cool down.
 *
 * sells[i]: to make a decision whether to sell at i,
 * we either take a rest, by just using the old decision at i - 1, or buy at/before i - 1, then sell at i.
 */
int best_time_buy_sell_stock_with_one_day_cool_down(vector<int> prices) {
    size_t size = prices.size();
    if (size <= 1) return 0;

    vector<int> sells(size, 0);  // max profit till index i. The series of transaction is ending with a buy
    vector<int> buys(size, 0);   // max profit till index i. The series of transaction is ending with a sell
    buys[0] = 0;
    buys[1] = max(-prices[0], -prices[1]);  // choose min value of price[0]/prices[1] to buy
    sells[0] = 0;
    sells[1] = max(0, prices[1] - prices[0]);  // if prices[1] > price[0], then profit
    for (size_t i = 2; i < size; ++i) {
        sells[i] = max(sells[i - 1], buys[i - 1] + prices[i]);
        buys[i] = max(buys[i - 1], sells[i - 2] - prices[i]);
    }
    return sells[size - 1];
}

int main() {
    cout << best_time_buy_sell_stock_only_once({7, 1, 5, 3, 6, 4}) << endl;            // 5
    cout << best_time_buy_sell_stock_with_one_day_cool_down({1, 2, 3, 0, 2}) << endl;  // 3
    return 0;
}
