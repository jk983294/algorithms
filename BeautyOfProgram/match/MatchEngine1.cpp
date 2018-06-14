#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace std;

class Reporter {
private:
    struct EVENT {
        long price;
        long vol;
    };

public:
    std::vector<EVENT> events;

public:
    int num_events;
    long total_price;

    void MatchEvent(long price, long vol) {
        EVENT event;
        event.price = price;
        event.vol = vol;
        ++num_events;
        total_price += price;
        events.push_back(event);
    }

    void Clear() {
        num_events = 0;
        total_price = 0;
    }
};

Reporter reporter;

#define MATCH(a, b) \
    { reporter.MatchEvent(a, b); };

#define BUY 0
#define SELL 1

class order {
public:
    long price;
    long qty;
    long filled;
    bool isBuy;
    bool cancelled{false};
    int orderId;

    order(long _price, long _qty, bool _isBuy, int _orderId) {
        this->price = _price;
        this->qty = _qty;
        this->isBuy = _isBuy;
        this->orderId = _orderId;
        this->filled = 0;
    }

    long remain_qty() { return qty - filled; }
};

class MatchEngine {
protected:
    std::map<long, std::list<std::shared_ptr<order>>, std::greater<long long>> bidBook;
    std::map<long, std::list<std::shared_ptr<order>>> askBook;
    std::map<int, std::shared_ptr<order>> id2order;
    int orderIdInternal = 0;

public:
    /**
     * LimitOrder handles the incoming order
     * @param direction BUY/SELL
     * @param price
     * @param vol
     * @return orderId
     */
    int LimitOrder(int direction, long price, long vol);

    void CancelOrder(int orderId);

    int MarketOrder(int direction, long vol);

private:
    void remove_order(std::list<std::shared_ptr<order>>& orders, std::list<std::shared_ptr<order>>::iterator itr1);
    void addOrder(std::shared_ptr<order> o, bool isMarketOrder);
};

int MatchEngine::LimitOrder(int direction, long price, long vol) {
    std::shared_ptr<order> o = std::shared_ptr<order>(new order(price, vol, direction == BUY, orderIdInternal++));
    addOrder(o, false);
    return o->orderId;
}

void MatchEngine::remove_order(std::list<std::shared_ptr<order>>& orders,
                               std::list<std::shared_ptr<order>>::iterator itr1) {
    for (auto i = orders.begin(); i != itr1; ++i) {
        id2order.erase((*i)->orderId);
    }
    orders.erase(orders.begin(), itr1);
}

int MatchEngine::MarketOrder(int direction, long vol) {
    std::shared_ptr<order> o = std::make_shared<order>(-1, vol, direction == BUY, orderIdInternal++);
    addOrder(o, true);
    return o->orderId;
}

void MatchEngine::CancelOrder(int orderId) {
    auto itr = id2order.find(orderId);
    if (itr != id2order.end()) {
        itr->second->cancelled = true;
    }
}

void MatchEngine::addOrder(std::shared_ptr<order> o, bool isMarketOrder) {
    long fill_count = 0;
    long lastFillPrice = -1;
    if (o->qty > 0) {
        if (o->isBuy) {
            auto askLevelItr = askBook.begin();
            while (o->remain_qty() > 0 && askLevelItr != askBook.end()) {
                if (isMarketOrder || askLevelItr->first <= o->price) {
                    auto vectorItr = askLevelItr->second.begin();
                    for (; vectorItr != askLevelItr->second.end(); ++vectorItr) {
                        order& askOrder = *(*vectorItr);
                        if (!askOrder.cancelled) {
                            if (askOrder.remain_qty() >= o->remain_qty()) {
                                fill_count = o->remain_qty();
                            } else {
                                fill_count = askOrder.remain_qty();
                            }
                            o->filled += fill_count;
                            askOrder.filled += fill_count;
                            lastFillPrice = askOrder.price;
                            MATCH(askOrder.price, fill_count);
                            if (o->remain_qty() == 0) break;
                        }
                    }
                    if (vectorItr != askLevelItr->second.end() && (*vectorItr)->remain_qty() == 0) {
                        ++vectorItr;
                    }
                    remove_order(askLevelItr->second, vectorItr);
                } else {
                    break;
                }
                if (o->remain_qty() == 0) break;
                ++askLevelItr;
            }  // end while

            if (askLevelItr != askBook.end() && askLevelItr->second.empty()) {
                ++askLevelItr;
            }
            askBook.erase(askBook.begin(), askLevelItr);

            if (o->remain_qty() > 0) {
                if (isMarketOrder) {
                    if (lastFillPrice > 0) {
                        o->price = lastFillPrice;
                    } else if (bidBook.size() > 0) {
                        o->price = bidBook.begin()->first;
                    }
                }

                if (o->price > 0) {
                    bidBook[o->price].push_back(o);
                    id2order[o->orderId] = o;
                }
            }
        } else {  // sell
            auto bidLevelItr = bidBook.begin();
            while (o->remain_qty() > 0 && bidLevelItr != bidBook.end()) {
                if (isMarketOrder || bidLevelItr->first >= o->price) {
                    auto vectorItr = bidLevelItr->second.begin();
                    for (; vectorItr != bidLevelItr->second.end(); ++vectorItr) {
                        order& bidOrder = *(*vectorItr);
                        if (!bidOrder.cancelled) {
                            if ((*vectorItr)->remain_qty() >= o->remain_qty()) {
                                fill_count = o->remain_qty();
                            } else {
                                fill_count = (*vectorItr)->remain_qty();
                            }
                            o->filled += fill_count;
                            bidOrder.filled += fill_count;
                            lastFillPrice = bidOrder.price;
                            MATCH(bidOrder.price, fill_count);
                            if (o->remain_qty() == 0) break;
                        }
                    }
                    if (vectorItr != bidLevelItr->second.end() && (*vectorItr)->remain_qty() == 0) {
                        ++vectorItr;
                    }
                    remove_order(bidLevelItr->second, vectorItr);
                } else {
                    break;
                }
                if (o->remain_qty() == 0) break;
                ++bidLevelItr;
            }  // end while
            if (bidLevelItr != bidBook.end() && bidLevelItr->second.empty()) {
                ++bidLevelItr;
            }
            bidBook.erase(bidBook.begin(), bidLevelItr);

            if (o->remain_qty() > 0) {
                if (isMarketOrder) {
                    if (lastFillPrice > 0) {
                        o->price = lastFillPrice;
                    } else if (askBook.size() > 0) {
                        o->price = askBook.begin()->first;
                    }
                }

                if (o->price > 0) {
                    askBook[o->price].push_back(o);
                    id2order[o->orderId] = o;
                }
            }
        }
    }
}

//****** following items are for test purpose, please do not modify ***************
MatchEngine engine;

std::vector<int> orderId;
static int num_test = 0;

#define TEST(d, p, v, n, ap)                                                      \
    {                                                                             \
        reporter.Clear();                                                         \
        orderId.push_back(engine.LimitOrder(d, p, v));                            \
        if (reporter.num_events == n && reporter.total_price == ap)               \
            std::cout << "SUCC: TEST " << ++num_test << " MATCH" << std::endl;    \
        else                                                                      \
            std::cout << "FAIL: TEST " << ++num_test << " MISMATCH" << std::endl; \
    }

#define TEST_CANCEL(ind)                  \
    {                                     \
        reporter.Clear();                 \
        engine.CancelOrder(orderId[ind]); \
    }

#define TEST_MARKET(d, v, n, ap)                                                  \
    {                                                                             \
        reporter.Clear();                                                         \
        orderId.push_back(engine.MarketOrder(d, v));                              \
        if (reporter.num_events == n && reporter.total_price == ap)               \
            std::cout << "SUCC: TEST " << ++num_test << " MATCH" << std::endl;    \
        else                                                                      \
            std::cout << "FAIL: TEST " << ++num_test << " MISMATCH" << std::endl; \
    }

int main(int argc, char** argv) {
    std::cout << "************ MATCH ENGINE *************" << std::endl;
    TEST(SELL, 100, 100, 0, 0);
    TEST(SELL, 101, 10, 0, 0);
    TEST(BUY, 99, 8, 0, 0);
    TEST(BUY, 100, 10, 1, 100);
    TEST(BUY, 101, 95, 2, 201);
    TEST(SELL, 101, 5, 0, 0);
    TEST(BUY, 100, 10, 0, 0);
    TEST(BUY, 99, 10, 0, 0);
    TEST_CANCEL(7);
    TEST(BUY, 99, 6, 0, 0);
    TEST(SELL, 97, 30, 3, 298);
    TEST(BUY, 98, 1, 1, 97);
    TEST_MARKET(BUY, 8, 2, 198);
    return 0;
};
